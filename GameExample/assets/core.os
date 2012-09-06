_E = _G

function __get(name){
	print "global property "..name.." is not found"
}

function eval(str, env){
	return compileText(str).applyEnv(env || _G, null, ...)
}

var events = {}

function addEventListener(eventName, func, userParams){
	events[eventName][func] = userParams
}

function triggerEvent(eventName, params){
	for(var func, userParams in events[eventName]){
		func(params, userParams)
	}
}

var timers = {}

function setTimeout(delaySec, func, count){
	count = count || 1
	count > 0 && func || return;
	var i = #timers
	timers[i] = {
		nextTimeSec = app.timeSec + delaySec
		delaySec = delaySec
		func = func
		count = count
	}
	return i
}

function clearTimeout(t){
	delete timers[t]
}

addEventListener("enterFrame", function(){
	var timeSec = app.timeSec
	for(var i, t in timers){
		if(t.nextTimeSec >= timeSec){
			t.func()
			if(t.count <= 1){
				delete timers[i]
				continue
			}
			t.count = t.count - 1
			t.nextTimeSec = timeSec + t.delaySec
		}
	}
})

