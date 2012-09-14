var core = require("core")
var app = require("app")
var node = require("node")
var image = require("image")
var director = require("director")

print "Hello World!"

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
		
		var function color(){
			return [math.random(0.2 0.95) math.random(0.2 0.95) math.random(0.2 0.95) 1]
		}
		
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
				/*
				easy = Easy.outBounce
				duration = 2
				x = this.width * 0.7
				y = this.height * 0.3
				anchorX = 0.5
				anchorY = 0.5
				rotation = 45
				zOrder = 1
				opacity = 0.7
				*/
				sequence = [{
					duration = 2
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
				}]
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
	}
}

director.scene = MyScene()

require("bitmapfont")