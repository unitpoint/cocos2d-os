
Image = extends Node {
	__object = {
		texture = null,
		frameLeft = 0,
		frameTop = 0,
		frameWidth = 0,
		frameHeight = 0,
		flipX = false,
		flipY = false,
	},
	__construct = function(t){
		@texture = t is Texture2d ? t : Texture2d(t)
		@frameWidth = @texture.width
		@frameHeight = @texture.height
		@width = @frameWidth
		@height = @frameHeight
	},
	
	paint = function(params){
		app.drawImage(this, params.opacity)
		if(CC_SPRITE_DEBUG_DRAW){
			@drawBB([0, 0, 0, 1])
		}
	},
	
	animation = function(t, onComplete){
		return @insert(ImageAnimation(t, this, onComplete))
	},
	
	stopAnimation = function(t){
		t && t.remove()
	},
	
	stopAllAnimations = function(){
		@removeAllInstancesOf(ImageAnimation)
	},
}
