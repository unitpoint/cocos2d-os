var physics = _G.physics = _E = extends _G {}

var world = b2World()
function get world(){ return world }

var fixedTimeStep = 1.0f / 60
var velocityIterations = 10
var positionIterations = 8
var timeAccumulator = 0

addEventListener("enterFrame", function(params){
	timeAccumulator = timeAccumulator + params.deltaTime
	for(; timeAccumulator >= fixedTimeStep;){
		world.step(fixedTimeStep, velocityIterations, positionIterations)
		timeAccumulator = timeAccumulator - fixedTimeStep
	}
})

function get velocityIterations(){ return velocityIterations }
function set velocityIterations(a){ velocityIterations = a }

function get positionIterations(){ return positionIterations }
function set positionIterations(a){ positionIterations = a }

function get fixedTimeStep(){ return fixedTimeStep }
function set fixedTimeStep(a){ fixedTimeStep = a }

function createBody(params){
	return world.createBody(params)
}

function destroyBody(params){
	return world.destroyBody(params)
}

Node.__object.merge {
	__physicsUpdateInProgress = null,
	__physicsBody = null,
}

var nodeSetX = Node.__set@x
var nodeSetY = Node.__set@y

Node.merge {
	addPhysicsBody = function(params){
		@removePhysicsBody()
		@__physicsBody = world.createBody({}.merge(params, {
			x = @x,
			y = @y,
			angle = math.rad(@rotation),
		}))
		@addEventListener("enterFrame", @__updateNodePosition)
		return @physicsBody
	},
	removePhysicsBody = function(){
		if(@__physicsBody){
			@removeEventListener("enterFrame", @__updateNodePosition)
			world.destroyBody(@__physicsBody)
			@__physicsBody = null
		}
	},
	__updateNodePosition = function(){
		var xf = @__physicsBody.transform
		@__physicsUpdateInProgress = true
		@x, @y, @rotation = xf.x, xf.y, math.deg(xf.angle)
		@__physicsUpdateInProgress = false
	},
	__get@physicsBody = function(){
		return @__physicsBody
	},
	__set@x = function(a){
		nodeSetX.call(this, a)
		if(!@__physicsUpdateInProgress){
			@__physicsBody.position = [@x, @y]
		}
	},
	__set@y = function(a){
		nodeSetY.call(this, a)
		if(!@__physicsUpdateInProgress){
			@__physicsBody.position = [@x, @y]
		}
	},
}

function extractPoint(p){
	if(arrayOf(p)){
		return p[0], p[1]
	}
	return p.x, p.y
}

function extractSize(p){
	if(arrayOf(p)){
		return p[0], p[1]
	}
	return p.width, p.height
}

function getBoxShapeVertices(leftTopCorner, size){
	var x, y = extractPoint(leftTopCorner)
	var width, height = extractSize(size)
	return [ [x, y], [x + width, y], [x + width, y + height], [x, y + height] ]
}

