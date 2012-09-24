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

		var animations = {
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
		for(var filename, anim in animations){
			var generalParams = anim.generalParams
			delete anim.generalParams
			for(var animName, params in anim){
				anim[animName] = {}.merge(generalParams, params)
			}
		}
		
		var Monster = extends Sprite {
			__object = {
				curAnimName = ""
				curAnim = null
				moveTransition = null
				prevX = 0
				prevY = 0
				health = 100
				fighting = null
			}
			
			__construct = function(filename){
				filename = filename || "monster-01.png"
				super(filename)
				this.animations = animations[filename]
				this.setTimeout(this.trackMove, 0.1, true)
				this.runAnimation("walkRight")
			}
			
			trackMove = function(){
				if(!this.curAnim || this.fighting) return;
				var dx, dy = this.x - this.prevX, this.y - this.prevY
				this.prevX, this.prevY = this.x, this.y
				var len = (dx*dx + dy*dy)**0.5
				// print("trackMove", dx, dy, len)
				len > 0 || return;
				dx, dy = dx / len, dy / len
				if(dy < -0.85 && "walkUp" in this.animations){
					this.runAnimation("walkUp")
					this.flipX = false
				}else if(dy > 0.85 && "walkDown" in this.animations){
					this.runAnimation("walkDown")
					this.flipX = false
				}else{
					this.runAnimation("walkRight");
					this.flipX = dx < 0
				}
			}
			
			runAnimation = function(name, onComplete){
				if(this.curAnimName == name && !onComplete) return;
				this.curAnimName = name
				this.stopAnimation(this.curAnim)
				this.curAnim = this.animation(this.animations[name], onComplete)
			}
			
			move = function(x, y, onComplete){
				var len = ((this.x - x)**2 + (this.y - y)**2)**0.5
				this.stopTransition(this.moveTransition)
				this.moveTransition = this.transition {
					x = x, y = y
					duration = len * 10.0 / director.width
					onComplete = onComplete
				}
			}
			
			fight = function(other){
				if(this.fighting || other.fighting) return;
				var side = this.x < other.x ? -1 : 1
				var cx = (this.x + other.x) / 2
				var cy = (this.y + other.y) / 2
				
				this.fighting = other
				this.move(cx + this.width/2*side, cy, this.startFightingAnimation)
				
				other.fighting = this
				other.move(cx - other.width/2*side, cy, other.startFightingAnimation)
			}
			
			die = function(){
				this.clearTimeout(this.trackMove)
				this.stopTransition(this.moveTransition)
				this.flipX = this.x > this.fighting.x
				this.timeSpeed = 1
				this.runAnimation("dieRight", function(){
					this.stopAnimation(this.curAnim)
					this.curAnim = null
					this.transition {
						opacity = 0
						duration = 1
						onComplete = function(){
							this.remove()
						}
					}
				})
			}
			
			startFightingAnimation = function(){
				this.health > 0 || return;
				this.flipX = this.x > this.fighting.x
				this.runAnimation("fightRight", function(){
					this.fighting.health = this.fighting.health - this.health * 0.3
					this.fighting.timeSpeed = math.max(0.7, this.fighting.timeSpeed * 0.8)
					if(this.fighting.health <= 0){
						this.fighting.die()
						this.fighting = null
						this.move(this.x + math.random(-1, 1) * this.width, this.y + math.random(-1, 1) * this.width)
					}
				})
			}
			
			__set@y = function(y){
				super(y)
				this.zOrder = y
			}
		}
		
		var function color(){
			return [math.random(0.8, 1), math.random(0.8, 1), math.random(0.8, 1)]
		}
		
		var monsters = []
		var scene = this
		var monsterNames = animations.keys
		var function createMonster(i){
			i = i || math.random(#monsterNames)
			var monster = Monster(monsterNames[ i % #monsterNames ])
			monster.x = scene.width * math.random(0.2, 0.8)
			monster.y = scene.height * math.random(0.2, 0.8)
			monster.timeSpeed = math.random(2.0, 3.0)
			monster.color = color() // colors[ i % #colors ]
			monster.opacity = 0
			monster.transition { opacity = 1, duration = 1 }
			scene.insert(monster)
			monsters.push(monster)
			monster.addEventListener("onExit", function(){
				for(var i, m in monsters){
					if(m === this){
						delete monsters[i]
						createMonster(math.random(#monsterNames))
						return;
					}
				} 
			})
		}
		
		for(var i = 0; i < 20; i++){
			createMonster()
		}
		
		var function moveMonsters(x, y){
			for(var i, monster in monsters){
				if(!monster.fighting) monster.move(x, y)
			}
		}
		
		this.addEventListener("touch", function(touch){
			moveMonsters(touch.local.x, touch.local.y)
		})
		
		this.setTimeout(function(){
			for(var i, monster in monsters){
				if(monster.fighting) continue
				for(var j = i+1; j < #monsters; j++){
					var other = monsters[j]
					var dist = ((monster.x - other.x)**2 + (monster.y - other.y)**2)**0.5
					if(dist < monster.width){
						monster.fight(other)
					}
				}
			}
		}, 0.3, true)
	}
}

director.scene = MyScene()	// create and set our game scene
