var app = require("app")

Node = {
	__events = {}
	__postEvents = {}
	__children = {}
	enabled = true
	
	__construct = function(){
		var self = this
		this.addEventListener("enterFrame", function(deltaTimeSec){ 
			self.updateTimers(deltaTimeSec)
			self.update(deltaTimeSec)
		})
		// this.addEventListener("paint", function(){ self.paint() })
	}
	
	update = function(deltaTimeSec){}
	paint = function(){}
	
	addEventListener = function(eventName, func, userParams){
		this.__events[eventName][func] = userParams
	}
	
	addPostEventListener = function(eventName, func, userParams){
		this.__postEvents[eventName][func] = userParams
	}
	
	triggerEvent = function(eventName, params){
		for(var func, userParams in this.__events[eventName]){
			func(params userParams)
		}
		for(var i, child in this.__children){
			if(child.enabled) child.triggerEvent(eventName, params)
		}
		for(var func, userParams in this.__postEvents[eventName]){
			func(params userParams)
		}
	}
	
	__timers = {}
	timeSec = 0
	timeSpeed = 1

	setTimeout = function(delaySec, func, count){
		count = count || 1
		count > 0 && func || return;
		var i = #this.__timers
		this.__timers[i] = {
			nextTimeSec = this.timeSec + delaySec
			delaySec = delaySec
			func = func
			count = count
		}
		return i
	}

	clearTimeout = function(t){
		delete this.__timers[t]
	}
	
	updateTimers = function(deltaTimeSec){
		this.timeSec = this.timeSec + deltaTimeSec * this.timeSpeed
		var timeSec = this.timeSec
		for(var i, t in this.__timers){
			if(t.nextTimeSec >= timeSec){
				t.func()
				if(t.count <= 1){
					delete this.__timers[i]
					continue
				}
				t.count = t.count - 1
				t.nextTimeSec = timeSec + t.delaySec
			}
		}
	}
}