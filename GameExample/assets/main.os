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
		super.__construct.call(this);
		
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
			self.update(params)
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
		
		var offsPerSec = director.width * this.speed * params.deltaTimeSec
		
		this.x = this.x + this.dx * offsPerSec
		this.y = this.y + this.dy * offsPerSec
		
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
		super.__construct.call(this);
		
		var function color(){
			return [math.random(0.2 0.95) math.random(0.2 0.95) math.random(0.2 0.95) 1]
		}
		
		{
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
		for(var i = 0; i < 20; i++){
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
						tx, ty, sx, sy = touch.x, touch.y, self.x, self.y
						touched = true
						self.zOrder = 1
						self.clearTimeout(timer)
					}else if(touch.phase == "move"){
						self.x, self.y = sx + touch.x - tx, sy + touch.y - ty
					}else if(touch.phase == "end"){
						touched = false
						self.zOrder = 0
						changeDir()
					}
				})
				
				var function clamp(a min max){
					if(a < min) return min
					if(a > max) return max
					return a
				}
				
				// self.rotation = 45
				/* self.addEventListener("enterFrame", function(params){
					self.rotation = 45 // math.deg(math.sin(params.deltaTimeSec * math.PI * 2))
				}) */
				
				var rotSpeed = math.random(0.8 1.5)
				self.addEventListener("enterFrame", function(params){
					self.rotation = math.deg(math.sin(self.timeSec * math.PI * rotSpeed))
					
					if(touched) return;
					
					var offsPerSec = director.width * speed * params.deltaTimeSec
					
					self.x = self.x + dx * offsPerSec
					self.y = self.y + dy * offsPerSec
					
					if(self.x < 0 || self.x > self.__parent.width){
						dx = -dx
						self.x = clamp(self.x, 0, self.__parent.width)
					}
					if(self.y < 0 || self.y > self.__parent.height){
						dy = -dy
						self.y = clamp(self.y, 0, self.__parent.height)
					}
				})
				
			}()
		}
	}
}

director.scene = MyScene()

require("bitmapfont")