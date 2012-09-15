
Text = extends Node {
	__construct = function(text, font, width, align){
		this.labelBMFont = LabelBMFont(text, font, width, align)
		this.__width = this.labelBMFont.width
		this.__height = this.labelBMFont.height
		this.__transformDirty, this.__inverseDirty = true, true
		delete this.color
	}
	
	__get@color = function(){ return this.labelBMFont.color }
	__set@color = function(a){ this.labelBMFont.color = a }

	__get@string = function(){ return this.labelBMFont.string }
	__set@string = function(a){ 
		if(this.labelBMFont.string != a){
			this.labelBMFont.string = a
			this.__width = this.labelBMFont.width
			this.__height = this.labelBMFont.height
			this.__transformDirty, this.__inverseDirty = true, true
		}
	}

	__set@width = function(a){ 
		if(this.__width !== a){
			this.labelBMFont.width = a
			this.__width = this.labelBMFont.width
			this.__height = this.labelBMFont.height
			this.__transformDirty, this.__inverseDirty = true, true
		}
	}
	__set@height = function(a){ 
		// nop
	}
	
	paint = function(params){
		app.drawLabelBMFont(this.labelBMFont, params.opacity)
		if(CC_SPRITE_DEBUG_DRAW){
			this.drawBB([0 0 0 1])
		}
	}	
}
