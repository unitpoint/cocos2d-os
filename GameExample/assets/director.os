_E = extends _G {}
_G.director = _E

require("core")
require("types")
require("node")
var app = require("app")
// var screenSize = app.screenSize

var __alphaBlending
function get alphaBlending(){ return __alphaBlending }
function set alphaBlending(a){
	__alphaBlending = a
	if(a){
		glEnable(GL_BLEND)
		glBlendFunc(GL_BLEND_SRC, GL_BLEND_DST)
	}else{
		glDisable(GL_BLEND)
	}
}

var __depthTest
function get depthTest(){ return __depthTest }
function set depthTest(a){
	__depthTest = a
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
var __projection
function get projection(){ return __projection }
function set projection(a){
	__projection = a
	updateProjection()
}

var function updateProjection(){
	var size = app.screenSize
	if(a == PROJECTION_2D){
		glViewport(0, 0, size.width, size.height);
        glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		ccglOrtho(0, size.width, 0, size.height, -1024 * CC_CONTENT_SCALE_FACTOR(), 
			1024 * CC_CONTENT_SCALE_FACTOR());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();	
	}else if(a == PROJECTION_3D){
		glViewport(0, 0, size.width, size.height);
        glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, size.width/size.height, 0.5, 1500.0);
		
		glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity();
		gluLookAt(size.width/2, size.height/2, zeye,
				 size.width/2, size.height/2, 0,
				 0.0f, 1.0f, 0.0f);
	}
}

alphaBlending = true
depthTest = true
projection = PROJECTION_3D
glClearColor(0 0 0 1)

animationIntervalSec = 1 / 60

var setAppOrientation = app.__set@orientation
app.__set@orientation = function(a){
	setAppOrientation(a)
	// screenSize = app.screenSize
	updateProjection()
}

app.orientation = app.ORIENTATION_LANDSCAPE_LEFT

var __runningScene
function get scene(){ return __runningScene }
function set scene(a){
	// __runningScene = a
	nextScene = a
	setNextScene()
}

nextScene = null
notificationNode = null
displayFPS = true
displayProfilers = true

scene = Scene()

var __totalFrames = 0
function get totalFrames(){ return __totalFrames }

function enableDefaultGlStates(){

}

function disableDefaultGlStates(){

}

var function setNextScene(){
	
}

var function drawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	
	if(nextScene) setNextScene()
	
	glPushMatrix()
	applyOrientation()

	// By default enable VertexArray, ColorArray, TextureCoordArray and Texture2D
	enableDefaultGlStates()

	// draw the scene
    if(__runningScene) __runningScene.visit()

	// draw the notifications node
	if(notificationNode) notificationNode.visit()

	if(displayFPS) showFPS()
	if(displayProfilers) showProfilers()

	disableDefaultGlStates()

	glPopMatrix()
	glSwapBuffers()
	__totalFrames++;
}

var old_triggerEvent = _G.triggerEvent
_G.triggerEvent = function(event_name, params){
	old_triggerEvent(event_name, params)
	if(__runningScene){ // && event_name != "enterFrame"){
		__runningScene.triggerEvent(event_name, params)
	}
}

addEventListener("touch", function(event){

})

deltaTimeSec = 0.01
var prevTimeSec = 0
addEventListener("enterFrame", function(){
	// calculate delta time
	var timeSec = app.timeSec
	deltaTimeSec = timeSec - prevTimeSec
	prevTimeSec = timeSec
	if(deltaTimeSec > 0.2) deltaTimeSec = 0.2
	
	// updateScene()
	drawScene()
})