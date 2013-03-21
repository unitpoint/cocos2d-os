var director = require("director")

print "Hello World!" // please see all printed messages here: assets-ram/output.txt

MyScene = extends Scene {
	__construct = function(){
		super() // call constructor of class we extend
		
		var bg = Image("bg.jpg") 	// create background image
		bg.x = @width / 2		// locate it at center of scene 
		bg.y = @height / 2
		bg.scale = math.max(@width / bg.width, @height / bg.height)
		@insert(bg)				// insert the background image to the scene

		Text("Football Starter Kit").attrs {	// create message
			x = @width,	// locate the message at right bottom corner
			y = @height,
			anchor = {x=1.05, y=1.05},
			shadow = true,	// we want shadow enabled		
			zOrder = 1,		// use zOrder to put the message at front of balls
		}.insertTo(this)
		
		// create ball class, extend Image
		var Ball = extends Image {
			__construct = function(imageFilename){
				super(imageFilename || "ball.png") // call constructor of Image class

				// set start speed of the ball
				var screenWidth, screen = director.contentWidth, director.contentHeight
				var speedX, speedY = math.random(-0.5, 0.5)*screenWidth, math.random(0.5, 1)*screenWidth
				var prevX, prevY = 0, 0
				var function trackVelocity(params){	// track velocity of the ball while dragging
					speedX = (@x - prevX) / params.deltaTime
					speedY = (@y - prevY) / params.deltaTime
					prevX, prevY = @x, @y
				}
				
				var friction, gravity = 0.9, 9
				var function physUpdate(params){	// main ball physics update function
					var parentWidth, parentHeight = @parent.width, @parent.height
					var radius = @width/2
					speedY = speedY + gravity
					@x = @x + speedX * params.deltaTime
					@y = @y + speedY * params.deltaTime
					if(@x >= parentWidth - radius){
						@x = parentWidth - radius
						speedX = speedX * -friction	// change dir
					}else if(@x <= radius){
						@x = radius
						speedX = speedX * -friction	// change dir
					}
					if(@y >= parentHeight - radius){
						@y = parentHeight - radius
						speedY = speedY * -friction	// change dir
						speedX = speedX * friction
					}else if(@y <= radius){
						@y = radius
						speedY = speedY * -friction	// change dir
					}
				}
				@addEventListener("enterFrame", physUpdate)	// add physUpdate as enterFrame listener
				
				@addEventListener("touch", function(touch){	// add touch behavior
					// print "ball touch: "..touch
					if(touch.phase == "start"){
						@x0, @y0 = touch.x - @x, touch.y - @y
						@removeEventListener("enterFrame", physUpdate)
						@addEventListener("enterFrame", trackVelocity)
					}else if(touch.phase == "move"){
						@x, @y = touch.x - @x0, touch.y - @y0
					}else if(touch.phase == "end" || touch.phase == "cancel"){
						@addEventListener("enterFrame", physUpdate)
						@removeEventListener("enterFrame", trackVelocity)
					}
					// return true
				})				
			}
		}
		
		var colors = [ [0.9, 0.7, 0.7], [0.7, 0.9, 0.7], [0.7, 0.7, 0.9] ]
		// create our balls as instances of Ball class
		for(var i = 0; i < 3; i++){
			Ball().attrs {	// create instance of Ball class
				x = @width * math.random(0.3, 0.7),
				y = @height * math.random(0.3, 0.5),
				color = colors[ i % #colors ],
			}.insertTo(this)	// insert the ball to the scene
		}
	}
}

director.scene = MyScene()	// create and set our game scene
