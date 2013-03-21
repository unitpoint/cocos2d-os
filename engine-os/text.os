
Text = extends Node {
	__object = {
		__labelBMFont = null,
		__shadowText = null,
		__shadowColor = [0, 0, 0, 1],
		__shadowOffsX = 1,
		__shadowOffsY = 1,
	},
	
	__construct = {|text, font, width, align|
		super()
		@__labelBMFont = LabelBMFont(text, font, width, align)
		@__width = @__labelBMFont.width
		@__height = @__labelBMFont.height
		@__transformDirty = @__inverseDirty = true
		@__shadowOffsX = @__shadowOffsY = @__labelBMFont.fontHeight * 0.05
		delete @color
	},
	
	__get@shadow = {|| @__shadowText !== null},
	
	__set@shadow = {|a|
		if(a == @shadow) return;
		if(!a){
			@__shadowText.remove()
			@__shadowText = null
		}else{
			@__shadowText = Text(@string, @font, @width, @align).attrs{
				anchor = {x=0, y=0},
				x = @__shadowOffsX,
				y = @__shadowOffsY,
				color = @__shadowColor,
			}.insertTo(this, -1)
		}
	},
	
	__get@color = {|| @__labelBMFont.color },
	__set@color = {|a| @__labelBMFont.color = a },

	__get@fontHeight = {|| @__labelBMFont.fontHeight },
	
	__get@font = {|| @__labelBMFont.font },
	__set@font = {|a| @__labelBMFont.font = a },

	__get@align = {|| @__labelBMFont.align },
	__set@align = {|a| @__labelBMFont.align = a },

	__get@shadowColor = {|| @__shadowColor },
	__set@shadowColor = {|a| @__shadowColor = a },

	__get@shadowOffsX = {|| @__shadowOffsX },
	__set@shadowOffsX = {|a| 
		if(@__shadowOffsX !== a){
			@__shadowOffsX = a
			if(@__shadowText){ 
				@__shadowText.x = @__shadowOffsX
			}
		}
	},

	__get@shadowOffsY = {|| @__shadowOffsY },
	__set@shadowOffsY = {|a| 
		if(@__shadowOffsY !== a){
			@__shadowOffsY = a
			if(@__shadowText){ 
				@__shadowText.y = @__shadowOffsY
			}
		}
	},

	__get@string = {|| @__labelBMFont.string },
	__set@string = {|a| 
		if(@__labelBMFont.string !== a){
			@__labelBMFont.string = a
			@__width = @__labelBMFont.width
			@__height = @__labelBMFont.height
			@__transformDirty = @__inverseDirty = true
			if(@__shadowText){
				@__shadowText.string = a
			}
		}
	},

	__set@width = {|a| 
		if(@__width !== a){
			@__labelBMFont.width = a
			@__width = @__labelBMFont.width
			@__height = @__labelBMFont.height
			@__transformDirty = @__inverseDirty = true
			if(@__shadowText) @__shadowText.width = a
		}
	},
	__set@height = {|a| 
		// nop
	},
	
	paint = {|params|
		app.drawLabelBMFont(@__labelBMFont, params.opacity)
		if(CC_SPRITE_DEBUG_DRAW){
			@drawBB([0, 0, 0, 1])
		}
	},
}
