var app = require("app")
require("utils")

Point = {
	__construct = function(x, y){
		this.x = x
		this.y = y
	}
}

Size = {
	__construct = function(width, height){
		this.width = width
		this.height = height
	}
}

var counter = 0

FunctionNode = {
	__object = {
		time = 0
		timeSpeed = 1
		
		__events = {}
		__childrenNeg = {}
		__childrenPos = {}
		__timers = {}
		__transitions = {}
		__parent = null
		__parentChildren = null
		__zOrder = 0
	}
	
	__get@parent = function(){return this.__parent}
	__set@parent = function(a){
		if(this.__parent !== a){ 
			this.remove() 
			if(a) a.insert(this) 
		}
	}
	
	__get@zOrder = function(){return this.__zOrder}
	__set@zOrder = function(a){
		a = math.ceil(a)
		if(this.__zOrder !== a){ 
			this.__zOrder = a
			if(this.__parent){
				this.__parentChildren[this][0] = a
				this.__parent.sortChildren(this.__parentChildren)
			}
		}
	}
	
	sortChildren = function(children){
		children.rsort(function(a b){
			var z = a[0] - b[0]
			return z != 0 ? z : a[1] - b[1]
		})
	}
	
	insert = function(node, zOrder){
		node.remove()
		
		if(zOrder)
			node.__zOrder = zOrder
		else
			zOrder = node.__zOrder
		
		var children = zOrder < 0 ? this.__childrenNeg : this.__childrenPos
		children[node] = [zOrder ++counter]
		this.sortChildren(children)
		node.__parent = this
		node.__parentChildren = children
		// node.triggerEvent("onEnter")
	}
	
	remove = function(node){
		node = node || this
		if(node.__parent){
			// node.triggerEvent("onExit")
			delete node.__parentChildren[node]
			node.__parent = null
			node.__parentChildren = null
		}
	}
	
	updateAllComponents = function(params){
		this.updateTransitions(params)
		this.updateTimers(params)
		for(var child in this.__childrenPos){
			child.handleUpdate(params)
		}
		if("enterFrame" in this.__events){
			params.target = this
			for(var func in this.__events["enterFrame"]){
				func.call(this params)
			}
		}
		for(var child in this.__childrenNeg){
			child.handleUpdate(params)
		}
	}
	
	handleUpdate = function(params){
		var deltaTime = params.deltaTime
		params.deltaTime = deltaTime * this.timeSpeed
		this.time = this.time + params.deltaTime
		this.updateAllComponents(params)
		params.deltaTime = deltaTime
	}
	
	addEventListener = function(eventName, func, zOrder){
		functionof func || return;
		this.__events[eventName][func] = zOrder || 0
		this.__events[eventName].rsort()
		return [eventName func]
	}
	
	removeEventListener = function(eventId){
		if(arrayof eventId){
			var eventName, func = eventId[0], eventId[1]
			delete this.__events[eventName][func]
		}
	}

	triggerEvent = function(eventName, params){
		for(var child in this.__childrenPos){
			child.triggerEvent(eventName, params)
		}
		if(eventName in this.__events){
			params.target = this
			for(var func in this.__events[eventName]){
				func.call(this params)
			}
		}
		for(var child in this.__childrenNeg){
			child.triggerEvent(eventName, params)
		}
	}
	
	setTimeout = function(func, delay, count, priority){
		count = count || 1
		count > 0 && functionof func || return;
		var i = func
		this.__timers[i] = {
			nextTime = this.time + delay
			delay = delay
			func = func
			count = count
			priority = priority || 0
		}
		this.__timers.rsort "priority"
		return i
	}

	clearTimeout = function(t){
		delete this.__timers[t]
	}
	
	updateTimers = function(){
		var time = this.time
		for(var i, t in this.__timers){
			if(t.nextTime <= time){
				// print "run timer "..t
				t.nextTime = time + t.delay
				if(t.count === true){
					t.func.call(this)
				}else{
					if(t.count <= 1){
						delete this.__timers[i]
					}else{
						t.count = t.count - 1
					}
					t.func.call(this)
				}
			}
		}
	}
	
	updateTransitions = function(params){
		for(var t in this.__transitions){
			t.handleUpdate(params)
		}
	}
	
	transition = function(t target){
		(t in this.__transitions) && return;
		if(!(t is Transition)){
			t = Transition(t)
		}
		t && !t.__parent || return;
		
		var zOrder = 0
		var children = this.__transitions
		children[t] = [zOrder ++counter]
		// this.sortChildren(children)
		t.__parent = this
		t.__parentChildren = children
		t.start(target || this)
	}
	
	stopTransition = function(t){
		t.remove()
	}
	
	stopAllTransitions = function(){
		for(var t in this.__transitions){
			t.remove()
		}
		this.__transitions = {}
	}
}

Node = extends FunctionNode {
	__object = {
		visible = true
		modal = false
		opacity = 1
		
		__isRelativeAnchor = true
		__x = 0
		__y = 0
		__width = 0
		__height = 0
		__scaleX = 1
		__scaleY = 1
		__skewX = 0
		__skewY = 0
		__anchorX = 0.5
		__anchorY = 0.5
		__rotation = 0
		
		__transformDirty = true
		__transform = null // node to parent
		__inverseDirty = true
		__inverseTransform = null // parent to node
		__transformGL = null // node to parent (GL)
	}
	
	__get@x = function(){return this.__x}
	__set@x = function(a){if(this.__x !== a){ this.__x = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@y = function(){return this.__y}
	__set@y = function(a){if(this.__y !== a){ this.__y = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@position = function(){return Point(this.__x this.__y)}
	__set@position = function(a){ this.x, this.y = a.x, a.y }
	
	__get@width = function(){return this.__width}
	__set@width = function(a){if(this.__width !== a){ this.__width = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@height = function(){return this.__height}
	__set@height = function(a){if(this.__height !== a){ this.__height = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@scaleX = function(){return this.__scaleX}
	__set@scaleX = function(a){if(this.__scaleX !== a){ this.__scaleX = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@scaleY = function(){return this.__scaleY}
	__set@scaleY = function(a){if(this.__scaleY !== a){ this.__scaleY = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@scale = function(){return this.__scaleX} // Point(this.__scaleX this.__scaleY)}
	__set@scale = function(a){ 
		if(numberof a){
			this.scaleX, this.scaleY = a, a
		}else{
			this.scaleX, this.scaleY = a.x, a.y 
		}
	}
	
	__get@skewX = function(){return this.__skewX}
	__set@skewX = function(a){if(this.__skewX !== a){ this.__skewX = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@skewY = function(){return this.__skewY}
	__set@skewY = function(a){if(this.__skewY !== a){ this.__skewY = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@skew = function(){return Point(this.__skewX this.__skewY)}
	__set@skew = function(a){ this.skewX, this.skewY = a.x, a.y }
	
	__get@anchorX = function(){return this.__anchorX}
	__set@anchorX = function(a){if(this.__anchorX !== a){ this.__anchorX = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@anchorY = function(){return this.__anchorY}
	__set@anchorY = function(a){if(this.__anchorY !== a){ this.__anchorY = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@anchor = function(){return Point(this.__anchorX this.__anchorY)}
	__set@anchor = function(a){ this.anchorX, this.anchorY = a.x, a.y }
	
	__get@rotation = function(){return this.__rotation}
	__set@rotation = function(a){if(this.__rotation !== a){ this.__rotation = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	__get@isRelativeAnchor = function(){return this.__isRelativeAnchor}
	__set@isRelativeAnchor = function(a){if(this.__isRelativeAnchor !== a){ this.__isRelativeAnchor = a; this.__transformDirty, this.__inverseDirty = true, true }}
	
	// __get@opacity = function(){return this.__opacity}
	// __set@opacity = function(a){this.__opacity = a}
	
	__construct = function(){
		// super.__construct.call(this)
		this.width = director.width
		this.height = director.height
	}
	
	paint = function(){}
	
	nodeToParentTransform = function(){
		if(this.__transformDirty){
			var t = Matrix()
			var anchorX, anchorY
			if(this.__anchorX !== 0 || this.__anchorY !== 0){
				anchorX = this.__anchorX * this.__width
				anchorY = this.__anchorY * this.__height
			}
			if(anchorX && !this.__isRelativeAnchor){
				t = t.translate(anchorX, anchorY)
			}
			if(this.__x !== 0 || this.__y !== 0){
				t = t.translate(this.__x, this.__y)
			}
			if(this.__rotation !== 0){
				t = t.rotate(this.__rotation)
			}
			if(this.__skewX !== 0 || this.__skewY !== 0){
				t = t.skew(this.__skewX, this.__skewY)
			}
			if(this.__scaleX !== 0 || this.__scaleY !== 0){
				t = t.scale(this.__scaleX, this.__scaleY)
			}
			if(anchorX){
				t = t.translate(-anchorX, -anchorY)
			}
			this.__transform = t
			this.__transformGL = t.toGL()
			this.__transformDirty = false
		}
		return this.__transform
	}
	
	parentToNodeTransform = function(){
		if(this.__inverseDirty){
			this.__inverseTransform = (clone this.nodeToParentTransform()).inverse()
			this.__inverseDirty = false
		}
	}
	
	nodeToWorldTransform = function(){
		// t could be changed so clone it
		var t = clone this.nodeToParentTransform()
		for(var p = this.__parent; p;){
			t = t.mult( p.nodeToParentTransform() )
			p = p.__parent
		}
		// print "nodeToWorldTransform"..t
		return t
	}
	
	worldToNodeTransform = function(){
		return this.nodeToWorldTransform().inverse()
	}
	
	pointToNodeSpace = function(point){
		return this.worldToNodeTransform().transform(point)
	}
	
	isLocalPoint = function(point){
		return point.x >= 0 && point.x < this.__width 
			&& point.y >= 0 && point.y < this.__height
	}
	
	transform = function(){
		this.nodeToParentTransform()
		glMultMatrix(this.__transformGL)
	}
	
	handlePaint = function(params){
		this.visible || return;
		
		var saveOpacity = params.opacity
		params.opacity = params.opacity * this.opacity
		
		glPushMatrix()
		this.transform()
		
		for(var child in this.__childrenNeg.reverseIter()){
			child.handlePaint(params)
		}
		
		this.paint(params)
		if("paint" in this.__events){
			params.target = this
			for(var func in this.__events["paint"]){
				func.call(this params)
			}
		}
		
		for(var child in this.__childrenPos.reverseIter()){
			child.handlePaint(params)
		}
		
		glPopMatrix()
		
		params.opacity = saveOpacity
	}
	
	handleTouch = function(touch){
		for(var child in this.__childrenPos){
			child.handleTouch(touch)
			if(touch.captured) return;
		}
		if("nativeTouch" in this.__events){
			touch.target = this
			for(var func in this.__events["nativeTouch"]){
				func.call(this touch)
				if(touch.captured) return;
			}
		}
		var autoCapture
		if("touch" in this.__events){
			if(touch.phase == "start"){
				if(!touch.captured){
					// touch.x, touch.y = touch.nativeX, touch.nativeY
					var local = this.pointToNodeSpace(touch)
					// echo("touch "touch", local"local", is local "this.isLocalPoint(local)"\n")
					if(this.isLocalPoint(local)){
						touch.local, touch.target, autoCapture = local, this, true
						for(var func in this.__events["touch"]){
							func.call(this touch)
							if(touch.captured){ 
								delete touch.local
								return
							}
						}
						delete touch.local
					}
				}
			}else if(touch.captured === this){
				// touch.x, touch.y = touch.nativeX, touch.nativeY
				touch.local, touch.target = this.pointToNodeSpace(touch), this
				for(var func in this.__events["touch"]){
					func.call(this touch)
					if(touch.captured){ 
						delete touch.local
						return
					}
				}
				delete touch.local
			}
		}
		for(var child in this.__childrenNeg){
			child.handleTouch(touch)
			if(touch.captured) return;
		}
		if(!touch.captured){
			if(autoCapture)
				touch.captured = this
			else if(this.modal){
				touch.captured = this
				touch.modal = true
			}
		}
	}
	
	setRect = function(x y width height){
		this.x = x
		this.y = y
		this.width = width
		this.height = height
	}
}

Transition = extends FunctionNode {
	__construct = function(transition){
		// super.__construct.call(this)
		this.transition = transition
	}
	
	start = function(target){
		var transition = this.transition
		if("speed" in transition){
			this.timeSpeed = transition.speed
			delete transition.speed
		}
		var function update(){
			var duration = transition.duration
			delete transition.duration
			
			var easy
			if("easy" in transition){
				easy = functionof transition.easy
				delete transition.easy
			}
			
			var startValues = {}
			for(var name, value in transition){
				if(value is Transition){
					delete transition[name]
					// this.transition(value, target)
					continue
				}
				if(name === "sequence"){
					
				}
				if(numberof value && name in target && numberof target[name]){
					startValues[name] = target[name]
				}else{
					delete transition[name]
				}
			}
			
			if(duration <= 0){
				// this.setTimeout(function(){
					for(var name, endValue in transition){
						target[name] = endValue
					}
					this.remove()
				// })
				return
			}
			this.time = 0
			this.timeSpeed = this.timeSpeed / duration
			
			// easy = function(a){ return a }
			if(easy){
				var updateAllComponents = this.updateAllComponents
				this.updateAllComponents = function(params){
					var saveTime = this.time
					this.time = easy(this.time)
					params.deltaTime = this.time - (saveTime - params.deltaTime)
					updateAllComponents.call(this, params)
					this.time = saveTime
				}
			}
			
			var listener = this.addEventListener("enterFrame", function(){
				var t = this.time
				if(t >= 1){ 
					t = 1
					// print("transition ended")
					// this.removeEventListener(listener)
					this.remove()
				}else{
					// print("transition progress", math.round((time - start) * 100 / duration).."%")
				}
				for(var name, endValue in transition){
					target[name] = startValues[name] * (1 - t) + endValue * t
					// print(name" --> "target[name])
				}
			}, true)
		}
		if("delay" in transition){
			this.setTimeout(update, transition.delay)
			delete transition.delay
		}else{
			update.call(this)
		}
	}
}

ColorNode = extends Node {
	__object = {
		color: [0.5 0.7 0.5 1]
	}
	
	paint = function(){
		// print "RectNode.paint "..this
		var points = [
			/*
			[this.x this.y], 
			[this.x + this.width this.y],
			[this.x + this.width this.y + this.height], 
			[this.x this.y + this.height],
			*/
			[0 0], 
			[this.width 0],
			[this.width this.height], 
			[0 this.height],
		];
		glColor(this.color)
		ccDrawPoly(points 4 true)
	}
}

Scene = extends Node {
	__object = {
		__isRelativeAnchor = false
		// __anchorX = 0
		// __anchorY = 0
	}
}