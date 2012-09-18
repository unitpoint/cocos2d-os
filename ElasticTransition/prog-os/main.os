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
		
		var spring = Image("spring.png")
		spring.anchor = {x=0.05 y=0.5}
		spring.x, spring.y = this.width/2, this.height/2
		spring.addEventListener("touch", function(touch){
			if(touch.phase == "start"){
				if("elasticTransition" in this){
					this.elasticTransition.remove()
					delete this.elasticTransition
				}
				var dx = touch.x - this.x
				var dy = touch.y - this.y
				this.len0 = (dx*dx + dy*dy)**0.5 // sqrt is equal to the power of 0.5
				this.scale0 = this.scale
				this.r0 = math.deg(math.atan2(dy, dx)) - this.rotation
			}else if(touch.phase == "move"){
				var dx = touch.x - this.x
				var dy = touch.y - this.y
				var len = (dx*dx + dy*dy)**0.5
				var rotation = math.deg(math.atan2(dy, dx))
				this.rotation = rotation - this.r0
				this.scaleX = this.scale0 * len / this.len0
			}else{ // end or cancel
				this.elasticTransition = this.transition {
					scaleX = 1
					rotation = math.round(this.rotation / 90) * 90 // snap to angle
					duration = 0.5
					easy = Easy.outBack
				}
			}
		})
		this.insert(spring)

		var message = Text("Elastic Transition")	// create message
		message.x = this.width	// locate the message at right bottom corner
		message.y = this.height
		message.anchor = {x=1.05 y=1.05}
		message.shadow = true	// we want shadow enabled		
		this.insert(message)		
	}
}

director.scene = MyScene()	// create and set our game scene
