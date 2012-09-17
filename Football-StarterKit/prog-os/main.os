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

		var message = Text("Football Starter Kit")	// create message
		message.x = this.width	// locate the message at right bottom corner
		message.y = this.height
		message.anchor = {x=1.05 y=1.05}
		message.shadow = true	// we want shadow enabled		
		message.zOrder = 1		// use zOrder to put the message at front of balls
		this.insert(message)
		
		// create ball class, extend Image
		var Ball = extends Image {
			__construct = function(imageFilename){
				super(imageFilename || "ball.png") // call constructor of Image class

				// set start speed of the ball
				var screenWidth, screen = director.width, director.height
				var speedX, speedY = math.random(-0.5, 0.5)*screenWidth, math.random(0.5, 1)*screenWidth
				var prevX, prevY = 0, 0
				var function trackVelocity(params){	// track velocity of the ball while dragging
					speedX = (this.x - prevX) / params.deltaTime
					speedY = (this.y - prevY) / params.deltaTime
					prevX, prevY = this.x, this.y
				}
				
				var friction, gravity = 0.9, 9
				var function physUpdate(params){	// main ball physics update function
					var parentWidth, parentHeight = this.parent.width, this.parent.height
					var radius = this.width/2
					speedY = speedY + gravity
					this.x = this.x + speedX * params.deltaTime
					this.y = this.y + speedY * params.deltaTime
					if(this.x >= parentWidth - radius){
						this.x = parentWidth - radius
						speedX = speedX * -friction	// change dir
					}else if(this.x <= radius){
						this.x = radius
						speedX = speedX * -friction	// change dir
					}
					if(this.y >= parentHeight - radius){
						this.y = parentHeight - radius
						speedY = speedY * -friction	// change dir
						speedX = speedX * friction
					}else if(this.y <= radius){
						this.y = radius
						speedY = speedY * -friction	// change dir
					}
				}
				this.addEventListener("enterFrame", physUpdate)	// add physUpdate as enterFrame listener
				
				this.addEventListener("touch", function(touch){	// add touch behavior
					if(touch.phase == "start"){
						this.x0, this.y0 = touch.x - this.x, touch.y - this.y
						this.removeEventListener("enterFrame", physUpdate)
						this.addEventListener("enterFrame", trackVelocity)
					}else if(touch.phase == "move"){
						this.x, this.y = touch.x - this.x0, touch.y - this.y0
					}else if(touch.phase == "end" || touch.phase == "cancel"){
						this.addEventListener("enterFrame", physUpdate)
						this.removeEventListener("enterFrame", trackVelocity)
					}
				})				
			}
		}
		
		var colors = [ [0.9 0.7 0.7], [0.7 0.9 0.7], [0.7 0.7 0.9] ]
		// create our balls as instances of Ball class
		for(var i = 0; i < 3; i++){
			var ball = Ball()	// create instance of Ball class
			ball.x = this.width * math.random(0.3, 0.7)
			ball.y = this.height * math.random(0.3, 0.5)
			ball.color = colors[ i % #colors ]
			this.insert(ball)	// insert the ball to the scene
		}
	}
}

director.scene = MyScene()	// create and set our game scene
