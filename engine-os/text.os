
Text = extends Node {
	__object = {
		__labelBMFont = null
		__shadowText = null
		__shadowColor = [0 0 0 1]
		__shadowOffsX = 1
		__shadowOffsY = 1
	}
	
	__construct = function(text, font, width, align){
		super()
		this.__labelBMFont = LabelBMFont(text, font, width, align)
		this.__width = this.__labelBMFont.width
		this.__height = this.__labelBMFont.height
		this.__transformDirty, this.__inverseDirty = true, true
		var offs = this.__labelBMFont.fontHeight * 0.05
		this.__shadowOffsX, this.__shadowOffsY = offs, offs
		delete this.color
	}
	
	__get@shadow = function(){
		return this.__shadowText !== null
	}
	
	__set@shadow = function(a){
		if(a == this.shadow) return;
		if(!a){
			this.__shadowText.remove()
			this.__shadowText = null
		}else{
			this.__shadowText = Text(this.string, this.font, this.width, this.align)
			this.__shadowText.anchor = {x=0 y=0}
			this.__shadowText.x = this.__shadowOffsX
			this.__shadowText.y = this.__shadowOffsY
			this.__shadowText.color = this.__shadowColor
			this.insert(this.__shadowText, -1)
		}
	}
	
	__get@color = function(){ return this.__labelBMFont.color }
	__set@color = function(a){ this.__labelBMFont.color = a }

	__get@fontHeight = function(){ return this.__labelBMFont.fontHeight }
	
	__get@font = function(){ return this.__labelBMFont.font }
	__set@font = function(a){ this.__labelBMFont.font = a }

	__get@align = function(){ return this.__labelBMFont.align }
	__set@align = function(a){ this.__labelBMFont.align = a }

	__get@shadowColor = function(){ return this.__shadowColor }
	__set@shadowColor = function(a){ this.__shadowColor = a }

	__get@shadowOffsX = function(){ return this.__shadowOffsX }
	__set@shadowOffsX = function(a){ 
		if(this.__shadowOffsX !== a){
			this.__shadowOffsX = a
			if(this.__shadowText){ 
				this.__shadowText.x = this.__shadowOffsX
			}
		}
	}

	__get@shadowOffsY = function(){ return this.__shadowOffsY }
	__set@shadowOffsY = function(a){ 
		if(this.__shadowOffsY !== a){
			this.__shadowOffsY = a
			if(this.__shadowText){ 
				this.__shadowText.y = this.__shadowOffsY
			}
		}
	}

	__get@string = function(){ return this.__labelBMFont.string }
	__set@string = function(a){ 
		if(this.__labelBMFont.string !== a){
			this.__labelBMFont.string = a
			this.__width = this.__labelBMFont.width
			this.__height = this.__labelBMFont.height
			this.__transformDirty, this.__inverseDirty = true, true
			if(this.__shadowText){
				this.__shadowText.string = a
			}
		}
	}

	__set@width = function(a){ 
		if(this.__width !== a){
			this.__labelBMFont.width = a
			this.__width = this.__labelBMFont.width
			this.__height = this.__labelBMFont.height
			this.__transformDirty, this.__inverseDirty = true, true
			if(this.__shadowText) this.__shadowText.width = a
		}
	}
	__set@height = function(a){ 
		// nop
	}
	
	paint = function(params){
		app.drawLabelBMFont(this.__labelBMFont, params.opacity)
		if(CC_SPRITE_DEBUG_DRAW){
			this.drawBB([0 0 0 1])
		}
	}	
}
