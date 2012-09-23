/*
world = b2World()

body = world.createBody {
	type = "static"
	position = {x=0 y=0}
}

body.createFixture {
	shape = {
		type = "circle"
		position = {x=100 y=100}
		radius = 125
	}
	friction = 0.2
	restitution = 0
	density = 0
	categoryBits = 0x0001
	maskBits = 0xfff
	groupIndex = 0
	isSensor = false
}
*/

var core = require("core")
var app = require("app")
var node = require("node")
var image = require("image")
var text = require("text")
var director = require("director")

print "Hello World!"

print "Sprite\n"..Sprite

// var image = Texture2d("award-first.png")
// print("image width "image.width" height "image.height" pixelformat "image.pixelFormat" hasPremultipliedAlpha "image.hasPremultipliedAlpha)

addEventListener("enterFrame", function(){
	// print "touches "..app.touches
}, true)

MyColorNode = extends ColorNode {
	__object = {
		speed = 0.5
		dx = 1 
		dy = 1
		touched = false
	}
	
	__construct = function(){
		super()
		
		var self, timer = this
		var function changeDir(){
			// print "changeDir "..self.osValueId
			self.dx = math.random(-1 1)
			self.dy = math.random(-1 1)
			// self.clearTimeout(timer)
			timer = self.setTimeout(changeDir, math.random(3.0 5.0))
		}
		changeDir()
		
		this.addEventListener("enterFrame", function(params){
			this.update(params)
		})
		
		var tx, ty, sx, sy
		this.addEventListener("touch", function(touch){
			if(touch.phase == "start"){
				tx, ty, sx, sy = touch.x, touch.y, self.x, self.y
				self.touched = true
				self.zOrder = 1
				self.clearTimeout(timer)
			}else if(touch.phase == "move"){
				self.x, self.y = sx + touch.x - tx, sy + touch.y - ty
			}else if(touch.phase == "end"){
				self.touched = false
				self.zOrder = 0
				changeDir()
			}
		})
	}
	
	update = function(params){
		if(this.touched) return;
		
		var offs = director.width * this.speed * params.deltaTime
		
		this.x = this.x + this.dx * offs
		this.y = this.y + this.dy * offs
		
		var function clamp(a min max){
			if(a < min) return min
			if(a > max) return max
			return a
		}
		
		if(this.x < 0 || this.x > this.__parent.width){
			this.dx = -this.dx
			this.x = clamp(this.x, 0, this.__parent.width)
		}
		if(this.y < 0 || this.y > this.__parent.height){
			this.dy = -this.dy
			this.y = clamp(this.y, 0, this.__parent.height)
		}
	}
}

MyScene = extends Scene {
	__construct = function(){
		super()
		glClearColor(0.2 0.2 0.2 1)
		
		var function color(){
			return [math.random(0.2 0.95) math.random(0.2 0.95) math.random(0.2 0.95) 1]
		}
		
		var message = Text("Awesome text with shadow")
		message.x = this.width * 0.5
		message.y = this.height * 0.5
		message.color = [1 0 0 1]
		message.shadow = true
		this.insert(message)

		var font = "arial-en-ru-16.fnt"
		var fps = Text("fps", font)
		fps.anchor = {x=1.05 y=1.05}
		fps.x = this.width
		fps.y = this.height
		fps.color = [0.9, 0.9, 0.0, 1]
		// fps.shadow = true
		this.insert(fps)
		
		var gcAllocatedBytes = Text("Kb", font)
		gcAllocatedBytes.anchor = {x=1.05 y=1.05}
		gcAllocatedBytes.x = fps.x
		gcAllocatedBytes.y = fps.y - fps.fontHeight*1.05*1
		gcAllocatedBytes.color = [0.9, 0.9, 0.0, 1]
		// gcAllocatedBytes.shadow = true
		this.insert(gcAllocatedBytes)
		
		var gcUsedBytes = Text("Kb", font)
		gcUsedBytes.anchor = {x=1.05 y=1.05}
		gcUsedBytes.x = fps.x
		gcUsedBytes.y = fps.y - fps.fontHeight*1.05*3
		gcUsedBytes.color = [0.9, 0.9, 0.0, 1]
		// gcUsedBytes.shadow = true
		this.insert(gcUsedBytes)
		
		var gcCachedBytes = Text("Kb", font)
		gcCachedBytes.anchor = {x=1.05 y=1.05}
		gcCachedBytes.x = fps.x
		gcCachedBytes.y = fps.y - fps.fontHeight*1.05*2
		gcCachedBytes.color = [0.9, 0.9, 0.0, 1]
		// gcAllocatedBytes.shadow = true
		this.insert(gcCachedBytes)
		
		var gcNumObjects = Text("0", font)
		gcNumObjects.anchor = {x=1.05 y=1.05}
		gcNumObjects.x = fps.x
		gcNumObjects.y = fps.y - fps.fontHeight*1.05*4
		gcNumObjects.color = [0.9, 0.9, 0.0, 1]
		// gcNumObjects.shadow = true
		this.insert(gcNumObjects)
		
		this.setTimeout(function(){
			fps.string = math.round(1 / director.deltaTime, 1).." fps"
			gcAllocatedBytes.string = math.round(GC.allocatedBytes / 1024).." Kb allocated"
			gcUsedBytes.string = math.round((GC.allocatedBytes - GC.cachedBytes) / 1024).." Kb used"
			gcCachedBytes.string = math.round(GC.cachedBytes / 1024).." Kb cached"
			gcNumObjects.string = GC.numObjects.." gc objects"
		}, 0.3, true)
		
		for(var i = 0; i < 10; i++){
			var monster = ((i % 2) == 0 ? Sprite : Image)("monster-01.png")
			// monster.name = "monster"
			var anim = monster.animation {
				cols = 9
				rows = 10
				delay = 0.08 // math.random(0.05, 0.1)
				start = 0
				frames = 17
				rect = {
					center = {x=0.48, y:0.45}
					width = 0.5 * 1.2
					height = 0.74 * 1.2
				}
			}
			anim.index = math.random(#anim.frames)
			monster.x = this.width * math.random(0.2, 0.8)
			monster.y = this.height * math.random(0.2, 0.8)
			monster.zOrder = monster.y
			monster.color = color()
			monster.timeSpeed = math.random(0.5, 5.0)
			// monster.scale = math.random(0.2, 2.0)
			this.insert(monster)
			
			function(){
				var tx, ty, sx, sy
				this.addEventListener("touch", function(touch){
					if(touch.phase == "start"){
						tx, ty, sx, sy = touch.x, touch.y, this.x, this.y
						this.zOrder = this.y
						// touch.captured = this
						// print("start " this.x this.y)
					}else if(touch.phase == "move"){
						this.x, this.y = sx + touch.x - tx, sy + touch.y - ty
						this.zOrder = this.y
						// print("move " this.x this.y)
					}else if(touch.phase == "end"){
						// this.zOrder = 0
						// print("end " this.x this.y)
					}
				})			
			}.call(monster)
		}
		// return this
		
		;{
			// var rect = ColorNode()
			var rect = Image("award-first.png")
			rect.speed = math.random(0.2 0.5)
			rect.anchor = {x = 0 y = 1}
			rect.setRect(
				this.width * 0.0
				this.height * 1.0
				100
				200
				)
			rect.color = color()
			
			// print "before transition"
			rect.transition { 
				delay = 2
				easy = Easy.inOutBounce
				// speed = 0.5
				repeat = true
				sequence = [{
					duration = 3
					x = this.width * 0.4
					y = this.height * 0.7
					anchorX = 0.5
					anchorY = 0.5
					rotation = 45
					zOrder = 1
					opacity = 0.7
				}, {
					duration = 1
					x = this.width * 0.7
					y = this.height * 0.3
					anchorX = 0.5
					anchorY = 0.5
					rotation = 45
					zOrder = 1
					opacity = 0.7
				}, {
					duration = 1
					x = this.width * 0.3
					y = this.height * 0.7
					rotation = -45
					opacity = 1.0
				}, {
					duration = 1
					x = this.width * 0.1
					y = this.height * 0.1
					rotation = 270
				}, {
					duration = 1
					x = this.width * 0.0
					y = this.height * 1.0
					anchorX = 0
					anchorY = 1
					rotation = 0
				}
				]
			}
			// print "after transition"
			
			this.insert(rect)
		}
		
		// OOP way using class MyColorNode, please see implementation of MyColorNode above
		for(var i = 0; i < 0; i++){
			var rect = MyColorNode()
			rect.speed = math.random(0.2 0.5)
			rect.setRect(
				this.width * math.random(0.1 0.7) 
				this.height * math.random(0.1 0.7) 
				this.width * math.random(0.1 0.2) 
				this.width * math.random(0.1 0.2) 
			)
			rect.color = color()
			this.insert(rect)
		}
		
		// the same functionality but using closure instead of OOP
		var scene = this
		for(var i = 0; i < 5; i++){
			function(){
				var self = Image("award-first.png") // ColorNode()
				self.anchor = { x = 0.5 y = 0.38 }
				var speed = math.random(0.2 0.5)
				self.setRect(
					scene.width * math.random(0.1 0.7) 
					scene.height * math.random(0.1 0.7) 
					scene.width * math.random(0.1 0.2) 
					scene.width * math.random(0.1 0.2) 
					)
				self.color = color()
				scene.insert(self)
				
				var dx, dy, touched, timer
				var function changeDir(){
					dx = math.random(-1 1)
					dy = math.random(-1 1)
					timer = self.setTimeout(changeDir, math.random(3.0 5.0))
				}
				changeDir()
				
				var tx, ty, sx, sy
				self.addEventListener("touch", function(touch){
					if(touch.phase == "start"){
						tx, ty, sx, sy = touch.x, touch.y, this.x, this.y
						touched = true
						this.zOrder = 1
						this.clearTimeout(timer)
					}else if(touch.phase == "move"){
						this.x, this.y = sx + touch.x - tx, sy + touch.y - ty
					}else if(touch.phase == "end"){
						touched = false
						this.zOrder = 0
						this.opacity = 1
						changeDir()
					}
				})
				
				var function clamp(a min max){
					if(a < min) return min
					if(a > max) return max
					return a
				}
				
				var rotSpeed = math.random(0.8 1.5)
				var time = 0
				self.addEventListener("enterFrame", function(params){
					if(touched){ 
						this.scaleX = 1 + (math.cos(this.time * math.PI * rotSpeed) + 1) / 2 * 0.5
						this.scaleY = 1 + (math.sin(this.time * math.PI * rotSpeed * 3) + 1) / 2 * 0.5
						this.opacity = 0.5 + (math.sin(this.time * math.PI * rotSpeed * 2) + 1) / 2 * 1.0
						return
					}
					time = time + params.deltaTime
					this.rotation = math.deg(math.sin(time * math.PI * rotSpeed))
					
					var offs = director.width * speed * params.deltaTime
					
					this.x = this.x + dx * offs
					this.y = this.y + dy * offs
					
					if(this.x < 0 || this.x > this.parent.width){
						dx = -dx
						this.x = clamp(this.x, 0, this.parent.width)
					}
					if(this.y < 0 || this.y > this.parent.height){
						dy = -dy
						this.y = clamp(this.y, 0, this.parent.height)
					}
				})
				
			}()
		}
		
		if(true){
			var bg = Image("bg.jpg")
			bg.x = this.width / 2
			bg.y = this.height / 2
			bg.scale = math.max(this.width / bg.width, this.height / bg.height)
			this.insert(bg, -10)
			
			var ball = Image("ball.png")
			ball.x = this.width * 0.5
			ball.y = this.height * 0.1
			ball.zOrder = 1000
			this.insert(ball)
			
			var physics = b2World()
			var physicsHz = 60
			var physicsTimeStep = 1.0f / physicsHz
			var physicsVelocityIterations = 10
			var physicsPositionIterations = 8
			var physicsTimeAccumulator = 0
			this.addEventListener("enterFrame", function(params){
				physicsTimeAccumulator = physicsTimeAccumulator + params.deltaTime
				for(; physicsTimeAccumulator >= physicsTimeStep;){
					debugger
					physics.step(physicsTimeStep, physicsVelocityIterations, physicsPositionIterations)
					physicsTimeAccumulator = physicsTimeAccumulator - physicsTimeStep
				}
			})
			
			var body = physics.createBody {
				type = "dynamic"
				x = ball.x
				y = ball.y
				fixture = {
					shape = {
						type = "circle"
						radius = ball.width/2
					}
					density = 1
				}
			}
			ball.addEventListener("enterFrame", function(){
				var position = body.position
				this.x, this.y = position.x, position.y
				this.rotation = math.deg(body.angle)
			})
		}
		
		if(false){
			var bg = Image("bg.jpg")
			bg.x = this.width / 2
			bg.y = this.height / 2
			bg.scale = math.max(this.width / bg.width, this.height / bg.height)
			this.insert(bg, -10)
			
			var ball = Image("ball.png")
			ball.x = this.width / 2
			ball.y = this.height / 2
			ball.zOrder = 1000
			this.insert(ball)
			
			var friction, gravity = 0.9, 9
			var screenWidth, screenHeight = this.width, this.height
			var speedX, speedY = math.random(-0.5, 0.5)*screenWidth, math.random(0.5, 1)*screenWidth
			var radius = ball.width/2
			
			ball.addEventListener("touch", function(touch){
				if(touch.phase == "start"){
					// tx, ty, sx, sy = touch.x, touch.y, this.x, this.y
					this.x0, this.y0 = touch.x - this.x, touch.y - this.y
					this.removeEventListener("enterFrame", physUpdate)
					this.addEventListener("enterFrame", trackVelocity)
				}else if(touch.phase == "move"){
					this.x, this.y = touch.x - this.x0, touch.y - this.y0
				}else if(touch.phase == "end" || touch.phase == "cancel"){
					this.addEventListener("enterFrame", physUpdate)
					this.removeEventListener("enterFrame", trackVelocity)
				}
			})
			
			var prevX, prevY = 0, 0
			var function trackVelocity(params){
				speedX = (this.x - prevX) / params.deltaTime
				speedY = (this.y - prevY) / params.deltaTime
				prevX, prevY = this.x, this.y
			}
				
			var function physUpdate(params){
				speedY = speedY + gravity
				this.x = this.x + speedX * params.deltaTime
				this.y = this.y + speedY * params.deltaTime
				if(this.x >= screenWidth - radius){
					this.x = screenWidth - radius
					speedX = speedX * -friction
				}else if(this.x <= radius){
					this.x = radius
					speedX = speedX * -friction
				}
				if(this.y >= screenHeight - radius){
					this.y = screenHeight - radius
					speedY = speedY * -friction
					speedX = speedX * friction
				}else if(this.y <= radius){
					this.y = radius
					speedY = speedY * -friction
				}
			}
			ball.addEventListener("enterFrame", physUpdate)
		}
	}
}

director.scene = MyScene()

// require("bitmapfont")