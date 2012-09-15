function __get(name){
	print concat("global property \""name"\" is not declared")
	print "back trace"
	printBackTrace(1)
	print ""
}

function Object.__get(name, autoCreate){
	if(autoCreate) return;
	print concat("object property \""name"\" is not declared in "this)
	print "back trace"
	printBackTrace(1) // skip current function
	print ""
}

function printBackTrace(skipNumFuncs){
	for(var i, t in debugBackTrace(skipNumFuncs + 1)){ // skip printBackTrace
		print concat("======= ["i"]")
		// print concat("  line: "t.line", pos: "t.pos", token: "t.token", file: "t.file)
		print concat("  line: "t.line", pos: "t.pos", file: "t.file)
		print concat("  function: "t.name", arguments: "t.arguments)
		// print concat("  object: "(t.object === _G && "<<GLOBALS>>" || t.object))
	}
}

function eval(str, env){
	return compileText(str).applyEnv(env || _G, null, ...)
}

var events = {}

function addEventListener(eventName, func, zOrder){
	functionof func || return;
	events[eventName][func] = zOrder || 0
	events[eventName].rsort()
	return [eventName func]
}

function removeEventListener(eventId){
	if(arrayof eventId){
		var eventName, func = eventId[0], eventId[1]
		delete events[eventName][func]
	}
}

function triggerEvent(eventName, params){
	// print "core.triggerEvent: "..events
	for(var func, zOrder in events[eventName]){
		func(params)
	}
}

var timers = {}

function isCallable(f){ return typeof f === "function" || typeof f === "object" }

function setTimeout(func, delay, count, priority){
	count = count || 1
	count > 0 && functionof func || return;
	var i = func // #timers
	timers[i] = {
		nextTime = app.timeSec + delay
		delay = delay
		func = func
		count = count
		priority = priority || 0
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
	var time = app.timeSec
	for(var i, t in timers){
		if(t.nextTime <= time){
			t.nextTime = time + t.delay
			if(t.count === true){
				t.func.call(null)
			}else{
				if(t.count <= 1){
					delete timers[i]
				}else{
					t.count = t.count - 1
				}
				t.func.call(null)
			}
		}
	}
} HIGH_PRIORITY+1)

function toNumber(a){
	return numberof valueof a
}

function toString(a){
	return stringof valueof a
}

function deepClone(p){
	p = clone p
	for(var k, v in p){
		p[k] = deepClone(v)
	}
	return p
}

function assert(a, message){
	if(!a){
		print(message ? message : "assert failed")
		printBackTrace(1)
		terminate()
	}
}