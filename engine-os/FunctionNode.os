
var counter = 0

FunctionNode = {
	__object = {
		time = 0,
		timeSpeed = 1,
		
		__events = {},
		__childrenNeg = {},
		__childrenPos = {},
		__timers = {},
		__parent = null,
		__parentChildren = null,
		__zOrder = 0,
	},
	
	__get@parent = {||@__parent},
	__set@parent = {|a| 
		if(@__parent !== a){ 
			@remove() 
			a && a.insert(this) 
		}
	},
	
	__get@zOrder = {||@__zOrder},
	__set@zOrder = {|a| 
		a = math.round(a)
		if(@__zOrder != a){ 
			@__zOrder = a
			if(@__parent){
				@__parentChildren[this][0] = a
				@__parent.sortChildren(@__parentChildren)
			}
		}
	},
	
	attrs: function(params){
		for(var field, value in objectOf(params)){
			this[field] = value
		}
		return this
	},
	
	sortChildren = function(children){
		children.sort {|b, a|
			var z = a[0] <=> b[0]
			return z != 0 ? z : a[1] <=> b[1]
		}
	},
	
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
	},
	
	insertTo = function(newParent, zOrder){
		return newParent.insert(this, zOrder)
	},
	
	remove = function(node){
		node = node || this
		if(node.__parent){
			node.triggerEvent("onExit", {sender: node})
			delete node.__parentChildren[node]
			node.__parent = null
			node.__parentChildren = null
		}
	},
	
	removeAll = function(){
		@__childrenNeg, @__childrenPos = {}, {}
	},
	
	contains = function(node){
		return node in @__childrenNeg || node in @__childrenPos
	},
	
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
	},
	
	handlePaint = function(){},
	handleTouch = function(){},
	handleKeyEvent = function(){},
	
	addEventListener = function(eventName, func, zOrder){
		functionOf(func) || return;
		eventName in @__events || @__events[eventName] = {}
		@__events[eventName][func] = zOrder || 0
		@__events[eventName].sort{|b, a| a <=> b}
		return [eventName, func]
	},
	
	removeEventListener = function(eventName, func){
		if(arrayOf(eventName)){
			eventName, func = eventName[0], eventName[1]
		}
		if(eventName in @__events){
			delete @__events[eventName][func]
		}
	},

	triggerLocalEvent = function(eventName, params){
		if(eventName in @__events){
			// params.target = this
			for(var func in @__events[eventName]){
				func.call(this, params)
			}
		}
	},
	
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
	},
	
	setTimeout = function(func, delay, count, priority){
		count = count || 1
		count > 0 && functionOf(func) || return;
		@__timers[func] = {
			nextTime = @time + delay,
			delay = delay,
			count = count,
			priority = priority || 0,
		}
		@__timers.sort{|b, a| a.priority <=> b.priority}
		return func
	},

	clearTimeout = function(t){
		delete @__timers[t]
	},
	
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
	},

	transition = function(t){
		// objectOf(t) || throw "object argument required"
		return @insert(Transition(t, this))
	},
	
	stopTransition = function(t){
		t && t.remove()
	},
	
	stopAllTransitions = function(){
		@removeAllInstancesOf(Transition)
	},
	
	removeAllInstancesOf = function(type){
		for(var t in @__childrenPos){
			if(t is type)
				t.remove()
		}
		for(var t in @__childrenNeg){
			if(t is type)
				t.remove()
		}
	},
}
