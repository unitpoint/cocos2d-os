var director = require("director")

print "Hello World!"

MyScene = extends Scene {
	__construct = function(){
		super()
		
		var bg = Image("bg.jpg")
		bg.x = this.width / 2
		bg.y = this.height / 2
		bg.scale = math.max(this.width / bg.width, this.height / bg.height)
		this.insert(bg)

		var text = Text("Football Starter Kit")
		text.anchor = {x=1.05 y=1.05}
		text.x = this.width
		text.y = this.height
		text.shadow = true
		text.zOrder = 1
		this.insert(text)
		
		var Ball = extends Image {
			__construct = function(imageFilename){
				super(imageFilename || "ball.png")

				var screenWidth, screen = director.width, director.height
				var speedX, speedY = math.random(-0.5, 0.5)*screenWidth, math.random(0.5, 1)*screenWidth
				var prevX, prevY = 0, 0
				var function trackVelocity(params){
					speedX = (this.x - prevX) / params.deltaTime
					speedY = (this.y - prevY) / params.deltaTime
					prevX, prevY = this.x, this.y
				}
				
				var friction, gravity = 0.9, 9
				var function physUpdate(params){
					var parentWidth, parentHeight = this.parent.width, this.parent.height
					var radius = this.width/2
					speedY = speedY + gravity
					this.x = this.x + speedX * params.deltaTime
					this.y = this.y + speedY * params.deltaTime
					if(this.x >= parentWidth - radius){
						this.x = parentWidth - radius
						speedX = speedX * -friction
					}else if(this.x <= radius){
						this.x = radius
						speedX = speedX * -friction
					}
					if(this.y >= parentHeight - radius){
						this.y = parentHeight - radius
						speedY = speedY * -friction
						speedX = speedX * friction
					}else if(this.y <= radius){
						this.y = radius
						speedY = speedY * -friction
					}
				}
				this.addEventListener("enterFrame", physUpdate)
				
				this.addEventListener("touch", function(touch){
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
		for(var i = 0; i < 3; i++){
			var ball = Ball()
			ball.x = this.width * math.random(0.3, 0.7)
			ball.y = this.height * math.random(0.3, 0.5)
			ball.color = colors[ i % #colors ]
			this.insert(ball)
		}
	}
}

director.scene = MyScene()
