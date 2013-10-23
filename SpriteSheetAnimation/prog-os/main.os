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
		message.anchor = {x=1.05, y=1.05}
		message.shadow = true	// we want shadow enabled		
		this.insert(message)

		var Monster = extends Image { // lets create Monster class so we can create a lot instances (monsters) if necessary
			__object = { // all instances of this class will have following properies by default
				curAnimName = "", // playing animation name
				curAnim = null,	// playing animation object
				moveTransition = null, // move transition object
				prevX = 0, // prev x && prev y to track monster speed
				prevY = 0,
			},
			
			__construct = function(filename, animations){
				super(filename) // call constructor of class we extend, so create image
				this.animations = animations
				this.setTimeout(this.trackMove, 0.1, true) // call this.trackMove every 0.1 seconds until we clear this timeout
				this.runAnimation("walkRight") // run "walkRight" animation by default
			},
			
			trackMove = function(){ // determine the direction of moving to switch animation
				var dx, dy = this.x - this.prevX, this.y - this.prevY
				this.prevX, this.prevY = this.x, this.y
				var len = (dx*dx + dy*dy)**0.5 // calculate length of the direction
				if(len == 0) return;
				dx, dy = dx / len, dy / len
				if(dy < -0.85){ // monster goes up
					this.runAnimation("walkUp")
					this.flipX = false
				}else if(dy > 0.85){ // monster goes down
					this.runAnimation("walkDown")
					this.flipX = false
				}else{ // // monster goes left or right
					this.runAnimation("walkRight");
					this.flipX = dx < 0
				}
			},
			
			runAnimation = function(name){ // start animation
				if(this.curAnimName == name) return;
				this.curAnimName = name
				this.stopAnimation(this.curAnim)
				this.curAnim = this.animation(this.animations[name])
			},
			
			move = function(x, y){ // move monster to position x,y
				var len = ((this.x - x)**2 + (this.y - y)**2)**0.5
				this.stopTransition(this.moveTransition)
				this.moveTransition = this.transition { // lets use transition to move monster
					x = x, y = y,
					duration = len * 10.0 / director.contentWidth,
				}
			},
			
			__set@y = function(y){ // track changing y position
				super(y) // call the same method of "super" class because we want to add behavior, not override
				this.zOrder = y // set zOrder, so bottom monsters will be front of top monsters
			},
		}
		
		var monster = Monster("monster-01.png", { // create our monster
			walkRight 	= { start = 0, frames = 17, delay = 0.08, cols = 9, rows = 10 },
			walkUp 		= { start = 17, frames = 13, delay = 0.08, cols = 9, rows = 10 },
			walkDown 	= { start = 30, frames = 12, delay = 0.08, cols = 9, rows = 10 },
			fightRight 	= { start = 42, frames = 12, delay = 0.08, cols = 9, rows = 10 },
			dieRight 	= { start = 67, frames = 17, delay = 0.08, cols = 9, rows = 10 },
		})
		monster.x = this.width * math.random(0.2, 0.8)
		monster.y = this.height * math.random(0.2, 0.8)
		monster.scale = 1.5 // scale monster to make them bigger
		this.insert(monster) // insert monster to the scene
		
		this.addEventListener("touch", function(touch){
			monster.move(touch.x, touch.y)
		})
	}
}

director.scene = MyScene()	// create and set our game scene
