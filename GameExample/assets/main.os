var core = require("core")
var app = require("app")
var node = require("node")
var director = require("director")

print "Hello World!"

addEventListener("enterFrame", function(){
	// print "touches "..app.touches
}, true)

MyColorNode = extends ColorNode {
	__object = {
		speed = 0.5
		dx = 1 
		dy = 1
		touch = false
	}
	
	__construct = function(){
		super.__construct.call(this);
		
		var self, timer = this
		var function changeDir(){
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
			if(touch.phase == "start" && !touch.captured){
				var local = self.pointToNodeSpace(touch)
				if(self.isLocalPoint(local)){
					tx, ty, sx, sy = touch.x, touch.y, self.x, self.y
					touch.captured = self
					self.touch = true
					self.clearTimeout(timer)
					self.zOrder = 1
				}
			}else if(touch.phase == "move" && touch.captured === self){
				self.x, self.y = sx + touch.x - tx, sy + touch.y - ty
				self.touch = true
				self.clearTimeout(timer)
			}else if(touch.phase == "end" && touch.captured === self){
				self.touch = false
				changeDir()
				self.zOrder = 0
			}
		})
	}
	
	update = function(params){
		if(this.touch) return;
		
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
			return [math.random() math.random() math.random() 1]
		}
		
		for(var i = 0; i < 100; i++){
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
	}
}

director.scene = MyScene()

require("bitmapfont")