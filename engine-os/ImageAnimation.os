
ImageAnimation = extends FunctionNode {
	__object = {
		frames = [],
		index = 0,
	},

	__construct = function(params, target, onComplete){
		super()
		@target, @onComplete = target, functionOf(onComplete)
		
		if("frames" in params && arrayOf(params.frames)){
			@frames = params.frames.clone()
		}else{
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
							left = frameWidth * x,
							top = frameHeight * y,
							width = frameWidth,
							height = frameHeight,
						}
					}
				}
			}
		}
		@update()
		@setTimeout(@update, params.delay, true)
	},
	
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
	},
}
