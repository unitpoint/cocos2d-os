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
		
		var base = Image("base.png") // create base of fan
		base.anchor = {x=0.5 y=0.95} // we want to use this anchor
		base.x, base.y = 0, this.height // locate the base at left bottom corner
		base.rotation = 45 // rotate it to 45 deg
		this.insert(base)
		
		var fan = Image("fan.png") // create the fan
		fan.x, fan.y = base.width/2, base.height*0.05 // locate it at top of the base
		base.insert(fan) // insert the fan to the base
		
		// you can call function with one argument without using brackets
		// so it's equal to fan.transition({...})
		fan.transition { // start rotation transition of the fan
			rotation = 360*2 // rotate to 720 degs
			duration = 3.5	 // in 3.5 seconds
			easy = Easy.outBack // use non linear transition
			repeat = true // repeat it forever
		}
		
		base.transition { // start transition of the base
			sequence = { { // describe the transition sequence
					x = this.width	// move the base to x
					y = this.height // move the base to y
					rotation = -45	// rotate to -45 deg
					duration = 2	// in 2 seconds
					easy = Easy.inOutBack // use non linear transition of this part of sequence
				}, {
					x = this.width
					y = 0
					rotation = -135
					duration = 2
					easy = Easy.inOutExpo // use non linear transition of this part of sequence
				}, {
					x = 0
					y = 0
					rotation = -225
					duration = 2
					easy = Easy.outBounce // use non linear transition of this part of sequence
				}, {
					x = base.x
					y = base.y
					rotation = base.rotation
					duration = 2
				}
			},
			alignRotation = true // use auto align rotation, comment this line to view difference
			repeat = true // repeat it forever
		}

		var message = Text("Sequence Transition")	// create message
		message.x = this.width	// locate the message at right bottom corner
		message.y = this.height
		message.anchor = {x=1.05 y=1.05}
		message.shadow = true	// we want shadow enabled		
		this.insert(message)		
	}
}

director.scene = MyScene()	// create and set our game scene
