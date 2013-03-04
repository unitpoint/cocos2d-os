var director = require("director")

print "Hello World!" // please see all printed messages here: assets-ram/output.txt

var function addStats(parent){
	var color = [0.0, 0.0, 0.0, 1]
	var font = "arial-en-ru-16.fnt"
	var fps = Text("fps", font).attrs {
		anchor = {x=1.05 y=1.05}
		x = parent.width
		y = parent.height - 50
		color = color
		// shadow = true
	}.insertTo(parent)
	
	var gcAllocatedBytes = Text("Kb", font).attrs{
		anchor = {x=1.05 y=1.05}
		x = fps.x
		y = fps.y - fps.fontHeight*1.05*1
		color = color
		// shadow = true
	}.insertTo(parent)
	
	var gcUsedBytes = Text("Kb", font).attrs{
		anchor = {x=1.05 y=1.05}
		x = fps.x
		y = fps.y - fps.fontHeight*1.05*3
		color = color
		// shadow = true
	}.insertTo(parent)
	
	var gcCachedBytes = Text("Kb", font).attrs{
		anchor = {x=1.05 y=1.05}
		x = fps.x
		y = fps.y - fps.fontHeight*1.05*2
		color = color
		// shadow = true
	}.insertTo(parent)
	
	var gcNumObjects = Text("0", font).attrs{
		anchor = {x=1.05 y=1.05}
		x = fps.x
		y = fps.y - fps.fontHeight*1.05*4
		color = color
		// shadow = true
	}.insertTo(parent)
	
	parent.setTimeout(function(){
		fps.string = sprintf("%.1f fps", 1 / director.deltaTime)
		gcAllocatedBytes.string = math.round(GC.allocatedBytes / 1024).." Kb allocated"
		gcUsedBytes.string = math.round((GC.allocatedBytes - GC.cachedBytes) / 1024).." Kb used"
		gcCachedBytes.string = math.round(GC.cachedBytes / 1024).." Kb cached"
		gcNumObjects.string = GC.numObjects.." gc objects"
	}, 0.3, true)
}

MyScene = extends Scene {
	__construct = function(){
		super() // call constructor of class we extend
		
		var bg = Image("bg.jpg") 	// create background image
		bg.x = @width / 2		// locate it at center of scene 
		bg.y = @height / 2
		bg.scale = math.max(@width / bg.width, @height / bg.height)
		@insert(bg)				// insert the background image to the scene

		var message = Text("Angry Monsters StarterKit")	// create message
		message.x = @width	// locate the message at right bottom corner
		message.y = @height
		message.anchor = {x=1.05 y=1.05}
		message.shadow = true	// we want shadow enabled		
		@insert(message)

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
				@animations = animations[filename] // save monster animations
				@setTimeout(@trackMove, 0.1, true)  // call @trackMove every 0.1 seconds until we clear this timeout
				@runAnimation("walkRight") // run "walkRight" animation by default
			}
			
			trackMove = function(){ // determine the direction of moving to switch animation
				if(!@curAnim || @fighting) return; // skip if no animation or monster is fighting
				var dx, dy = @x - @prevX, @y - @prevY
				@prevX, @prevY = @x, @y
				var len = (dx*dx + dy*dy)**0.5 // calculate length of the direction
				len > 0 || return;
				dx, dy = dx / len, dy / len // normalize the direction
				if(dy < -0.85 && "walkUp" in @animations){ // monster goes up
					@runAnimation("walkUp")
					@flipX = false
				}else if(dy > 0.85 && "walkDown" in @animations){ // monster goes down
					@runAnimation("walkDown")
					@flipX = false
				}else{ // monster goes left or right
					@runAnimation("walkRight");
					@flipX = dx < 0
				}
			}
			
			runAnimation = function(name, onComplete){ // start needed animation
				if(@curAnimName == name && !onComplete) return; // prevent restarting animation
				@curAnimName = name
				@stopAnimation(@curAnim)
				@curAnim = @animation(@animations[name], onComplete)
			}
			
			move = function(x, y, onComplete){ // move monster to position x,y
				var len = ((@x - x)**2 + (@y - y)**2)**0.5
				@stopTransition(@moveTransition)
				@moveTransition = @transition { // lets use transition to move monster
					x = x, y = y
					duration = len * 10.0 / director.contentWidth
					onComplete = onComplete // call this function on complete
				}
			}
			
			fight = function(other){ // try to fight with other monster
				if(@fighting || other.fighting) return; // skip if monster is already fighting
				var side = @x < other.x ? -1 : 1
				var cx = (@x + other.x) / 2
				var cy = (@y + other.y) / 2
				
				@fighting = other
				@move(cx + @width/2*side, cy, @startFightingAnimation) // move monster to fighting position
				
				other.fighting = this
				other.move(cx - other.width/2*side, cy, other.startFightingAnimation) // move other monster to fighting position
			}
			
			startFightingAnimation = function(){ // start fighting
				@health > 0 || return; // skip if monster is dead
				@flipX = @x > @fighting.x // determine side of monster
				@runAnimation("fightRight", function(){ // run fighting animations
					@fighting.health = @fighting.health - @health * 0.3 // make damage to other monster
					// @fighting.timeSpeed = math.max(0.7, @fighting.timeSpeed * 0.8) // damaged monster is tired, so make him slow down
					if(@fighting.health <= 0){ // check if other monster is dead
						@fighting.die() // start die animations
						@fighting = null
						// go away a bit when the fight is finished
						@move(@x + math.random(-1, 1) * @width, @y + math.random(-1, 1) * @width)
					}
				})
			}
			
			die = function(){ // start dying animations
				@clearTimeout(@trackMove) // remove @trackMove timeout functions
				@stopTransition(@moveTransition) // stop moving animations
				@flipX = @x > @fighting.x // determine side
				@timeSpeed = 1 // reset time speed to 1
				@runAnimation("dieRight", function(){ // run dying animations
					@stopAnimation(@curAnim)
					@curAnim = null
					@transition { // start fade out transition
						opacity = 0
						duration = 1
						onComplete = function(){
							@remove() // remove monster on the fade out transition completed
						}
					}
				})
			}
			
			__set@y = function(y){ // track changing y position
				super(y) // call the same method of "super" class because we want to add behavior, not override
				@zOrder = y // set zOrder, so bottom monsters will be front of top monsters
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
		
		@addEventListener("touch", function(touch){
			moveMonsters(touch.local.x, touch.local.y)
		})
		
		@setTimeout(function(){ // set new timeout function to check monsters crossed
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
		
		addStats(this)
	}
}

director.scene = MyScene()	// create and set our game scene
