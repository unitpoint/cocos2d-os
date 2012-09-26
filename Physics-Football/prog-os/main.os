var director = require("director")
var physics = require("physics")

print "Hello World!" // please see all printed messages here: assets-ram/output.txt

MyScene = extends Scene {
	__construct = function(){
		super() // call constructor of class we extend
		
		var bg = Image("bg.jpg") 	// create background image
		bg.x = this.width / 2		// locate it at center of scene 
		bg.y = this.height / 2
		bg.scale = math.max(this.width / bg.width, this.height / bg.height)
		this.insert(bg)				// insert the background image to the scene

		var bounce = 0.9
		var staticWalls = physics.createBody { // make solid static shapes outside of the screen
			type = "static"
			fixture = {
				shapes = [ 
					physics.getBoxShapeVertices([0, director.height], [director.width, director.height*0.1]),
					physics.getBoxShapeVertices([0, director.height*-0.1], [director.width, director.height*0.1]),
					physics.getBoxShapeVertices([director.width*-0.1, 0], [director.width*0.1, director.height]),
					physics.getBoxShapeVertices([director.width, 0], [director.width*0.1, director.height]),
				],
				bounce = bounce
			}
		}
			
		// create ball class, extend Image
		var Ball = extends Image {
			__construct = function(imageFilename){
				super(imageFilename || "ball.png") // call constructor of Image class

				var body = this.addPhysicsBody { // add physics body to the ball
					type = "dynamic"
					fixture = {
						radius = this.width/2
						bounce = bounce
					}
				}
				// set initial angular velocity
				body.angularVelocity = math.rad(math.random(-720, 720))
				// set initial linear velocity
				body.linearVelocity = [director.width * math.random(-1, 1), director.width * math.random(-1, 1)]
						
				// set start speed of the ball
				var speedX, speedY, prevX, prevY = 0, 0, 0, 0
				var function trackVelocity(params){	// track velocity while dragging
					speedX = (this.x - prevX) / params.deltaTime
					speedY = (this.y - prevY) / params.deltaTime
					prevX, prevY = this.x, this.y
					body.linearVelocity = [0, 0] // clear linearVelocity while dragging
					body.gravityScale = 0 // clear gravityScale while dragging
				}
				
				this.addEventListener("touch", function(touch){	// add touch behavior
					if(touch.phase == "start"){
						this.x0, this.y0 = touch.x - this.x, touch.y - this.y
						this.addEventListener("enterFrame", trackVelocity)
					}else if(touch.phase == "move"){
						this.x, this.y = touch.x - this.x0, touch.y - this.y0
					}else if(touch.phase == "end" || touch.phase == "cancel"){
						body.linearVelocity = [speedX, speedY] // set speed after dragging
						body.gravityScale = 1 // reset gravityScale to 1
						body.isAwake = true // don't allow body to sleep after dragging
						this.removeEventListener("enterFrame", trackVelocity)
					}
				})				
			}
		}
		
		var colors = [ [0.9 0.7 0.7], [0.7 0.9 0.7], [0.7 0.7 0.9] ]
		// create our balls as instances of Ball class
		for(var i = 0; i < 3; i++){
			var ball = Ball()	// create instance of Ball class
			ball.x = this.width * math.random(0.2, 0.8)
			ball.y = this.height * math.random(0.2, 0.5)
			ball.color = colors[ i % #colors ]
			this.insert(ball)	// insert the ball to the scene
		}
		// add several boxes
		for(var i = 0; i < 2; i++){
			var box = Image("box.jpg") // add box
			box.x = this.width * math.random(0.2, 0.8)
			box.y = this.height * math.random(0.2, 0.5)
			box.color = colors[ i % #colors ]
			this.insert(box) // insert box to the scene
			var body = box.addPhysicsBody { // add physics body to the box
				type = "dynamic"
				fixture = {
					shape = physics.getBoxShapeVertices([-box.width/2, -box.height/2], [box.width, box.height])
					bounce = 0.95
				}
			}
			// set initial angular velocity
			body.angularVelocity = math.rad(math.random(-720, 720))
			// set initial linear velocity
			body.linearVelocity = [director.width * math.random(-1, 1), director.width * math.random(-1, 1)]
		}
		
		var message = Text("Physics Football")	// create message
		message.x = this.width	// locate the message at right bottom corner
		message.y = this.height
		message.anchor = {x=1.05 y=1.05}
		message.shadow = true	// we want shadow enabled		
		message.zOrder = 1		// use zOrder to put the message at front of balls
		this.insert(message)		
	}
}

director.scene = MyScene()	// create and set our game scene
