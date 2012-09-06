// Application module
_E = extends _G {}
_G.app = _E

require("core")
require("types")

__get@orientation = function(){
	// native function
}
__set@orientation = function(a){
	// native function
}

__get@screenWidth = function(){
	// native function
} 
__get@screenHeight = function(){
	// native function
}

__get@screenSize = function(){
	return Size(this.screenWidth this.screenHeight)
}

ORIENTATION_PORTRAIT = 0
ORIENTATION_PORTRAIT_UPSIDE_DOWN = 1
ORIENTATION_LANDSCAPE_LEFT = 2
ORIENTATION_LANDSCAPE_RIGHT = 3

orientation = ORIENTATION_PORTRAIT