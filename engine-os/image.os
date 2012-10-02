
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
		this.texture = t is Texture2d ? t : Texture2d(t)
		this.frameWidth = this.texture.width
		this.frameHeight = this.texture.height
		this.width = this.frameWidth
		this.height = this.frameHeight
	}
	
	paint = function(params){
		app.drawImage(this, params.opacity)
		if(CC_SPRITE_DEBUG_DRAW){
			this.drawBB([0 0 0 1])
		}
	}
	
	animation = function(t, onComplete){
		return this.insert(ImageAnimation(t, this, onComplete))
	}
	
	stopAnimation = function(t){
		t && t.remove()
	}
	
	stopAllAnimations = function(){
		this.removeAllInstancesOf(ImageAnimation)
	}
}

ImageAnimation = extends FunctionNode {
	__object = {
		frames = []
		index = 0
	}

	__construct = function(params, target, onComplete){
		super()
		this.target, this.onComplete = target, functionof onComplete
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
					this.frames.push {
						left = frameWidth * x
						top = frameHeight * y
						width = frameWidth
						height = frameHeight
					}
				}
			}
		}
		this.update()
		this.setTimeout(this.update, params.delay, true)
	}
	
	update = function(){
		var frame, target = this.frames[this.index], this.target
		this.index = (this.index + 1) % #this.frames
		if(this.index == 0 && this.onComplete){
			// this.setTimeout(function(){
				this.onComplete.call(target, this)
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
		this.image = Image(filename)
		this.width = this.image.width
		this.height = this.image.height
		this.image.x = this.width * 0.5
		this.image.y = this.height * 0.5
		this.insert(this.image, -1)
		delete this.color
	}
	
	__get@color = function(){ return this.image.color }
	__set@color = function(a){ this.image.color = a }
	
	__get@flipX = function(){ return this.image.flipX }
	__set@flipX = function(a){ this.image.flipX = a }
	
	__get@flipY = function(){ return this.image.flipY }
	__set@flipY = function(a){ this.image.flipY = a }
	
	animation = function(params, onComplete){
		var self = this
		var anim = this.image.animation(params, onComplete && function(anim){
			onComplete.call(self, anim)
		})
		if("rect" in params){
			var rect = params.rect
			this.width = this.image.width * rect.width
			this.height = this.image.height * rect.height
			var cx, cy = rect.center.x, rect.center.y
			if("anchor" in rect){
				cx = cx + rect.width * (rect.anchor.x - 0.5)
				cy = cy + rect.height * (rect.anchor.y - 0.5)
			}
			this.image.anchorX = cx
			this.image.anchorY = cy
		}else{
			this.width = this.image.width
			this.height = this.image.height
		}
		this.image.x = this.width * 0.5
		this.image.y = this.height * 0.5
		return anim
	}
	
	stopAnimation = function(t){
		this.image.stopAnimation(t)
	}
	
	stopAllAnimations = function(){
		this.image.stopAllAnimations()
	}
	
	paint = function(params){
		if(CC_SPRITE_DEBUG_DRAW){
			this.drawBB([1 0 0 1])
		}
	}
}
