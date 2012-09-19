var director = require("director")

print "Hello World!" // please see all printed messages here: assets-ram/output.txt

MyScene = extends Scene {
	__construct = function(){
		super() // call constructor of class we extend
		
		var bg = Image("bg.jpg") 	// create background image
		bg.x = this.width / 2		// locate it at center of scene 
		bg.y = this.height / 2
		bg.scale = math.max(this.width / bg.width, this.height / bg.height)
		this.insert(bg)				// insert the background image to the scene

		var message = Text("Sprite Sheet Animation")	// create message
		message.x = this.width	// locate the message at right bottom corner
		message.y = this.height
		message.anchor = {x=1.05 y=1.05}
		message.shadow = true	// we want shadow enabled		
		this.insert(message)

		var Monster = extends Image {
			__object = {
				curAnimName = ""
				curAnim = null
				moveTransition = null
				prevX = 0
				prevY = 0
			}
			
			__construct = function(filename, animations){
				super(filename)
				this.animations = animations
				this.setTimeout(this.trackMove, 0.1, true)
				this.runAnimation("walkRight")
			}
			
			trackMove = function(){
				var dx, dy = this.x - this.prevX, this.y - this.prevY
				this.prevX, this.prevY = this.x, this.y
				var len = (dx*dx + dy*dy)**0.5
				if(len == 0) return;
				dx, dy = dx / len, dy / len
				if(dy < -0.85){
					this.runAnimation("walkUp")
					this.flipX = false
				}else if(dy > 0.85){
					this.runAnimation("walkDown")
					this.flipX = false
				}else{
					this.runAnimation("walkRight");
					this.flipX = dx < 0
				}
			}
			
			runAnimation = function(name){
				if(this.curAnimName == name) return;
				this.curAnimName = name
				this.stopAnimation(this.curAnim)
				this.curAnim = this.animation(this.animations[name])
			}
			
			move = function(x, y){
				var len = ((this.x - x)**2 + (this.y - y)**2)**0.5
				this.stopTransition(this.moveTransition)
				this.moveTransition = this.transition {
					x = x, y = y
					duration = len * 10.0 / director.width
				}
			}
			
			__set@y = function(y){
				super(y)
				this.zOrder = y
			}
		}
		
		var monster = Monster("monster-01.png", { 
			walkRight 	= { start = 0, frames = 17, delay = 0.08, cols = 9, rows = 10 }
			walkUp 		= { start = 17, frames = 13, delay = 0.08, cols = 9, rows = 10 }
			walkDown 	= { start = 30, frames = 12, delay = 0.08, cols = 9, rows = 10 }
			fightRight 	= { start = 42, frames = 12, delay = 0.08, cols = 9, rows = 10 }
			dieRight 	= { start = 67, frames = 17, delay = 0.08, cols = 9, rows = 10 }
		})
		monster.x = this.width * math.random(0.2, 0.8)
		monster.y = this.height * math.random(0.2, 0.8)
		this.insert(monster)
		
		this.addEventListener("touch", function(touch){
			monster.move(touch.x, touch.y)
		})
	}
}

director.scene = MyScene()	// create and set our game scene
