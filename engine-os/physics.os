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

PhysicsBodyNode = extends FunctionNode {
	__object = {
		body = null
	}
	__construct = function(parent, params){
		params = clone params
		
		var function createBody(){
			if(!this.body){
				this.body = world.createBody(params.merge {
					x = parent.x
					y = parent.y
					angle = math.rad(parent.rotation)
				})
			}
		}
		createBody.call(this)
		this.addEventListener("onEnter", function(){
			createBody.call(this)
			this.addEventListener("enterFrame", this.update)
		})
		this.addEventListener("onExit", function(){
			this.removeEventListener("enterFrame", this.update)
			world.destroyBody(this.body)
			this.body = null
		})
		"__physicsBodyNode" in parent && parent.remove(parent.__physicsBodyNode)
		parent.__physicsBodyNode = parent.insert(this)
	}
	
	update = function(){
		var xf, parent = this.body.transform, this.parent
		parent.x, parent.y, parent.rotation = xf.x, xf.y, math.deg(xf.angle)
	}
}

function Node.addPhysicsBody(params){
	return PhysicsBodyNode(this, params).body
}

function Node.__get@physicsBody(){
	return "__physicsBodyNode" in this ? this.__physicsBodyNode.body : null
}
