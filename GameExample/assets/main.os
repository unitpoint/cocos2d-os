var core = require("core")
var app = require("app")
var node = require("node")
var director = require("director")

print "Hello World!"

MyColorNode = extends ColorNode {
	__object = {
		speed: 0.5
		dd: [1 1] // math.random()
	}
	
	__construct = function(){
		super.__construct.call(this);
		
		var self = this
		var function changeDir(){
			self.dd[0] = math.random(-1 1)
			self.dd[1] = math.random(-1 1)
			self.setTimeout(changeDir, math.random(0.5 1.5))
		}
		changeDir()
	}
	
	update = function(deltaTimeSec){
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
		
		var rect = ColorNode()
		rect.speed = math.random(0.2 0.5)
		rect.setRect(
			this.width * 0.75
			this.height * 0.75
			200
			100
			)
		rect.color = color()
		this.addChild(rect)
		
		for(var i = 0; i < 0; i++){
			var rect = MyColorNode()
			rect.speed = math.random(0.2 0.5)
			rect.setRect(
				this.width * math.random(0.1 0.6) 
				this.height * math.random(0.1 0.6) 
				this.width * math.random(0.1 0.3) 
				this.width * math.random(0.1 0.3) 
				)
			rect.color = color()
			this.addChild(rect)
		}
	}
}

director.scene = MyScene()

