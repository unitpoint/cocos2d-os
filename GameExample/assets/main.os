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
		dd = [1 1]
		touch = false
	}
	
	isLocalPoint = function(point){
		return point.x >= 0 && point.x < this.width 
			&& point.y >= 0 && point.y < this.height
	}
	
	__construct = function(){
		super.__construct.call(this);
		
		var self, timer = this
		var function changeDir(){
			self.dd[0] = math.random(-1 1)
			self.dd[1] = math.random(-1 1)
			// self.clearTimeout(timer)
			timer = self.setTimeout(changeDir, math.random(3.0 5.0))
		}
		changeDir()
		
		var tx, ty, sx, sy
		this.addEventListener("touch", function(touch){
			if(touch.phase == "start" && !touch.captured){
				var local = self.pointToNodeSpace(touch)
				if(self.isLocalPoint(local)){
					tx, ty, sx, sy = touch.x, touch.y, self.x, self.y
					touch.captured = self
					self.touch = true
					self.clearTimeout(timer)
				}
			}else if(touch.phase == "move" && touch.captured === self){
				self.x, self.y = sx + touch.x - tx, sy + touch.y - ty
				self.touch = true
				self.clearTimeout(timer)
			}else if(touch.captured === self){
				self.touch = false
				changeDir()
			}
		})
	}
	
	update = function(deltaTimeSec){
		if(this.touch) return;
		
		var offsPerSec = director.width * this.speed * deltaTimeSec
		
		this.x = this.x + this.dd[0] * offsPerSec
		this.y = this.y + this.dd[1] * offsPerSec
		
		var function clamp(a min max){
			if(a < min) return min
			if(a > max) return max
			return a
		}
		
		if(this.x < 0 || this.x > this.__parent.width){
			this.dd[0] = -this.dd[0]
			this.x = clamp(this.x, 0, this.__parent.width)
		}
		if(this.y < 0 || this.y > this.__parent.height){
			this.dd[1] = -this.dd[1]
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
		
		for(var i = 0; i < 10; i++){
			var rect = MyColorNode()
			rect.speed = math.random(0.2 0.5)
			rect.setRect(
				this.width * math.random(0.1 0.7) 
				this.height * math.random(0.1 0.7) 
				this.width * math.random(0.1 0.2) 
				this.width * math.random(0.1 0.2) 
				)
			rect.color = color()
			this.addChild(rect)
		}
	}
}

director.scene = MyScene()

require("bitmapfont")