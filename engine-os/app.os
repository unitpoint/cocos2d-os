require("constants")
// require("core")
// require("type")

_E = _G.app // extends C++ namespace

function get screenSize(){
	return Size(this.screenWidth this.screenHeight)
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
		return
	}
	if(!(id in touchEvents)){
		return
	}
	var touch = touchEvents[id]
	if(phase == "move"){
		if(touch.phase == "start"){
			if(!touch.processed){
				touch.x = x
				touch.y = y
				return
			}
		}else if(touch.phase != "move"){
			return
		}
	}
	touch.x = x
	touch.y = y
	touch.phase = phase
	touch.processed = false
	touch.id = id
}
