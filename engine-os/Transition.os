require("utils")

Transition = extends FunctionNode {
	__object = {
		duration = 0,
		list = [],
		finished = false,
		onComplete = null,
	},

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
	},
	
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
	},
	
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
	},
	
	applyTimeToList = function(time, list){
		var prev
		for(var i, t in list){
			@applyTimeToItem(time, t, prev)
			prev = t.endValues
		}
	},
	
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
	},
}
