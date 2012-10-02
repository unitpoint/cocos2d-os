_E = extends _G {}
_G.physics = _E

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
	__physicsUpdateInProgress = null
	__physicsBody = null
}

var nodeSetX = Node.__set@x
var nodeSetY = Node.__set@y

Node.merge {
	addPhysicsBody = function(params){
		this.removePhysicsBody()
		this.__physicsBody = world.createBody({}.merge(params, {
			x = this.x
			y = this.y
			angle = math.rad(this.rotation)
		}))
		this.addEventListener("enterFrame", this.__updateNodePosition)
		return this.physicsBody
	}
	removePhysicsBody = function(){
		if(this.__physicsBody){
			this.removeEventListener("enterFrame", this.__updateNodePosition)
			world.destroyBody(this.__physicsBody)
			this.__physicsBody = null
		}
	}
	__updateNodePosition = function(){
		var xf = this.__physicsBody.transform
		this.__physicsUpdateInProgress = true
		this.x, this.y, this.rotation = xf.x, xf.y, math.deg(xf.angle)
		this.__physicsUpdateInProgress = false
	}
	__get@physicsBody = function(){
		return this.__physicsBody
	}
	__set@x = function(a){
		nodeSetX.call(this, a)
		if(!this.__physicsUpdateInProgress){
			this.__physicsBody.position = [this.x, this.y]
		}
	}
	__set@y = function(a){
		nodeSetY.call(this, a)
		if(!this.__physicsUpdateInProgress){
			this.__physicsBody.position = [this.x, this.y]
		}
	}
}

function extractPoint(p){
	if(arrayof p){
		return p[0], p[1]
	}
	return p.x, p.y
}

function extractSize(p){
	if(arrayof p){
		return p[0], p[1]
	}
	return p.width, p.height
}

function getBoxShapeVertices(leftTopCorner, size){
	var x, y = extractPoint(leftTopCorner)
	var width, height = extractSize(size)
	return [ [x, y], [x + width, y], [x + width, y + height], [x, y + height] ]
}

