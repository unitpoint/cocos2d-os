
Sprite = extends Node {
	__construct = function(filename){
		super()
		@image = Image(filename)
		@width = @image.width
		@height = @image.height
		@image.x = @width * 0.5
		@image.y = @height * 0.5
		@insert(@image, -1)
		delete @color
	},
	
	__get@color = function(){ @image.color },
	__set@color = function(a){ @image.color = a },
	
	__get@flipX = function(){ @image.flipX },
	__set@flipX = function(a){ @image.flipX = a },
	
	__get@flipY = function(){ @image.flipY },
	__set@flipY = function(a){ @image.flipY = a },
	
	animation = function(params, onComplete){
		var self = this
		var anim = @image.animation(params, onComplete && function(anim){
			onComplete.call(self, anim)
		})
		if("rect" in params){
			var rect = params.rect
			@width = @image.width * rect.width
			@height = @image.height * rect.height
			var cx, cy = rect.center.x, rect.center.y
			if("anchor" in rect){
				cx = cx + rect.width * (rect.anchor.x - 0.5)
				cy = cy + rect.height * (rect.anchor.y - 0.5)
			}
			@image.anchorX = cx
			@image.anchorY = cy
		}else{
			@width = @image.width
			@height = @image.height
		}
		@image.x = @width * 0.5
		@image.y = @height * 0.5
		return anim
	},
	
	stopAnimation = function(t){
		@image.stopAnimation(t)
	},
	
	stopAllAnimations = function(){
		@image.stopAllAnimations()
	},
	
	paint = function(params){
		if(CC_SPRITE_DEBUG_DRAW){
			@drawBB([1, 0, 0, 1])
		}
	},
}
