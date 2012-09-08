var app = require("app")

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

Node = {
	__object = {
		__events = {}
		__children = []
		__timers = {}
		timeSec = 0
		timeSpeed = 1
		enabled = true
		left = 0
		top = 0
		width = 0
		height = 0
	}
	
	__construct = function(){
		this.width = director.width
		this.height = director.height
		var self = this
		this.addEventListener("enterFrame", function(deltaTimeSec){ 
			self.updateTime(deltaTimeSec)
			self.update(deltaTimeSec)
		}, HIGH_PRIORITY + 1)
		// this.addEventListener("paint", function(){ self.paint() })
	}
	
	update = function(deltaTimeSec){}
	paint = function(){}
	
	addEventListener = function(eventName, func, zOrder){
		this.__events[eventName][func] = zOrder || -1
		this.__events[eventName].rsort()
	}
	
	removeEventListener = function(eventName, func){
		delete this.__events[eventName][func]
	}

	triggerEvent = function(eventName, params){
		var childrenProcessed = false
		for(var func, zOrder in this.__events[eventName]){
			if(!childrenProcessed && zOrder < 0){
				for(var i, child in this.__children.reverseIter()){
					if(child.enabled) child.triggerEvent(eventName, params)
				}
				childrenProcessed = true;
			}
			func(params)
		}
		if(!childrenProcessed){
			for(var i, child in this.__children.reverseIter()){
				if(child.enabled) child.triggerEvent(eventName, params)
			}
		}
	}
	
	setTimeout = function(func, delaySec, count, priority){
		count = count || 1
		count > 0 && func || return;
		var i = #this.__timers
		this.__timers[i] = {
			nextTimeSec = this.timeSec + delaySec
			delaySec = delaySec
			func = func
			count = count
			priority = priority || -1
		}
		// this.__timers.sort(function(a b){ return b.priority - a.priority })
		this.__timers.rsort "priority"
		return i
	}

	clearTimeout = function(t){
		delete this.__timers[t]
	}
	
	updateTime = function(deltaTimeSec){
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

Scene = extends Node {
	update = function(deltaTimeSec){
		print "Scene.update: "..deltaTimeSec
	}
}