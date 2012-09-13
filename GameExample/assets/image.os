
function new(){
	return Function.apply(Image, arguments);
}

Image = extends Node {
	__object = {
		texture = null
		frameX = 0
		frameY = 0
		frameWidth = 0
		frameHeight = 0
		flipX = false
		flipY = false
	}
	__construct = function(filename){
		this.texture = Texture2d(filename)
		this.frameWidth = this.texture.width
		this.frameHeight = this.texture.height
	}
	
	paint = function(params){
		app.drawImage(this, params.opacity)
	}
}