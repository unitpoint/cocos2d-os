require("constants")
// require("core")
// require("type")

_E = _G.app // extends C++ namespace

function get screenSize(){
	return Size(this.screenWidth this.screenHeight)
}

orientation = ORIENTATION_PORTRAIT

touches = {}

var autoTouchId = -1
function registerTouchEvent(x y phase id){
	if(id == 0){
		id = phase == "start" ? --autoTouchId : autoTouchId
	}
	if(phase == "start"){
		touches[id] = {
			x = x
			y = y
			phase = phase
			processed = false
			id = id
			captured = null
		}
		return
	}
	if(!(id in touches)){
		return
	}
	var touch = touches[id]
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
