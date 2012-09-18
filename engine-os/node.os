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
		a = math.round(a)
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
		
		if(zOrder){
			zOrder = math.round(zOrder)
			node.__zOrder = zOrder
		}else
			zOrder = node.__zOrder
		
		var children = zOrder < 0 ? this.__childrenNeg : this.__childrenPos
		children[node] = [zOrder, ++counter]
		this.sortChildren(children)
		node.__parent = this
		node.__parentChildren = children
		node.triggerEvent("onEnter")
		return node
	}
	
	remove = function(node){
		node = node || this
		if(node.__parent){
			node.triggerEvent("onExit")
			delete node.__parentChildren[node]
			node.__parent = null
			node.__parentChildren = null
		}
	}
	
	handleUpdate = function(params){
		var deltaTime = params.deltaTime
		params.deltaTime = deltaTime * this.timeSpeed
		this.time = this.time + params.deltaTime
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
		params.deltaTime = deltaTime
	}
	
	handlePaint = function(){}
	handleTouch = function(){}
	
	addEventListener = function(eventName, func, zOrder){
		functionof func || return;
		this.__events[eventName][func] = zOrder || 0
		this.__events[eventName].rsort()
		return [eventName func]
	}
	
	removeEventListener = function(eventName, func){
		if(arrayof eventName){
			eventName, func = eventName[0], eventName[1]
		}
		if(eventName in this.__events){
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
				func.call(this, params)
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

	transition = function(t){
		return this.insert(Transition(t, this))
	}
	
	stopTransition = function(t){
		t.remove()
	}
	
	stopAllTransitions = function(){
		this.removeAllInstancesOf(Transition)
	}
	
	removeAllInstancesOf = function(type){
		for(var t in this.__childrenPos){
			if(t is type)
				t.remove()
		}
		for(var t in this.__childrenNeg){
			if(t is type)
				t.remove()
		}
	}
}

Node = extends FunctionNode {
	__object = {
		visible = true
		modal = false
		opacity = 1
		color = null
		
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
	
	__construct = function(){
		super()
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
				func.call(this, params)
			}
		}
		
		for(var child in this.__childrenPos.reverseIter()){
			child.handlePaint(params)
		}
		
		glPopMatrix()
		
		params.opacity = saveOpacity
	}
	
	handleTouch = function(touch){
		if(touch.captured !== this){
			for(var child in this.__childrenPos){
				child.handleTouch(touch) && return true;
			}
		}
		if("nativeTouch" in this.__events){
			touch.target = this
			for(var func in this.__events["nativeTouch"]){
				func.call(this touch)
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
							if(func.call(this, touch) === true){
								touch.captured = this
								touch.capturedFunc = func
								delete touch.local
								return true
							}
						}
						delete touch.local
					}
				}
			}else if(touch.captured === this){
				// touch.x, touch.y = touch.nativeX, touch.nativeY
				touch.local, touch.target = this.pointToNodeSpace(touch), this
				if(touch.capturedFunc){
					if(touch.capturedFunc in this.__events["touch"]){
						touch.capturedFunc.call(this, touch)
					}
				}else{
					for(var func in this.__events["touch"]){
						func.call(this, touch)
					}
				}
				delete touch.local
				touch.captured && return true;
			}
		}
		if(touch.captured !== this){
			for(var child in this.__childrenNeg){
				child.handleTouch(touch) && return true;
			}
		}
		if(!touch.captured){
			if(autoCapture){
				touch.captured = this
				return true
			}else if(this.modal){
				touch.captured = this
				touch.modal = true
				return true
			}
		}
		return false
	}
	
	setRect = function(x y width height){
		this.x = x
		this.y = y
		this.width = width
		this.height = height
	}
	
	drawBB = function(color, fill){
		var points = [
			[0, 0],
			[this.width, 0],
			[this.width, this.height],
			[0, this.height],
		]
		glColor(color)
		ccDrawPoly(points, true, fill)
	}
}

Transition = extends FunctionNode {
	__object = {
		duration = 0
		list = []
		finished = false
	}

	__construct = function(params, target){
		super()
		this.target = target
		var t = this.calculateTransition(this.list, params, 0, 1)
		this.duration = t.endTime
		// print "calculateTransition "..this.list
		this.addEventListener("enterFrame", this.update, true)
	}
	
	calculateTransition = function(list, params, startTime, speed){
		var t = {}
		var delay = 0
		if("delay" in params){
			delay = math.max(0, params.delay)
			delete params.delay
		}
		var duration = 0
		if("duration" in params){
			duration = math.max(0, params.duration)
			delete params.duration
		}
		if("speed" in params){
			speed = speed * params.speed
			delete params.speed
		}
		if(speed > 0){
			duration = duration / speed
			delay = delay / speed
		}else{
			duration, delay = 0, 0
		}
		t.easy = null
		if("easy" in params){
			t.easy = functionof params.easy
			delete params.easy
		}
		t.repeat = 1
		if("repeat" in params){
			t.repeat = params.repeat
			delete params.repeat
		}
		t.infinite = t.repeat === true
		t.repeat = math.max(0, numberof t.repeat)

		t.alignRotation = false
		if("alignRotation" in params){
			t.alignRotation = params.alignRotation
			delete params.alignRotation
		}
		
		// t.duration = duration
		t.startTime = startTime
		t.startTransitionTime = startTime + delay
		t.endTime = t.startTransitionTime + duration
		list.push(t)
		
		t.startValues = null
		t.endValues = {}
		t.subTransitions = []
		for(var name, value in params){
			if(name === "sequence"){
				// delete params[name]
				var sequenceStartTime = t.startTransitionTime
				var closed = false
				if("closed" in value){
					closed = value.closed
					delete value.closed
					if(closed){
						value.push(clone value[0])
					}
				}
				var alignRotation = t.alignRotation
				if("alignRotation" in value){
					alignRotation = value.alignRotation
					delete value.alignRotation
				}
				for(var i, sub in value){
					if(objectof sub){
						sub.alignRotation = alignRotation
						sub = this.calculateTransition(t.subTransitions, sub, sequenceStartTime, speed)
						sequenceStartTime = sub.endTime
						t.endTime = math.max(t.endTime, sub.endTime)
					}
				}
				continue
			}
			if(name === "spawn"){
				// delete params[name]
				var alignRotation = t.alignRotation
				if("alignRotation" in value){
					alignRotation = value.alignRotation
					delete value.alignRotation
				}
				for(var i, sub in value){
					if(objectof sub){
						sub.alignRotation = alignRotation
						sub = this.calculateTransition(t.subTransitions, sub, t.startTransitionTime, speed)
						t.endTime = math.max(t.endTime, sub.endTime)
					}
				}
				continue
			}
			if(name == "endValues"){
				// delete params[name]
				continue
			}
			// delete t[name]
			t.endValues[name] = value
		}
		t.endTransitionTime = t.endTime
		if(t.infinite){
			t.endTime = math.MAX_NUMBER
		}else{
			t.endTime = t.startTime + (t.endTime - t.startTime) * t.repeat
		}
		if(#t.subTransitions == 0){
			t.subTransitions = null
		}
		return t
	}
	
	update = function(){
		var time, duration = this.time, this.duration
		if(time >= duration){
			// this.addEventListener("enterFrame", function(){
				this.remove()
				this.finished = true
				// print("transition finished", time, duration)
			// })
			time = duration
		}
		this.applyTimeToList(time, this.list)
	}
	
	applyTimeToList = function(time, list){
		var prev
		for(var i, t in list){
			this.applyTimeToItem(time, t, prev)
			prev = t.endValues
		}
	}
	
	applyTimeToItem = function(time, t, prev){
		if(time < t.startTransitionTime){
			return
		}
		if(!t.infinite && time > t.endTime){
			return
		}
		// print("applyTimeToItem time OK", t.startTransitionTime, time, t.endTime)
		var target = this.target
		if(!t.startValues){
			t.startValues = {}
			for(var name, value in t.endValues){
				if(numberof value && name in target && numberof target[name]){
					t.startValues[name] = name in prev ? prev[name] : target[name]
				}else{
					delete t.endValues[name]
				}
			}
			if(t.alignRotation && "rotation" in t.endValues){
				var start = t.startValues.rotation
				var end = t.endValues.rotation
				var diff = end - start
				if(math.abs(diff) > 180){
					if(diff < 0){
						diff = 360 + diff - math.floor(diff / 360) * 360
					}else if(diff > 360){
						diff = diff - math.floor(diff / 360) * 360
					}
					if(diff > 180){
						diff = diff - 360
					}
					t.endValues.rotation = start + diff
				}
			}
			// print("startValues "..t.startValues, "endValues "..t.endValues)
		}
		var tween
		var duration = t.endTransitionTime - t.startTransitionTime
		if(this.finished)
			time = time - t.startTransitionTime
		else
			time = math.fmod(time - t.startTransitionTime,  duration)
		// print "frame time "..time
		if(duration <= 0){ // || time >= duration){
			tween = 1
		}else if(t.easy){
			tween = t.easy(time / duration)
			time = tween * duration
		}else{
			tween = time / duration
		}
		for(var name, endValue in t.endValues){
			target[name] = t.startValues[name] * (1 - tween) + endValue * tween
			// print(name.." --> "..target[name], "start value "..t.startValues[name], "end "..endValue, "tween "..tween)
		}
		if(t.subTransitions)
			this.applyTimeToList(time + t.startTransitionTime, t.subTransitions)
	}
}

ColorNode = extends Node {
	__object = {
		color: [0.5 0.7 0.5 1]
	}
	
	paint = function(){
		this.drawBB(this.color, true)
	}
}

Scene = extends Node {
	__object = {
		__isRelativeAnchor = false
		// __anchorX = 0
		// __anchorY = 0
	}
}