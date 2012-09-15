
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
	
	animation = function(t){
		return this.insert(ImageAnimation(t, this))
	}
	
	stopAnimation = function(t){
		t.remove()
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

	__construct = function(params, target){
		super()
		this.target = target
		var cols, rows, start, count = params.cols, params.rows, params.start, params.frames
		
		var frameWidth, frameHeight = target.texture.width / cols, target.texture.height / rows
		var end = start + (count < 0 ? cols * rows : count) - 1
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
		target.frameLeft = frame.left
		target.frameTop = frame.top
		target.frameWidth = frame.width
		target.frameHeight = frame.height
		target.width = frame.width
		target.height = frame.height
	}
}
