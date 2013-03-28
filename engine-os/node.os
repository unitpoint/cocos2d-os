// require("utils")

Node = extends FunctionNode {
	__object = {
		visible = true,
		modal = false,
		opacity = 1,
		color = null,
		
		__isRelativeAnchor = true,
		__x = 0,
		__y = 0,
		__width = 0,
		__height = 0,
		__scaleX = 1,
		__scaleY = 1,
		__skewX = 0,
		__skewY = 0,
		__anchorX = 0.5,
		__anchorY = 0.5,
		__rotation = 0,
		
		__transformDirty = true,
		__transform = null, // node to parent
		__inverseDirty = true,
		__inverseTransform = null, // parent to node
		__transformGL = null, // node to parent (GL)
	},
	
	__get@x = {||@__x},
	__set@x = {|a| if(@__x != a){ @__x = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@y = {||@__y},
	__set@y = {|a| if(@__y != a){ @__y = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@position = {|| Point(@__x, @__y)},
	__set@position = {|a| @x, @y = a.x, a.y },
	
	__get@width = {||@__width},
	__set@width = {|a| if(@__width != a){ @__width = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@height = {||@__height},
	__set@height = {|a| if(@__height != a){ @__height = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@scaleX = {||@__scaleX},
	__set@scaleX = {|a| if(@__scaleX != a){ @__scaleX = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@scaleY = {||@__scaleY},
	__set@scaleY = {|a| if(@__scaleY != a){ @__scaleY = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@scale = {||@__scaleX}, // Point(@__scaleX, @__scaleY)},
	__set@scale = {|a| 
		if(numberOf(a)){
			@scaleX, @scaleY = a, a
		}else{
			@scaleX, @scaleY = a.x, a.y 
		}
	},
	
	__get@skewX = {|| @__skewX },
	__set@skewX = {|a| if(@__skewX != a){ @__skewX = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@skewY = {||@__skewY},
	__set@skewY = {|a| if(@__skewY != a){ @__skewY = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@skew = {||Point(@__skewX, @__skewY)},
	__set@skew = {|a| @skewX, @skewY = a.x, a.y },
	
	__get@anchorX = {||@__anchorX},
	__set@anchorX = {|a| if(@__anchorX != a){ @__anchorX = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@anchorY = {||@__anchorY},
	__set@anchorY = {|a| if(@__anchorY != a){ @__anchorY = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@anchor = {|| Point(@__anchorX, @__anchorY)},
	__set@anchor = {|a| 
		if(arrayOf(a)){
			@anchorX, @anchorY = a[0], a[1]
		}else{
			@anchorX, @anchorY = a.x, a.y 
		}
	},
	
	__get@rotation = {||@__rotation},
	__set@rotation = {|a| if(@__rotation != a){ @__rotation = a; @__transformDirty = @__inverseDirty = true }},
	
	__get@isRelativeAnchor = {||@__isRelativeAnchor},
	__set@isRelativeAnchor = {|a| if(@__isRelativeAnchor != a){ @__isRelativeAnchor = a; @__transformDirty = @__inverseDirty = true }},
	
	__construct = function(){
		super()
		@width = director.contentWidth
		@height = director.contentHeight
		// printf("node %s: %s, %s\n", @prototype.name, @width, @height)
	},
	
	paint = function(){},
	
	nodeToParentTransform = function(){
		if(@__transformDirty){
			var t = Matrix()
			var anchorX, anchorY
			if(@__anchorX != 0 || @__anchorY != 0){
				anchorX = @__anchorX * @__width
				anchorY = @__anchorY * @__height
			}
			if(anchorX && !@__isRelativeAnchor){
				t = t.translate(anchorX, anchorY)
			}
			if(@__x != 0 || @__y != 0){
				t = t.translate(@__x, @__y)
			}
			if(@__rotation != 0){
				t = t.rotate(@__rotation)
			}
			if(@__skewX != 0 || @__skewY != 0){
				t = t.skew(@__skewX, @__skewY)
			}
			if(@__scaleX != 0 || @__scaleY != 0){
				t = t.scale(@__scaleX, @__scaleY)
			}
			if(anchorX){
				t = t.translate(-anchorX, -anchorY)
			}
			@__transform = t
			@__transformGL = t.toGL()
			@__transformDirty = false
		}
		return @__transform
	},
	
	parentToNodeTransform = function(){
		if(@__inverseDirty){
			@__inverseTransform = @nodeToParentTransform().clone().inverse()
			@__inverseDirty = false
		}
	},
	
	nodeToWorldTransform = function(){
		// t could be changed so clone it
		var t = @nodeToParentTransform().clone()
		for(var p = @__parent; p;){
			t = t.mult( p.nodeToParentTransform() )
			p = p.__parent
		}
		// print "nodeToWorldTransform"..t
		return t
	},
	
	worldToNodeTransform = function(){
		return @nodeToWorldTransform().inverse()
	},
	
	pointToNodeSpace = function(point){
		return @worldToNodeTransform().transform(point)
	},
	
	isLocalPoint = function(point){
		return point.x >= 0 && point.x < @__width 
			&& point.y >= 0 && point.y < @__height
	},
	
	transform = function(){
		@nodeToParentTransform()
		glMultMatrix(@__transformGL)
	},
	
	handlePaint = function(params){
		@visible || return;
		
		var saveOpacity = params.opacity
		params.opacity = params.opacity * @opacity
		
		glPushMatrix()
		@transform()
		
		for(var child in @__childrenNeg.reverseIter()){
			child.handlePaint(params)
		}
		
		@paint(params)
		if("paint" in @__events){
			// params.target = this
			for(var func in @__events.paint){
				func.call(this, params)
			}
		}
		
		for(var child in @__childrenPos.reverseIter()){
			child.handlePaint(params)
		}
		
		glPopMatrix()
		
		params.opacity = saveOpacity
	},
	
	handleKeyEvent = function(event){
		// @triggerEvent("key", event)
		if(event.captured !== this){
			for(var child in @__childrenPos){
				child.handleKeyEvent(event) && return true;
			}
		}
		if("key" in @__events){
			for(var func in @__events.key){
				func.call(this, event)
			}
		}
		if(event.captured !== this){
			for(var child in @__childrenNeg){
				child.handleKeyEvent(event) && return true;
			}
		}
		if(!event.captured && @modal){
			event.captured = this
			event.modal = true
			return true
		}
		return false
	},
	
	handleTouch = function(touch){
		if(touch.captured !== this){
			for(var child in @__childrenPos){
				child.handleTouch(touch) && return true;
			}
		}
		if("nativeTouch" in @__events){
			// touch.target = this
			for(var func in @__events.nativeTouch){
				func.call(this, touch)
			}
		}
		var autoCapture
		if("touch" in @__events){
			if(touch.phase == "start"){
				if(!touch.captured){
					// touch.x, touch.y = touch.nativeX, touch.nativeY
					var local = @pointToNodeSpace(touch)
					// echo("touch "touch", local"local", is local "@isLocalPoint(local)"\n")
					if(@isLocalPoint(local)){
						touch.local, autoCapture = local, true
						// print "set autoCapture: "..autoCapture
						// touch.target = this
						for(var func in @__events.touch){
							if(func.call(this, touch) === true){
								print "captured by "..this
								touch.captured = this
								touch.capturedFunc = func
								delete touch.local
								return true
							}
						}
						delete touch.local
						// print "autoCapture active: "..autoCapture
					}
				}
			}else if(touch.captured === this){
				// touch.x, touch.y = touch.nativeX, touch.nativeY
				touch.local = @pointToNodeSpace(touch)
				// touch.target = this
				if(touch.capturedFunc){
					if(touch.capturedFunc in @__events.touch){
						touch.capturedFunc.call(this, touch)
					}
				}else{
					for(var func in @__events.touch){
						func.call(this, touch)
					}
				}
				delete touch.local
				touch.captured && return true;
			}
		}
		if(touch.captured !== this){
			for(var child in @__childrenNeg){
				child.handleTouch(touch) && return true;
			}
		}
		// print "captured at end: "..touch.captured..", "..autoCapture
		if(!touch.captured){
			if(autoCapture){
				touch.captured = this
				// print "autoCapture: "..touch
				return true
			}else if(@modal){
				touch.captured = this
				touch.modal = true
				return true
			}
		}
		return false
	},
	
	setRect = function(x, y, width, height){
		@x = x
		@y = y
		@width = width
		@height = height
	},
	
	drawBB = function(color, fill){
		var points = [
			[0, 0],
			[@width, 0],
			[@width, @height],
			[0, @height],
		]
		glColor(color)
		ccDrawPoly(points, true, fill)
	},
}
