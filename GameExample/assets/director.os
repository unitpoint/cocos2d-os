var core = require("core")
var app = require("app")
require("constants")
require("node")

_E = extends app {}
_G.director = _E

// _E = extends node {}

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

PROJECTION_2D = 0
PROJECTION_3D = 1
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
		gluLookAt(size.width/2, size.height/2, zeye,
				 size.width/2, size.height/2, 0,
				 0.0f, 1.0f, 0.0f)
	}
}

var function applyOrientation()
{
	var w = app.screenWidth / 2
	var h = app.screenHeight / 2

	var orientation = app.orientation
	if(orientation == ORIENTATION_PORTRAIT){
		// nothing
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

animationIntervalSec = 1 / 60

var setAppOrientation = app.__set@orientation
app.__set@orientation = function(a){
	setAppOrientation(a)
	// screenSize = app.screenSize
	updateProjection()
}

app.orientation = app.ORIENTATION_LANDSCAPE_LEFT

var runningScene
function get scene(){ return runningScene }
function set scene(a){
	// runningScene = a
	nextScene = a
	setNextScene()
}

nextScene = null
notificationNode = null
displayFPS = true
displayProfilers = true

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
	nextScene = null
}

var function drawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	
	if(nextScene) setNextScene()
	
	glPushMatrix()
	applyOrientation()

	// By default enable VertexArray, ColorArray, TextureCoordArray and Texture2D
	enableDefaultGlStates()

	// draw the scene
    if(runningScene) runningScene.visit()

	// draw the notifications node
	if(notificationNode) notificationNode.visit()

	if(displayFPS) showFPS()
	if(displayProfilers) showProfilers()

	disableDefaultGlStates()

	glPopMatrix()
	glSwapBuffers()
	
	++totalFrames
}

function showFPS(){
}

function showProfilers(){
}

var coreTriggerEvent = core.triggerEvent
function core.triggerEvent(eventName, params){
	coreTriggerEvent(eventName, params)
	if(runningScene && eventName != "enterFrame"){
		runningScene.triggerEvent(eventName, params)
	}
}

addEventListener("touch", function(event){

})

var deltaTimeSec = 0.01
function get deltaTimeSec(){return deltaTimeSec}

var timeSpeed = 1
function get timeSpeed(){return timeSpeed}
function set timeSpeed(a){ timeSpeed = a }

var prevTimeSec = 0

addEventListener("enterFrame", function(){
	// calculate delta time
	var timeSec = app.timeSec
	deltaTimeSec = (timeSec - prevTimeSec) * timeSpeed
	prevTimeSec = timeSec
	if(deltaTimeSec > 0.2) deltaTimeSec = 0.2
	
	if(runningScene){
		runningScene.triggerEvent("enterFrame", deltaTimeSec)
	}
	
	drawScene()
})