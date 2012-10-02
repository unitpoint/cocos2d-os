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

		var message = Text("Angry Monsters StarterKit")	// create message
		message.x = this.width	// locate the message at right bottom corner
		message.y = this.height
		message.anchor = {x=1.05 y=1.05}
		message.shadow = true	// we want shadow enabled		
		this.insert(message)

		var animations = { // define animations for our monsters
			"monster-01.png" = {
				generalParams = {
					cols = 9
					rows = 10
					delay = 0.08
					rect = {
						center = {x=0.48, y=0.45}
						width = 0.5
						height = 0.74
					}
				}
				walkRight 	= { start = 0, frames = 17 }
				walkUp 		= { start = 17, frames = 13 }
				walkDown 	= { start = 30, frames = 12 }
				fightRight 	= { start = 42, frames = 12 }
				dieRight 	= { start = 67, frames = 17 }
			}
			"monster-03.png" = {
				generalParams = {
					cols = 7
					rows = 12
					delay = 0.08
					rect = {
						center = {x=0.46 y=0.48}
						width = 0.7 
						height = 0.8
					}
				}
				walkUp 		= { start = 17, frames = 13 }
				walkRight 	= { start = 0, frames = 17 }
				walkDown 	= { start = 30, frames = 12 }
				fightRight 	= { start = 42, frames = 11 }
				dieRight 	= { start = 70, frames = 11}
			}
		}
		for(var filename, anim in animations){ // prepare animations fo usage
			var generalParams = anim.generalParams
			delete anim.generalParams
			for(var animName, params in anim){
				anim[animName] = {}.merge(generalParams, params)
			}
		}
		
		var Monster = extends Sprite { // lets create Monster class so we can create a lot of monsters if necessary
			__object = { // all instances of this class will have following properies by default
				curAnimName = "" // playing animation name
				curAnim = null // playing animation object
				moveTransition = null // move transition object
				prevX = 0 // prev x && prev y to track monster speed
				prevY = 0
				health = 100 // monster health
				fighting = null // monster fighting with
			}
			
			__construct = function(filename){ // Monster class constructor, it's called when you do Monster(...)
				filename = filename || "monster-01.png"
				super(filename) // call constructor of class we extend, so create image
				this.animations = animations[filename] // save monster animations
				this.setTimeout(this.trackMove, 0.1, true)  // call this.trackMove every 0.1 seconds until we clear this timeout
				this.runAnimation("walkRight") // run "walkRight" animation by default
			}
			
			trackMove = function(){ // determine the direction of moving to switch animation
				if(!this.curAnim || this.fighting) return; // skip if no animation or monster is fighting
				var dx, dy = this.x - this.prevX, this.y - this.prevY
				this.prevX, this.prevY = this.x, this.y
				var len = (dx*dx + dy*dy)**0.5 // calculate length of the direction
				len > 0 || return;
				dx, dy = dx / len, dy / len // normalize the direction
				if(dy < -0.85 && "walkUp" in this.animations){ // monster goes up
					this.runAnimation("walkUp")
					this.flipX = false
				}else if(dy > 0.85 && "walkDown" in this.animations){ // monster goes down
					this.runAnimation("walkDown")
					this.flipX = false
				}else{ // monster goes left or right
					this.runAnimation("walkRight");
					this.flipX = dx < 0
				}
			}
			
			runAnimation = function(name, onComplete){ // start needed animation
				if(this.curAnimName == name && !onComplete) return; // prevent restarting animation
				this.curAnimName = name
				this.stopAnimation(this.curAnim)
				this.curAnim = this.animation(this.animations[name], onComplete)
			}
			
			move = function(x, y, onComplete){ // move monster to position x,y
				var len = ((this.x - x)**2 + (this.y - y)**2)**0.5
				this.stopTransition(this.moveTransition)
				this.moveTransition = this.transition { // lets use transition to move monster
					x = x, y = y
					duration = len * 10.0 / director.contentWidth
					onComplete = onComplete // call this function on complete
				}
			}
			
			fight = function(other){ // try to fight with other monster
				if(this.fighting || other.fighting) return; // skip if monster is already fighting
				var side = this.x < other.x ? -1 : 1
				var cx = (this.x + other.x) / 2
				var cy = (this.y + other.y) / 2
				
				this.fighting = other
				this.move(cx + this.width/2*side, cy, this.startFightingAnimation) // move monster to fighting position
				
				other.fighting = this
				other.move(cx - other.width/2*side, cy, other.startFightingAnimation) // move other monster to fighting position
			}
			
			startFightingAnimation = function(){ // start fighting
				this.health > 0 || return; // skip if monster is dead
				this.flipX = this.x > this.fighting.x // determine side of monster
				this.runAnimation("fightRight", function(){ // run fighting animations
					this.fighting.health = this.fighting.health - this.health * 0.3 // make damage to other monster
					this.fighting.timeSpeed = math.max(0.7, this.fighting.timeSpeed * 0.8) // damaged monster is tired, so make him slow down
					if(this.fighting.health <= 0){ // check if other monster is dead
						this.fighting.die() // start die animations
						this.fighting = null
						// go away a bit when the fight is finished
						this.move(this.x + math.random(-1, 1) * this.width, this.y + math.random(-1, 1) * this.width)
					}
				})
			}
			
			die = function(){ // start dying animations
				this.clearTimeout(this.trackMove) // remove this.trackMove timeout functions
				this.stopTransition(this.moveTransition) // stop moving animations
				this.flipX = this.x > this.fighting.x // determine side
				this.timeSpeed = 1 // reset time speed to 1
				this.runAnimation("dieRight", function(){ // run dying animations
					this.stopAnimation(this.curAnim)
					this.curAnim = null
					this.transition { // start fade out transition
						opacity = 0
						duration = 1
						onComplete = function(){
							this.remove() // remove monster on the fade out transition completed
						}
					}
				})
			}
			
			__set@y = function(y){ // track changing y position
				super(y) // call the same method of "super" class because we want to add behavior, not override
				this.zOrder = y // set zOrder, so bottom monsters will be front of top monsters
			}
		}
		
		var function color(){ // color random function
			return [math.random(0.8, 1), math.random(0.8, 1), math.random(0.8, 1)]
		}
		
		var monsters = [] // alive monsters array
		var scene = this
		var monsterNames = animations.keys // save keys of animations object, its are filenames
		var function createMonster(i){ // create new monster
			i = i || math.random(#monsterNames) // determine random monster name
			var monster = Monster(monsterNames[ i % #monsterNames ]) // create new instance of Monster class
			monster.x = scene.width * math.random(0.2, 0.8) // set random x position
			monster.y = scene.height * math.random(0.2, 0.8) // set random y position
			monster.timeSpeed = math.random(2.0, 3.0) // set random monster's local time speed
			monster.color = color() // set random color
			monster.opacity = 0 // set initial opacity to zero because of we want run fade in transition
			monster.transition { opacity = 1, duration = 1 } // start the fade in transition
			scene.insert(monster) // insert monster to scene
			monsters.push(monster) // save our monster to the alive monsters array
			monster.addEventListener("onExit", function(){ // capture onExit event (when monster will be dead)
				for(var i, m in monsters){
					if(m === this){ // find monster inside of to the alive monsters array
						delete monsters[i] // remove it
						createMonster(math.random(#monsterNames)) // create new monster
						return;
					}
				} 
			})
		}
		
		for(var i = 0; i < 20; i++){ // create initial monsters
			createMonster()
		}
		
		var function moveMonsters(x, y){ // move monsters to the touched position
			for(var i, monster in monsters){
				if(!monster.fighting) monster.move(x, y)
			}
		}
		
		this.addEventListener("touch", function(touch){
			moveMonsters(touch.local.x, touch.local.y)
		})
		
		this.setTimeout(function(){ // set new timeout function to check monsters crossed
			for(var i, monster in monsters){
				if(monster.fighting) continue
				for(var j = i+1; j < #monsters; j++){
					var other = monsters[j]
					var dist = ((monster.x - other.x)**2 + (monster.y - other.y)**2)**0.5
					if(dist < monster.width){ // are monsters close to each other to fight
						monster.fight(other)
					}
				}
			}
		}, 0.3, true) // call the timeout each 0.3 seconds forever
	}
}

director.scene = MyScene()	// create and set our game scene
