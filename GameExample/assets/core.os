function __get(name){
	print "global property "..name.." is not declared"
	print "back trace"
	printBackTrace(1)
	print ""
}

function printBackTrace(skip_funcs){
	for(var i, t in debugBackTrace(skip_funcs + 1)){
		print concat("======= ["i"]")
		print concat("  function: "t.name", arguments: "t.arguments)
		// print concat("  line: "t.line", pos: "t.pos", token: "t.token", file: "t.file)
		print concat("  line: "t.line", pos: "t.pos", file: "t.file)
		// print concat("  object: "(t.object === _G && "<<GLOBALS>>" || t.object))
	}
}

/*
function Object.__get(name){
	print "object property "..name.." is not declared in "..this
}
*/

function eval(str, env){
	return compileText(str).applyEnv(env || _G, null, ...)
}

var events = {}

function addEventListener(eventName, func, zOrder){
	events[eventName][func] = zOrder || -1
	events[eventName].rsort()
}

function removeEventListener(eventName, func){
	delete events[eventName][func]
}

function triggerEvent(eventName, params){
	for(var func, zOrder in events[eventName]){
		func(params)
	}
}

var timers = {}

function isCallable(f){ return typeof f === "function" || typeof f === "object" }

function setTimeout(func, delaySec, count, priority){
	count = count || 1
	count > 0 && func || return;
	var i = #timers
	timers[i] = {
		nextTimeSec = app.timeSec + delaySec
		delaySec = delaySec
		func = func
		count = count
		priority = priority || -1
	}
	// timers.sort(function(a b){ return b.priority - a.priority })
	timers.rsort "priority"
	return i
}

function clearTimeout(t){
	delete timers[t]
}

HIGH_PRIORITY = 999999

addEventListener("enterFrame" function(){
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
} HIGH_PRIORITY+1)
