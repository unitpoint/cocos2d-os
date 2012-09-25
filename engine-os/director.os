var core = require("core")
var app = require("app")
require("constants")
require("node")
require("image")
require("text")
require("utils")

_E = extends _G {}
_G.director = _E

print "screen size "..app.screenSize

if(CC_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA){
    CC_BLEND_SRC = GL_ONE
    CC_BLEND_DST = GL_ONE_MINUS_SRC_ALPHA
}else{
    CC_BLEND_SRC = GL_SRC_ALPHA
    CC_BLEND_DST = GL_ONE_MINUS_SRC_ALPHA
}

function get width(){ return app.screenWidth }
function get height(){ return app.screenHeight }
function get size(){ return Size(this.width this.height) }

var alphaBlending
function get alphaBlending(){ return alphaBlending }
function set alphaBlending(a){
	alphaBlending = a
	if(a){
		glEnable(GL_BLEND)
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST)
	}else{
		glDisable(GL_BLEND)
	}
}

var depthTest
function get depthTest(){ return depthTest }
function set depthTest(a){
	depthTest = a
	if(a){
		glClearDepth(1.0)
		glEnable(GL_DEPTH_TEST)
		glDepthFunc(GL_LEQUAL)
//		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)
	}else{
		glDisable(GL_DEPTH_TEST)
	}
}

var projection
function get projection(){ return projection }
function set projection(a){
	projection = a
	updateProjection()
}

var function updateProjection(){
	var size = app.screenSize
	var zeye = size.height / 1.1566
	if(projection == PROJECTION_2D){
		glViewport(0, 0, size.width, size.height)
        glMatrixMode(GL_PROJECTION)
		glLoadIdentity()
		ccglOrtho(0, size.width, 0, size.height, -1024 * CC_CONTENT_SCALE_FACTOR(), 
			1024 * CC_CONTENT_SCALE_FACTOR())
		glMatrixMode(GL_MODELVIEW)
		glLoadIdentity()	
	}else if(projection == PROJECTION_3D){
		glViewport(0, 0, size.width, size.height)
        glMatrixMode(GL_PROJECTION)
		glLoadIdentity()
		gluPerspective(60, size.width/size.height, 0.5, 1500.0)
		
		glMatrixMode(GL_MODELVIEW)	
		glLoadIdentity()
		gluLookAt(size.width/2, size.height/2, -zeye,
				 size.width/2, size.height/2, 0,
				 0.0, -1.0, 0.0)
	}
}

var function applyOrientation()
{
	var w = app.screenWidth / 2
	var h = app.screenHeight / 2

	var orientation = app.orientation
	if(orientation == ORIENTATION_PORTRAIT){
		/* glTranslatef(w h 0)
		glScalef(-1 1 1)
		glTranslatef(-w -h 0) */
	}else if(orientation == ORIENTATION_PORTRAIT_UPSIDE_DOWN){
		// upside down
		glTranslatef(w,h,0)
		glRotatef(180,0,0,1)
		glTranslatef(-w,-h,0)
	}else if(orientation == ORIENTATION_LANDSCAPE_RIGHT){
		glTranslatef(w,h,0)
		glRotatef(90,0,0,1)
		glTranslatef(-h,-w,0)
	}else if(orientation == ORIENTATION_LANDSCAPE_LEFT){
		glTranslatef(w,h,0)
		glRotatef(-90,0,0,1)
		glTranslatef(-h,-w,0)
	}
}

_E.alphaBlending = true
_E.depthTest = true
_E.projection = PROJECTION_3D

glClearColor(0 0 0 1)

animationInterval = 1 / 60

var setAppOrientation = app.__set@orientation
app.__set@orientation = function(a){
	setAppOrientation.call(app, a)
	// screenSize = app.screenSize
	updateProjection()
}

// app.orientation = ORIENTATION_LANDSCAPE_LEFT
// app.orientation = ORIENTATION_LANDSCAPE_RIGHT
app.orientation = ORIENTATION_PORTRAIT
// app.orientation = ORIENTATION_PORTRAIT_UPSIDE_DOWN

var runningScene
function get scene(){ return runningScene }
function set scene(a){
	// runningScene = a
	nextScene = a
	setNextScene()
}

function insert(node){
	if(runningScene && node) runningScene.insert(node)
}

function remove(node){
	if(runningScene && node) runningScene.remove(node)
}

nextScene = null

_E.scene = Scene()

var totalFrames = 0
function get totalFrames(){ return totalFrames }

function enableDefaultGlStates(){
	glEnableClientState(GL_VERTEX_ARRAY)
	glEnableClientState(GL_COLOR_ARRAY)
	glEnableClientState(GL_TEXTURE_COORD_ARRAY)
	glEnable(GL_TEXTURE_2D)
}

function disableDefaultGlStates(){
	glDisable(GL_TEXTURE_2D)
	glDisableClientState(GL_TEXTURE_COORD_ARRAY)
	glDisableClientState(GL_COLOR_ARRAY)
	glDisableClientState(GL_VERTEX_ARRAY)
}

var function setNextScene(){
	runningScene = nextScene
	nextScene = null
}

var function paint(){
	// glClearColor(1 0 0 1)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	
	if(nextScene) setNextScene()
	
	glPushMatrix()
	applyOrientation()

	// By default enable VertexArray, ColorArray, TextureCoordArray and Texture2D
	enableDefaultGlStates()
	
	// paint the scene
	var paintParams = {opacity = 1}
    if(runningScene) runningScene.handlePaint(paintParams)
	
	disableDefaultGlStates()

	glPopMatrix()
	glSwapBuffers()
	
	++totalFrames
}

touches = {}

function handleTouches(){
	var time, orientation, width, height, touches = app.timeSec, app.orientation, _E.width, _E.height, {}
	for(var id, touch in app.touches){
		if(!touch.processed){
			if(orientation == ORIENTATION_PORTRAIT){
				// touch.y = height - touch.y
			}else if(orientation == ORIENTATION_PORTRAIT_UPSIDE_DOWN){
				touch.x = width - touch.x
			}else if(orientation == ORIENTATION_LANDSCAPE_LEFT){
				// touch.x, touch.y = touch.y, touch.x
				touch.x, touch.y = height - touch.y, touch.x
			}else if(orientation == ORIENTATION_LANDSCAPE_RIGHT){
				// touch.x, touch.y = height - touch.y, width - touch.x
				touch.x, touch.y = touch.y, width - touch.x
			}
			touch.nativeX, touch.nativeY = touch.x, touch.y
			touches.push touch
		}else if(touch.phase == "end" || touch.phase == "cancel" || time - touch.processed > 30){
			// print "delete old touch "..app.touches[id]
			delete app.touches[id]
		}
	}
	for(var id, touch in touches){
		if(touch.processed){
			continue;
		}
		touch.processed = time
		if(touch.captured && !touch.modal){ // && touch.phase != "start"){
			var cur = touch.captured
			var recursion = {[cur] = true}
			for(;cur !== runningScene && cur.__parent;){
				cur = cur.__parent
				if(cur in recursion) break
				recursion[cur] = true
			}
			if(cur === runningScene){
				// touch.captured.triggerEvent("touch" touch)
				touch.captured.handleTouch(touch)
				if(touch.captured){
					// print "still captured " // ..touch
					continue
				}
				// print concat("captured node "cur" didn't capture "touch" so run generic step")
			}else{
				touch.captured = null
				// print "captured node is detached "..touch.." so run generic step"
			}
		}
		touch.modal = false
		// runningScene.triggerEvent("touch" touch)
		runningScene.handleTouch(touch)
	}
	// print "touches "..app.touches
}

var deltaTime = 0.01
function get deltaTime(){return deltaTime}

var timeSpeed = 1
function get timeSpeed(){return timeSpeed}
function set timeSpeed(a){ timeSpeed = a }

var time = 0
function get time(){return time}
function set time(a){ time = a }

var prevAppTime = 0
var prevDeltaTime = 0

var function clamp(a, min, max){
	if(a < min) return min
	if(a > max) return max
	return a
}

var coreTriggerEvent = core.triggerEvent
function core.triggerEvent(eventName, params){
	if(eventName == "enterFrame"){
		// calculate delta time
		var appTime = app.timeSec
		deltaTime = (appTime - prevAppTime) * timeSpeed
		prevAppTime = appTime
		deltaTime = clamp(deltaTime, prevDeltaTime*0.9, prevDeltaTime*1.1) 
		deltaTime = clamp(deltaTime, 0.01, 0.1) 
		prevDeltaTime = deltaTime
		time = time + deltaTime
		
		var updateParams = {deltaTime = deltaTime}
		coreTriggerEvent.call(core, eventName, updateParams)
		handleTouches()

		if(runningScene) runningScene.handleUpdate(updateParams)

		paint()
	}else{
		coreTriggerEvent.call(core, eventName, params)
		if(runningScene) runningScene.triggerEvent(eventName, params)
	}
}
