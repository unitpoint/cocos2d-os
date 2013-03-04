require("utils")

Point = {
	__construct = function(x, y){
		@x = x
		@y = y
	}
}

Size = {
	__construct = function(width, height){
		@width = width
		@height = height
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
	
	__get@parent = {||@__parent}
	__set@parent = {|a| 
		if(@__parent !== a){ 
			@remove() 
			a && a.insert(this) 
		}
	}
	
	__get@zOrder = {||@__zOrder}
	__set@zOrder = {|a| 
		a = math.round(a)
		if(@__zOrder != a){ 
			@__zOrder = a
			if(@__parent){
				@__parentChildren[this][0] = a
				@__parent.sortChildren(@__parentChildren)
			}
		}
	}
	
	attrs: function(params){
		for(var field, value in objectOf(params)){
			this[field] = value
		}
		return this
	}
	
	sortChildren = function(children){
		children.sort {|b a|
			var z = a[0] <=> b[0]
			return z != 0 ? z : a[1] <=> b[1]
		}
	}
	
	insert = function(node, zOrder){
		node.remove()
		
		if(zOrder){
			node.__zOrder = zOrder = math.round(zOrder)
		}else
			zOrder = node.__zOrder
		
		var children = zOrder < 0 ? @__childrenNeg : @__childrenPos
		children[node] = [zOrder, ++counter]
		@sortChildren(children)
		node.__parent = this
		node.__parentChildren = children
		node.triggerEvent("onEnter", {sender: node})
		return node
	}
	
	insertTo = function(newParent, zOrder){
		return newParent.insert(this, zOrder)
	}
	
	remove = function(node){
		node = node || this
		if(node.__parent){
			node.triggerEvent("onExit", {sender: node})
			delete node.__parentChildren[node]
			node.__parent = null
			node.__parentChildren = null
		}
	}
	
	removeAll = function(){
		@__childrenNeg, @__childrenPos = {}, {}
	}
	
	contains = function(node){
		return node in @__childrenNeg || node in @__childrenPos
	}
	
	handleUpdate = function(params){
		var deltaTime = params.deltaTime
		params.deltaTime = deltaTime * @timeSpeed
		@time = @time + params.deltaTime
		@updateTimers(params)
		for(var child in @__childrenPos){
			child.handleUpdate(params)
		}
		if("enterFrame" in @__events){
			// params.target = this
			for(var func in @__events.enterFrame){
				func.call(this, params)
			}
		}
		for(var child in @__childrenNeg){
			child.handleUpdate(params)
		}
		params.deltaTime = deltaTime
	}
	
	handlePaint = function(){}
	handleTouch = function(){}
	handleKeyEvent = function(){}
	
	addEventListener = function(eventName, func, zOrder){
		functionOf(func) || return;
		eventName in @__events || @__events[eventName] = {}
		@__events[eventName][func] = zOrder || 0
		@__events[eventName].sort{|b a| a <=> b}
		return [eventName, func]
	}
	
	removeEventListener = function(eventName, func){
		if(arrayOf(eventName)){
			eventName, func = eventName[0], eventName[1]
		}
		if(eventName in @__events){
			delete @__events[eventName][func]
		}
	}

	triggerLocalEvent = function(eventName, params){
		if(eventName in @__events){
			// params.target = this
			for(var func in @__events[eventName]){
				func.call(this, params)
			}
		}
	}
	
	triggerEvent = function(eventName, params){
		for(var child in @__childrenPos){
			child.triggerEvent(eventName, params)
		}
		if(eventName in @__events){
			// params.target = this
			for(var func in @__events[eventName]){
				func.call(this, params)
			}
		}
		for(var child in @__childrenNeg){
			child.triggerEvent(eventName, params)
		}
	}
	
	setTimeout = function(func, delay, count, priority){
		count = count || 1
		count > 0 && functionOf(func) || return;
		@__timers[func] = {
			nextTime = @time + delay
			delay = delay
			count = count
			priority = priority || 0
		}
		@__timers.sort{|b a| a.priority <=> b.priority}
		return func
	}

	clearTimeout = function(t){
		delete @__timers[t]
	}
	
	updateTimers = function(){
		var time = @time
		for(var func, t in @__timers){
			if(t.nextTime <= time){
				// print "run timer "..t
				t.nextTime = time + t.delay
				if(t.count === true){
					func.call(this)
				}else{
					if(t.count <= 1){
						delete @__timers[func]
					}else{
						t.count = t.count - 1
					}
					func.call(this)
				}
			}
		}
	}

	transition = function(t){
		return @insert(Transition(t, this))
	}
	
	stopTransition = function(t){
		t && t.remove()
	}
	
	stopAllTransitions = function(){
		@removeAllInstancesOf(Transition)
	}
	
	removeAllInstancesOf = function(type){
		for(var t in @__childrenPos){
			if(t is type)
				t.remove()
		}
		for(var t in @__childrenNeg){
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
	
	__get@x = {||@__x}
	__set@x = {|a| if(@__x != a){ @__x = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@y = {||@__y}
	__set@y = {|a| if(@__y != a){ @__y = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@position = {|| Point(@__x @__y)}
	__set@position = {|a| @x, @y = a.x, a.y }
	
	__get@width = {||@__width}
	__set@width = {|a| if(@__width != a){ @__width = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@height = {||@__height}
	__set@height = {|a| if(@__height != a){ @__height = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@scaleX = {||@__scaleX}
	__set@scaleX = {|a| if(@__scaleX != a){ @__scaleX = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@scaleY = {||@__scaleY}
	__set@scaleY = {|a| if(@__scaleY != a){ @__scaleY = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@scale = {||@__scaleX} // Point(@__scaleX @__scaleY)}
	__set@scale = {|a| 
		if(numberOf(a)){
			@scaleX, @scaleY = a, a
		}else{
			@scaleX, @scaleY = a.x, a.y 
		}
	}
	
	__get@skewX = {|| @__skewX }
	__set@skewX = {|a| if(@__skewX != a){ @__skewX = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@skewY = {||@__skewY}
	__set@skewY = {|a| if(@__skewY != a){ @__skewY = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@skew = {||Point(@__skewX @__skewY)}
	__set@skew = {|a| @skewX, @skewY = a.x, a.y }
	
	__get@anchorX = {||@__anchorX}
	__set@anchorX = {|a| if(@__anchorX != a){ @__anchorX = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@anchorY = {||@__anchorY}
	__set@anchorY = {|a| if(@__anchorY != a){ @__anchorY = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@anchor = {|| Point(@__anchorX @__anchorY)}
	__set@anchor = {|a| 
		if(arrayOf(a)){
			@anchorX, @anchorY = a[0], a[1]
		}else{
			@anchorX, @anchorY = a.x, a.y 
		}
	}
	
	__get@rotation = {||@__rotation}
	__set@rotation = {|a| if(@__rotation != a){ @__rotation = a; @__transformDirty = @__inverseDirty = true }}
	
	__get@isRelativeAnchor = {||@__isRelativeAnchor}
	__set@isRelativeAnchor = {|a| if(@__isRelativeAnchor != a){ @__isRelativeAnchor = a; @__transformDirty = @__inverseDirty = true }}
	
	__construct = function(){
		super()
		@width = director.contentWidth
		@height = director.contentHeight
		printf("node %s: %s, %s\n", @prototype.name, @width, @height)
	}
	
	paint = function(){}
	
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
	}
	
	parentToNodeTransform = function(){
		if(@__inverseDirty){
			@__inverseTransform = @nodeToParentTransform().clone().inverse()
			@__inverseDirty = false
		}
	}
	
	nodeToWorldTransform = function(){
		// t could be changed so clone it
		var t = @nodeToParentTransform().clone()
		for(var p = @__parent; p;){
			t = t.mult( p.nodeToParentTransform() )
			p = p.__parent
		}
		// print "nodeToWorldTransform"..t
		return t
	}
	
	worldToNodeTransform = function(){
		return @nodeToWorldTransform().inverse()
	}
	
	pointToNodeSpace = function(point){
		return @worldToNodeTransform().transform(point)
	}
	
	isLocalPoint = function(point){
		return point.x >= 0 && point.x < @__width 
			&& point.y >= 0 && point.y < @__height
	}
	
	transform = function(){
		@nodeToParentTransform()
		glMultMatrix(@__transformGL)
	}
	
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
	}
	
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
	}
	
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
	}
	
	setRect = function(x, y, width, height){
		@x = x
		@y = y
		@width = width
		@height = height
	}
	
	drawBB = function(color, fill){
		var points = [
			[0, 0],
			[@width, 0],
			[@width, @height],
			[0, @height],
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
		onComplete = null
	}

	__construct = function(params, target){
		super()
		@target = target
		if("onComplete" in params){
			@onComplete = functionOf(params.onComplete)
			delete params.onComplete
		}
		var t = @calculateTransition(@list, params, 0, 1)
		@duration = t.endTime
		// print "calculateTransition "..@list
		@addEventListener("enterFrame", @update, true)
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
			duration = delay = 0
		}
		t.easy = null
		if("easy" in params){
			t.easy = functionOf(params.easy)
			delete params.easy
		}
		t.repeat = 1
		if("repeat" in params){
			t.repeat = params.repeat
			delete params.repeat
		}
		t.infinite = t.repeat === true
		t.repeat = math.max(0, numberOf(t.repeat))

		t.alignRotation = false
		if("alignRotation" in params){
			t.alignRotation = params.alignRotation
			delete params.alignRotation
		}
		
		// t.duration = duration
		t.startTime = startTime
		t.startTransitionTime = startTime + delay
		t.endTime = t.startTransitionTime + duration
		list[] = t
		
		t.startValues = null
		t.endValues = {}
		t.subTransitions = []
		for(var name, value in params){
			if(name == "sequence"){
				// delete params[name]
				var sequenceStartTime = t.startTransitionTime
				var closed = false
				if("closed" in value){
					closed = value.closed
					delete value.closed
					if(closed){
						value[] = value[0].clone()
					}
				}
				var alignRotation = t.alignRotation
				if("alignRotation" in value){
					alignRotation = value.alignRotation
					delete value.alignRotation
				}
				for(var i, sub in value){
					if(objectOf(sub)){
						sub.alignRotation = alignRotation
						sub = @calculateTransition(t.subTransitions, sub, sequenceStartTime, speed)
						sequenceStartTime = sub.endTime
						t.endTime = math.max(t.endTime, sub.endTime)
					}
				}
				continue
			}
			if(name == "spawn"){
				// delete params[name]
				var alignRotation = t.alignRotation
				if("alignRotation" in value){
					alignRotation = value.alignRotation
					delete value.alignRotation
				}
				for(var i, sub in value){
					if(objectOf(sub)){
						sub.alignRotation = alignRotation
						sub = @calculateTransition(t.subTransitions, sub, t.startTransitionTime, speed)
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
		var time, duration = @time, @duration
		if(time >= duration){
			// @addEventListener("enterFrame", function(){
				@remove()
				@finished = true
				@onComplete && @onComplete.call(@target)
				// print("transition finished", time, duration)
			// })
			time = duration
		}
		@applyTimeToList(time, @list)
	}
	
	applyTimeToList = function(time, list){
		var prev
		for(var i, t in list){
			@applyTimeToItem(time, t, prev)
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
		var target = @target
		if(!t.startValues){
			t.startValues = {}
			for(var name, value in t.endValues){
				if(numberOf(value) && name in target && numberOf(target[name])){
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
						diff = 360 + diff % 360 // diff - math.floor(diff / 360) * 360
					}else if(diff > 360){
						diff = diff % 360 // diff - math.floor(diff / 360) * 360
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
		if(@finished)
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
			@applyTimeToList(time + t.startTransitionTime, t.subTransitions)
	}
}

ColorNode = extends Node {
	__object = {
		color: [0.5 0.7 0.5 1]
	}
	
	paint = function(){
		@drawBB(@color, true)
	}
}

Group = extends Node {
	__object = {
		__isRelativeAnchor = false
		__anchorX = 0
		__anchorY = 0
	}
}

Scene = extends Group {

}