
Image = extends Node {
	__object = {
		texture = null
		frameLeft = 0
		frameTop = 0
		frameWidth = 0
		frameHeight = 0
		flipX = false
		flipY = false
	}
	__construct = function(t){
		@texture = t is Texture2d ? t : Texture2d(t)
		@frameWidth = @texture.width
		@frameHeight = @texture.height
		@width = @frameWidth
		@height = @frameHeight
	}
	
	paint = function(params){
		app.drawImage(this, params.opacity)
		if(CC_SPRITE_DEBUG_DRAW){
			@drawBB([0 0 0 1])
		}
	}
	
	animation = function(t, onComplete){
		return @insert(ImageAnimation(t, this, onComplete))
	}
	
	stopAnimation = function(t){
		t && t.remove()
	}
	
	stopAllAnimations = function(){
		@removeAllInstancesOf(ImageAnimation)
	}
}

ImageAnimation = extends FunctionNode {
	__object = {
		frames = []
		index = 0
	}

	__construct = function(params, target, onComplete){
		super()
		@target, @onComplete = target, functionOf(onComplete)
		var cols, rows = params.cols, params.rows
		var start, count = ("start" in params ? params.start : 0), ("frames" in params ? params.frames : cols * rows)
		
		var frameWidth, frameHeight = target.texture.width / cols, target.texture.height / rows
		var end = start + (count || cols * rows) - 1
		var yStart = math.floor(start / cols)
		var yEnd = math.min(rows-1, math.floor(end / cols))
		for(var y = yStart; y <= yEnd; y++){
			for(var x = 0; x < cols; x++){
				var i = y*cols + x
				if(i >= start && i <= end){
					@frames.push {
						left = frameWidth * x
						top = frameHeight * y
						width = frameWidth
						height = frameHeight
					}
				}
			}
		}
		@update()
		@setTimeout(@update, params.delay, true)
	}
	
	update = function(){
		var frame, target = @frames[@index], @target
		@index = (@index + 1) % #@frames
		if(@index == 0 && @onComplete){
			// @setTimeout(function(){
				@onComplete.call(target, this)
			// })
		}
		target.frameLeft = frame.left
		target.frameTop = frame.top
		target.frameWidth = frame.width
		target.frameHeight = frame.height
		target.width = frame.width
		target.height = frame.height
	}
}

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
	}
	
	__get@color = function(){ return @image.color }
	__set@color = function(a){ @image.color = a }
	
	__get@flipX = function(){ return @image.flipX }
	__set@flipX = function(a){ @image.flipX = a }
	
	__get@flipY = function(){ return @image.flipY }
	__set@flipY = function(a){ @image.flipY = a }
	
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
	}
	
	stopAnimation = function(t){
		@image.stopAnimation(t)
	}
	
	stopAllAnimations = function(){
		@image.stopAllAnimations()
	}
	
	paint = function(params){
		if(CC_SPRITE_DEBUG_DRAW){
			@drawBB([1 0 0 1])
		}
	}
}
