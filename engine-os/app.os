require("constants")
// require("core")
// require("type")

_E = _G.app // extends C++ namespace

function get screenSize(){
	return Size(@screenWidth @screenHeight)
}

orientation = ORIENTATION_PORTRAIT

touchEvents = {}
keyEvents = {}

function registerKeyEvent(key pressed){
	if(key in keyEvents){
		keyEvents[key].pressed = pressed
		return
	}
	keyEvents[key] = {
		key = key
		pressed = pressed
		processed = false
		captured = null
		capturedFunc = null
	}
}

var autoTouchId = 0
function registerTouchEvent(x y phase id){
	// printf("registerTouchEvent: %s %s %s %s\n", x, y, phase, id)
	if(id == 0){
		id = phase == "start" ? --autoTouchId : autoTouchId
	}
	if(phase == "start"){
		touchEvents[id] = {
			x = x
			y = y
			phase = phase
			processed = false
			id = id
			captured = null
			capturedFunc = null
		}
		// printf("start: %s\n", touchEvents)
		return
	}
	if(!(id in touchEvents)){
		// printf("id not found: %s, %s\n", id, touchEvents)
		return
	}
	var touch = touchEvents[id]
	if(phase == "move"){
		if(touch.phase == "start"){
			if(!touch.processed){
				touch.x = x
				touch.y = y
				// printf("start not processed: %s, %s\n", id, touchEvents)
				return
			}
		}else if(touch.phase != "move"){
			// printf("not moved, skip: %s, %s\n", id, touchEvents)
			return
		}
	}
	touch.x = x
	touch.y = y
	touch.phase = phase
	touch.processed = false
	touch.id = id
	// printf("new touch: %s, %s\n", id, touchEvents)
}
