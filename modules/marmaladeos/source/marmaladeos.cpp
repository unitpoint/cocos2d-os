// Application main file.

#include "marmaladeos.h"
#include "glos.h"
#include "box2d-os.h"

#include "stddef.h"

#include "s3eOSExec.h"
#include "s3eSurface.h"
#include "s3eKeyboard.h"
#include "s3ePointer.h"
#include "s3eAccelerometer.h"

#include "IwMemBucket.h"

MarmaladeOS::MarmaladeOS(const OS_CHAR * os_paths[], const OS_CHAR * compiled_files_path, const OS_CHAR * output_filename)
{
	this->os_paths = os_paths;
	this->compiled_files_path = compiled_files_path;
	this->output_filename = output_filename;
	s3eFileDelete(output_filename);

	texture2d_class_crc = (int)&texture2d_class_crc;
	texture2d_instance_crc = (int)&texture2d_instance_crc;

	labelBMFont_class_crc = (int)&labelBMFont_class_crc;
	labelBMFont_instance_crc = (int)&labelBMFont_instance_crc;

	gc_start_time = 0;
	gc_frame_time = 0;

	IwGLInit();

	s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, 4);
	orientation = 0;

	is_multi_touch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;
	if(is_multi_touch){
		s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, &multiTouchEventHandler, this);
		s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &multiMotionEventHandler, this);
	}else{
		s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, &touchEventHandler, this);
		s3ePointerRegister(S3E_POINTER_MOTION_EVENT, &motionEventHandler, this);
	}
	// Register keyboard event handler
	s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, &keyEventHandler, this);
	s3eKeyboardRegister(S3E_KEYBOARD_CHAR_EVENT, &charEventHandler, this);
}

MarmaladeOS::~MarmaladeOS()
{
	if(is_multi_touch){
		s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, &multiTouchEventHandler);
		s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &multiMotionEventHandler);
	}else{
		s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, &touchEventHandler);
		s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, &motionEventHandler);
	}
	// Register keyboard event handler
	s3eKeyboardUnRegister(S3E_KEYBOARD_KEY_EVENT, &keyEventHandler);
	s3eKeyboardUnRegister(S3E_KEYBOARD_CHAR_EVENT, &charEventHandler);

	if(IwGLIsInitialised()){
  		IwGLTerminate();
	}

	// s3eDeviceRequestQuit();
}

bool MarmaladeOS::init(MemoryManager * mem)
{
	if(!OS::init(mem)){
		return false;
	}

	initOpenGL(this);
	initOpenGL2(this);
	initOpenGLExt(this);
	initAppModule();
	initTextureClass();
	initLabelBMFontClass();
	initBox2d(this);

	return true;
}

void MarmaladeOS::shutdown()
{
	cocos2d::CCSharedFinalizer::finalizeAll();
	OS::shutdown();
}

void MarmaladeOS::initAppModule()
{
	struct App
	{
		static int getScreenWidth(OS * os, int params, int, int, void*)
		{
			os->pushNumber( IwGLGetInt(IW_GL_WIDTH) );
			return 1;
		}
		static int getScreenHeight(OS * os, int params, int, int, void*)
		{
			os->pushNumber( IwGLGetInt(IW_GL_HEIGHT) );
			return 1;
		}
		static int getIsMultiTouch(OS * os, int params, int, int, void*)
		{
			os->pushBool( ((MarmaladeOS*)os)->is_multi_touch );
			return 1;
		}
		static int getTimeMS(OS * os, int params, int, int, void*)
		{
			os->pushNumber( (OS_NUMBER)s3eTimerGetMs() );
			return 1;
		}
		static int getTimeSec(OS * os, int params, int, int, void*)
		{
			os->pushNumber( (OS_NUMBER)s3eTimerGetMs() * 0.001f );
			return 1;
		}
		static int getAccelerometerX(OS * os, int params, int, int, void*)
		{
			os->pushNumber( (OS_NUMBER)s3eAccelerometerGetX() / S3E_ACCELEROMETER_1G );
			return 1;
		}
		static int getAccelerometerY(OS * os, int params, int, int, void*)
		{
			os->pushNumber( (OS_NUMBER)s3eAccelerometerGetY() / S3E_ACCELEROMETER_1G );
			return 1;
		}
		static int getAccelerometerZ(OS * os, int params, int, int, void*)
		{
			os->pushNumber( (OS_NUMBER)s3eAccelerometerGetZ() / S3E_ACCELEROMETER_1G );
			return 1;
		}
		static int getHasAccelerometer(OS * os, int params, int, int, void*)
		{
			os->pushNumber( s3eAccelerometerGetInt(S3E_ACCELEROMETER_AVAILABLE) );
			return 1;
		}
		static int startAccelerometer(OS * os, int params, int, int, void*)
		{
			s3eAccelerometerStart();
			return 0;
		}
		static int stopAccelerometer(OS * os, int params, int, int, void*)
		{
			s3eAccelerometerStop();
			return 0;
		}
		static int getOrientation(OS * os, int params, int, int, void*)
		{
			os->pushNumber(((MarmaladeOS*)os)->orientation);
			return 1;
		}
		static int setOrientation(OS * os, int params, int, int, void*)
		{
			((MarmaladeOS*)os)->orientation = os->toInt();
			return 0;
		}
		static int drawImage(OS * os, int params, int, int, void*)
		{
			((MarmaladeOS*)os)->drawImage(params);
			return 0;
		}
		static int drawLabelBMFont(OS * os, int params, int, int, void*)
		{
			((MarmaladeOS*)os)->drawLabelBMFont(params);
			return 0;
		}
	};
	FuncDef funcs[] = {
		// {"getScreenWidth", App::getScreenWidth},
		{"__get@screenWidth", App::getScreenWidth},
		// {"getScreenHeight", App::getScreenHeight},
		{"__get@screenHeight", App::getScreenHeight},
		// {"getIsMultiTouch", App::getIsMultiTouch},
		{"__get@isMultiTouch", App::getIsMultiTouch},
		{"__get@timeMS", App::getTimeMS},
		{"__get@timeSec", App::getTimeSec},
		{"__get@accelerometerX", App::getAccelerometerX},
		{"__get@accelerometerY", App::getAccelerometerY},
		{"__get@accelerometerZ", App::getAccelerometerZ},
		{"__get@hasAccelerometer", App::getHasAccelerometer},
		{"startAccelerometer", App::startAccelerometer},
		{"stopAccelerometer", App::stopAccelerometer},
		{"__get@orientation", App::getOrientation},
		{"__set@orientation", App::setOrientation},
		{"drawImage", App::drawImage},
		{"drawLabelBMFont", App::drawLabelBMFont},
		{}
	};
	getModule("app");
	setFuncs(funcs);

	NumberDef numbers[] = {
		{"ESC", s3eKeyEsc},
		{"TAB", s3eKeyTab},
		{"BACKSPACE", s3eKeyBackspace},
		{"ENTER", s3eKeyEnter},
		{"LEFT_SHIFT", s3eKeyLeftShift},
		{"LEFT_CTRL", s3eKeyLeftControl},
		{"SPACE", s3eKeySpace},
		{"LEFT", s3eKeyLeft},
		{"UP", s3eKeyUp},
		{"RIGHT", s3eKeyRight},
		{"DOWN", s3eKeyDown},
		{"0", s3eKey0},
		{"1", s3eKey1},
		{"2", s3eKey2},
		{"3", s3eKey3},
		{"4", s3eKey4},
		{"5", s3eKey5},
		{"6", s3eKey6},
		{"7", s3eKey7},
		{"8", s3eKey8},
		{"9", s3eKey9},
		{"A", s3eKeyA},
		{"B", s3eKeyB},
		{"C", s3eKeyC},
		{"D", s3eKeyD},
		{"E", s3eKeyE},
		{"F", s3eKeyF},
		{"G", s3eKeyG},
		{"H", s3eKeyH},
		{"I", s3eKeyI},
		{"J", s3eKeyJ},
		{"K", s3eKeyK},
		{"L", s3eKeyL},
		{"M", s3eKeyM},
		{"N", s3eKeyN},
		{"O", s3eKeyO},
		{"P", s3eKeyP},
		{"Q", s3eKeyQ},
		{"R", s3eKeyR},
		{"S", s3eKeyS},
		{"T", s3eKeyT},
		{"U", s3eKeyU},
		{"V", s3eKeyV},
		{"W", s3eKeyW},
		{"X", s3eKeyX},
		{"Y", s3eKeyY},
		{"Z", s3eKeyZ},
		{"F1", s3eKeyF1},
		{"F2", s3eKeyF2},
		{"F3", s3eKeyF3},
		{"F4", s3eKeyF4},
		{"F5", s3eKeyF5},
		{"F6", s3eKeyF6},
		{"F7", s3eKeyF7},
		{"F8", s3eKeyF8},
		{"F9", s3eKeyF9},
		{"F10", s3eKeyF10},
		{"NUM_PAD_0", s3eKeyNumPad0},
		{"NUM_PAD_1", s3eKeyNumPad1},
		{"NUM_PAD_2", s3eKeyNumPad2},
		{"NUM_PAD_3", s3eKeyNumPad3},
		{"NUM_PAD_4", s3eKeyNumPad4},
		{"NUM_PAD_5", s3eKeyNumPad5},
		{"NUM_PAD_6", s3eKeyNumPad6},
		{"NUM_PAD_7", s3eKeyNumPad7},
		{"NUM_PAD_8", s3eKeyNumPad8},
		{"NUM_PAD_9", s3eKeyNumPad9},
		{"NUM_PAD_PLUS", s3eKeyNumPadPlus},
		{"NUM_PAD_MINUS", s3eKeyNumPadMinus},
		{"NUM_PAD_ENTER", s3eKeyNumPadEnter},
		{"RSK", s3eKeyRSK}, //!< Right soft key.
		{"LSK", s3eKeyLSK}, //!< Left soft key.
		{"LS", s3eKeyLS}, //!< Left shoulder button.
		{"RS", s3eKeyRS}, //!< Right shoulder button.
		{"#", s3eKeyHash}, //!< # Key.
		{"*", s3eKeyStar}, //!< * Key (on keyboard numberpad for normal keyboards).

		// Select/ok button
		{"OK", s3eKeyOk}, //!< Select key.
		{"CLR", s3eKeyCLR}, //!< CLR key.

		// Volume
		{"VOLUME_UP", s3eKeyVolUp}, //!< Volume Up key.
		{"VOLUME_DOWN", s3eKeyVolDown}, //!< Volume Down key.

		//Misc.
		{"CAMERA", s3eKeyCamera}, //!< Camera button.
		{"MIC", s3eKeyMic}, //!< Microphone button.
		{"FN", s3eKeyFn}, //!< Fn button.
		{"SYM", s3eKeySym}, //!< Sym button.

		//Call
		{"ACCEPT", s3eKeyAccept}, //!< call accept (talk).
		{"END", s3eKeyEnd}, //!< call end (reject).
		{"HOME", s3eKeyHomePage}, //!< Home key.

		{"BUTTON_1", s3eKeyButton1}, //!< Generic Button1.
		{"BUTTON_2", s3eKeyButton2}, //!< Generic Button2.
		{"BUTTON_3", s3eKeyButton3}, //!< Generic Button3.
		{"BUTTON_4", s3eKeyButton4}, //!< Generic Button4.
		{"BUTTON_5", s3eKeyButton5}, //!< Generic Button5.
		{"BUTTON_6", s3eKeyButton6}, //!< Generic Button6.
		{"BUTTON_7", s3eKeyButton7}, //!< Generic Button7.
		{"BUTTON_8", s3eKeyButton8}, //!< Generic Button8.

		{"F11", s3eKeyF11}, //!< Key F11.
		{"F12", s3eKeyF12}, //!< Key F12.
		{"LEFT_ALT", s3eKeyLeftAlt}, //!< Left Alt key.

		{"RIGHT_CTRL", s3eKeyRightControl}, //!< Right Control Key.
		{"RIGHT_ALT", s3eKeyRightAlt}, //!< Right Alt Key.
		{"RIGHT_SHIFT", s3eKeyRightShift}, //!< Right Shift Key.
		{"`", s3eKeyBacktick}, //!< Backtick '`' Key.
		{",", s3eKeyComma}, //!< Comma ',' Key.
		{".", s3eKeyPeriod}, //!< Period '.' Key.
		{"/", s3eKeySlash}, //!< Forward slash '/' Key.
		{"\\", s3eKeyBackSlash}, //!< Back slash '\' Key.
		{";", s3eKeySemicolon}, //!< Semicolon ';' Key.
		{"'", s3eKeyApostrophe}, //!< Apostrophe (') Key.
		{"[", s3eKeyLeftBracket}, //!< Left Bracket '[' Key.
		{"]", s3eKeyRightBracket}, //!< Right Bracket ']' Key.
		{"=", s3eKeyEquals}, //!< Equals '=' Key.
		{"-", s3eKeyMinus}, //!< Minus '-' key on main keyboard.
		{"CAPS_LOCK", s3eKeyCapsLock}, //!< Caps Lock key

		{"NUM_PAD_PERIOD", s3eKeyNumPadPeriod}, //!< Period '.' key on numberpad
		{"NUM_PAD_SLASH", s3eKeyNumPadSlash}, //!< Slash '/' key on numberpad
		{"NUM_LOCK", s3eKeyNumLock}, //!< NumLock key
		{"INSERT", s3eKeyInsert}, //!< Insert key
		{"HOME", s3eKeyHome}, //!< Home key
		{"PAGE_UP", s3eKeyPageUp}, //!< Page Up key
		{"PAGE_DOWN", s3eKeyPageDown}, //!< Page Down key
		{"END_KB", s3eKeyKbEnd}, //!< End key (on keyboard)
		{"DELETE", s3eKeyDelete}, //!< Delete key
		{"PAUSE", s3eKeyPause}, //!< Pause key
		{"@", s3eKeyAt}, //!< At '@' key
		{"BACK", s3eKeyBack}, //!< Back key
		{"MENU", s3eKeyMenu}, //!< Menu key
		{"SEARCH", s3eKeySearch}, //!< Search key
		{"3D_MODE", s3eKey3DMode}, //!< 3D Mode key

		{"GAME_KEY_A", s3eKeyAbsGameA}, //!< Abstract Game keyA.
		{"GAME_KEY_B", s3eKeyAbsGameB}, //!< Abstract Game keyB.
		{"GAME_KEY_C", s3eKeyAbsGameC}, //!< Abstract Game keyC.
		{"GAME_KEY_D", s3eKeyAbsGameD}, //!< Abstract Game keyD.
		{"GAME_UP", s3eKeyAbsUp}, //!< Abstract Up.
		{"GAME_DOWN", s3eKeyAbsDown}, //!< Abstract Down.
		{"GAME_LEFT", s3eKeyAbsLeft}, //!< Abstract Left.
		{"GAME_RIGHT", s3eKeyAbsRight}, //!< Abstract Right.
		{"GAME_OK", s3eKeyAbsOk}, //!< Abstract Ok.
		{"GAME_ASK", s3eKeyAbsASK}, //!< Abstract action softkey.
		{"GAME_BSK", s3eKeyAbsBSK}, //!< Abstract backwards softkey.
		{}
	};
	getObject("keys");
	setNumbers(numbers);
	pop();

	require("app"); // add some additional
}

float MarmaladeOS::clampUnit(float f)
{
	if(f < 0.0f) return 0.0f;
	if(f > 1.0f) return 1.0f;
	return f;
}

bool MarmaladeOS::getColor(int offs, float color[4])
{
	if(isArray(offs)){
		for(int i = 0; i < 4; i++){
			pushStackValue(offs);
			pushNumber(i);
			getProperty(false);
			color[i] = !isNumber() ? (pop(), 1.0f) : clampUnit(popFloat());
		}
		return true;
	}else if(isObject(offs)){
		static const OS_CHAR * rgba[] = {
			OS_TEXT("r"), OS_TEXT("g"), OS_TEXT("b"), OS_TEXT("a") 
		};
		for(int i = 0; i < 4; i++){
			pushStackValue(offs);
			pushString(rgba[i]);
			getProperty();
			color[i] = !isNumber() ? (pop(), 1.0f) : clampUnit(popFloat());
		}
		return true;
	}
	for(int i = 0; i < 4; i++){
		color[i] = 1.0f;
	}
	return false;
}

void MarmaladeOS::drawLabelBMFont(int params)
{
	if(params < 1) return;
		
	float opacity = 1.0f;
	if(params >= 2){
		opacity = isNumber(-params+1) ? 1.0f : clampUnit(toFloat(-params+1));
	}

	LabelBMFont * label = (LabelBMFont*)toUserdata(labelBMFont_instance_crc, -params);
	if(label){
		GLubyte glOpacity = (GLubyte)(opacity * 255);
		if(glOpacity != label->label->getOpacity()){
			label->label->setOpacity(glOpacity);
		}
		label->label->visit();
	}
}

void MarmaladeOS::drawImage(int params)
{
	if(!isObject(-params)) return;

	float opacity;
	if(params >= 2){
		opacity = !isNumber(-params+1) ? 1.0f : clampUnit(toFloat(-params+1));
	}else{
		getProperty(-params, "opacity");
		opacity = !isNumber() ? (pop(), 1.0f) : clampUnit(popFloat());
	}

	params = getAbsoluteOffs(-params);
			
	getProperty(params, "texture");
	cocos2d::CCTexture2D * texture = (cocos2d::CCTexture2D*)toUserdata(texture2d_instance_crc);
	if(!texture) return;

	getProperty(params, "width");
	float width = popFloat();

	getProperty(params, "height");
	float height = popFloat();

	getProperty(params, "frameLeft");
	float frameX = popFloat();

	getProperty(params, "frameTop");
	float frameY = popFloat();

	getProperty(params, "frameWidth");
	float frameWidth = popFloat();

	getProperty(params, "frameHeight");
	float frameHeight = popFloat();

	getProperty(params, "flipX");
	bool flipX = popBool();

	getProperty(params, "flipY");
	bool flipY = popBool();

	float color[4];
	getProperty(params, "color");
	getColor(-1, color);
	pop();

	cocos2d::ccBlendFunc blendFunc;
	if(texture->getHasPremultipliedAlpha()){
		blendFunc.src = CC_BLEND_SRC;
		blendFunc.dst = CC_BLEND_DST;
		for(int i = 0; i < 4; i++){
			color[i] *= opacity;
		}
	}else{
		blendFunc.src = GL_SRC_ALPHA;
		blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
	}

	float atlasWidth = (float)texture->getPixelsWide();
	float atlasHeight = (float)texture->getPixelsHigh();

	float left = frameX / atlasWidth;
	float right	= left + frameWidth / atlasWidth;
	float top = frameY / atlasHeight;
	float bottom = top + frameHeight / atlasHeight;

	float temp;
	if(flipX){
		temp = left;
		left = right;
		right = temp;
	}
	if(flipY){
		temp = top;
		top = bottom;
		bottom = temp;
	}

	cocos2d::ccV3F_C4B_T2F_Quad quad;

	quad.tl.vertices = cocos2d::vertex3(0, 0, 0);
	quad.tr.vertices = cocos2d::vertex3(width, 0, 0);
	quad.bl.vertices = cocos2d::vertex3(0, height, 0);
	quad.br.vertices = cocos2d::vertex3(width, height, 0);

	quad.bl.texCoords.u = left;
	quad.bl.texCoords.v = bottom;
	quad.br.texCoords.u = right;
	quad.br.texCoords.v = bottom;
	quad.tl.texCoords.u = left;
	quad.tl.texCoords.v = top;
	quad.tr.texCoords.u = right;
	quad.tr.texCoords.v = top;

	cocos2d::ccColor4B tmpColor = { 
		(GLubyte)(255 * color[0]),
		(GLubyte)(255 * color[1]),
		(GLubyte)(255 * color[2]),
		(GLubyte)(255 * color[3])
	};
	quad.bl.colors = tmpColor;
	quad.br.colors = tmpColor;
	quad.tl.colors = tmpColor;
	quad.tr.colors = tmpColor;

	#define kQuadSize sizeof(quad.bl)

	bool newBlend = blendFunc.src != CC_BLEND_SRC || blendFunc.dst != CC_BLEND_DST;
	if(newBlend){
		glBlendFunc(blendFunc.src, blendFunc.dst);
	}
	glBindTexture(GL_TEXTURE_2D, texture->getName());

	long offset = (long)&quad;

	// vertex
	int diff = offsetof(cocos2d::ccV3F_C4B_T2F, vertices);
	glVertexPointer(3, GL_FLOAT, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof(cocos2d::ccV3F_C4B_T2F, colors);
	glColorPointer(4, GL_UNSIGNED_BYTE, kQuadSize, (void*)(offset + diff));
	
	// tex coords
	diff = offsetof(cocos2d::ccV3F_C4B_T2F, texCoords);
	glTexCoordPointer(2, GL_FLOAT, kQuadSize, (void*)(offset + diff));
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	if(newBlend){
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	}
}

void MarmaladeOS::initTextureClass()
{
	struct Texture2d
	{
		static int getPixelFormat(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			cocos2d::CCTexture2D * texture = (cocos2d::CCTexture2D*)os->toUserdata(os->texture2d_instance_crc, -params-1);
			if(texture){
				os->pushNumber((OS_NUMBER)texture->getPixelFormat());
				return 1;
			}
			return 0;
		}

		static int getWidth(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			cocos2d::CCTexture2D * texture = (cocos2d::CCTexture2D*)os->toUserdata(os->texture2d_instance_crc, -params-1);
			if(texture){
				os->pushNumber((OS_NUMBER)texture->getContentSize().width);
				return 1;
			}
			return 0;
		}

		static int getHeight(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			cocos2d::CCTexture2D * texture = (cocos2d::CCTexture2D*)os->toUserdata(os->texture2d_instance_crc, -params-1);
			if(texture){
				os->pushNumber((OS_NUMBER)texture->getContentSize().height);
				return 1;
			}
			return 0;
		}

		static int getHasPremultipliedAlpha(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			cocos2d::CCTexture2D * texture = (cocos2d::CCTexture2D*)os->toUserdata(os->texture2d_instance_crc, -params-1);
			if(texture){
				os->pushBool(texture->getHasPremultipliedAlpha());
				return 1;
			}
			return 0;
		}

		static void ccTexture2dDtor(OS * os, void * data, void * user_param)
		{
			cocos2d::CCTexture2D * texture = (cocos2d::CCTexture2D*)data;
			texture->release();
		}

		static int newTexture(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			String filename = os->toString(-params);
			const char * ext[2];
			if(os->getFilenameExt(filename) == ".jpg"){
				ext[0] = ".jpg";
				ext[1] = ".png";
			}else{
				ext[0] = ".png";
				ext[1] = ".jpg";
			}
			for(int i = 0; i < 2; i++){
				filename = os->changeFilenameExt(filename, ext[i]);
				if(os->isFileExist(filename)){
					break;
				}
			}
			cocos2d::CCTexture2D * texture = cocos2d::CCTextureCache::sharedTextureCache()->addImage(filename);
			if(texture){
				texture->retain();
				os->pushUserPointer(os->texture2d_instance_crc, texture, ccTexture2dDtor);
				os->pushStackValue(-1);
				os->getGlobal("Texture2d");
				os->setPrototype(os->texture2d_instance_crc);
				return 1;
			}
			return 0;
		}
	};
	FuncDef list[] = {
		{"__get@pixelFormat", Texture2d::getPixelFormat},
		{"__get@width", Texture2d::getWidth},
		{"__get@height", Texture2d::getHeight},
		{"__get@hasPremultipliedAlpha", Texture2d::getHasPremultipliedAlpha},
		{"__construct", Texture2d::newTexture},
		{}
	};

	pushGlobals();
	pushString("Texture2d");
	pushUserdata(texture2d_class_crc, 0);
	setFuncs(list);
	setProperty();
}

MarmaladeOS::LabelBMFont::LabelBMFont(OS * os, cocos2d::CCLabelBMFont * p_label): string(os), font(os), align(os, "left")
{
	label = p_label;
	label->retain();
	label->setScaleY(-1.0f);
	label->setAnchorPoint(ccp(0, 1));
}

MarmaladeOS::LabelBMFont::~LabelBMFont()
{
	label->release();
}

void MarmaladeOS::LabelBMFont::setColor(float color[4])
{
	OS_MEMCPY(this->color, color, sizeof(color));
	cocos2d::ccColor3B ccColor;
	ccColor.r = (GLubyte)(255 * color[0]);
	ccColor.g = (GLubyte)(255 * color[1]);
	ccColor.b = (GLubyte)(255 * color[2]);
	label->setColor(ccColor);
	label->setOpacity((GLubyte)(255 * color[3]));
}

void MarmaladeOS::initLabelBMFontClass()
{
	struct Lib
	{
		static int getString(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label){
				os->pushString(label->string);
				return 1;
			}
			return 0;
		}

		static int setString(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label && params > 0){
				String str = os->toString(-params);
				if(label->string != str){
					label->string = str;
					label->label->setString(label->string);
				}
			}
			return 0;
		}

		class LabelBMFontConfig: public cocos2d::CCLabelBMFont
		{
		public:

			cocos2d::CCBMFontConfiguration * getFontConfig(){ return m_pConfiguration; }
		};

		static int getFontHeight(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label){
				cocos2d::CCBMFontConfiguration * fontConfig = ((LabelBMFontConfig*)label->label)->getFontConfig();
				os->pushNumber((OS_NUMBER)fontConfig->m_uCommonHeight);
				return 1;
			}
			return 0;
		}

		static int getFont(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label){
				os->pushString(label->font);
				return 1;
			}
			return 0;
		}

		static int setFont(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label && params > 0){
				String str = os->toString(-params);
				if(label->font != str){
					label->font = str;

					cocos2d::CCTextAlignment alignment = cocos2d::CCTextAlignmentLeft;
					if(label->align == "right"){
						alignment = cocos2d::CCTextAlignmentRight;
					}else if(label->align == "center"){
						alignment = cocos2d::CCTextAlignmentCenter;
					}else{
						label->align = Core::String(os, "left");
					}

					float width = label->label->getContentSize().width;
					
					label->label->release();
					label->label = cocos2d::CCLabelBMFont::labelWithString(label->string, label->font, 
						width, alignment, ccp(label->offs[0], label->offs[1]));
				}
			}
			return 0;
		}

		static int getColor(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label){
				os->newArray();
				for(int i = 0; i < 4; i++){
					os->pushStackValue(-1);
					os->pushNumber(i);
					os->pushNumber(label->color[i]);
					os->setProperty();
				}
				return 1;
			}
			return 0;
		}

		static int setColor(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label && params > 0){
				float color[4];
				os->getColor(-params, color);
				label->setColor(color);
			}
			return 0;
		}

		static int getAlign(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label){
				os->pushString(label->align);
				return 1;
			}
			return 0;
		}

		static int setAlign(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label && params > 0){
				label->align = os->toString(-params);
					
				cocos2d::CCTextAlignment alignment = cocos2d::CCTextAlignmentLeft;
				if(label->align == "right"){
					alignment = cocos2d::CCTextAlignmentRight;
				}else if(label->align == "center"){
					alignment = cocos2d::CCTextAlignmentCenter;
				}else{
					label->align = Core::String(os, "left");
				}

				label->label->setAlignment(alignment);
			}
			return 0;
		}

		static int getWidth(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label){
				os->pushNumber(label->label->getContentSize().width);
				return 1;
			}
			return 0;
		}

		static int setWidth(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label && params > 0){
				label->label->setWidth(os->toNumber(-params));
			}
			return 0;
		}

		static int getHeight(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			LabelBMFont * label = (LabelBMFont*)os->toUserdata(os->labelBMFont_instance_crc, -params-1);
			if(label){
				os->pushNumber(label->label->getContentSize().height);
				return 1;
			}
			return 0;
		}

		static void labelBMFontDtor(OS * os, void * data, void * user_param)
		{
			LabelBMFont * label = (LabelBMFont*)data;
			label->~LabelBMFont();
		}

		static int newLabelBMFont(OS * p_os, int params, int, int, void*)
		{
			MarmaladeOS * os = (MarmaladeOS*)p_os;
			if(params < 1){
				return 0;
			}
			String string = os->toString(-params);
			String fontName	= os->isString(-params+1) ? os->toString(-params+1) : String(os, "arial-en-ru-32.fnt");
			float width		= os->isNumber(-params+2) ? os->toNumber(-params+2) : 0;
			String align	= os->isString(-params+3) ? os->toString(-params+3) : String(os, "");
			cocos2d::CCPoint offs = ccp(0, 0);

			cocos2d::CCTextAlignment alignment = cocos2d::CCTextAlignmentLeft;
			if(align == "right"){
				alignment = cocos2d::CCTextAlignmentRight;
			}else if(align == "center"){
				alignment = cocos2d::CCTextAlignmentCenter;
			}else{
				align = Core::String(os, "left");
			}
			cocos2d::CCLabelBMFont * ccLabel = cocos2d::CCLabelBMFont::labelWithString(string, fontName, width, alignment, offs);
			if(ccLabel){
				LabelBMFont * label = (LabelBMFont*)os->pushUserdata(os->labelBMFont_instance_crc, sizeof(LabelBMFont), labelBMFontDtor);
				new (label) LabelBMFont(os, ccLabel);
				label->string = string;
				label->font = fontName;
				label->align = align;
				label->offs[0] = offs.x;
				label->offs[1] = offs.y;

				float color[4] = {1, 1, 1, 1};
				label->setColor(color);

				os->pushStackValue(-1);
				os->getGlobal("LabelBMFont");
				os->setPrototype(os->labelBMFont_instance_crc);
				return 1;
			}
			return 0;
		}
	};


	FuncDef list[] = {
		{"__get@fontHeight", Lib::getFontHeight},
		{"__get@font", Lib::getFont},
		{"__set@font", Lib::setFont},
		{"__get@string", Lib::getString},
		{"__set@string", Lib::setString},
		{"__get@color", Lib::getColor},
		{"__set@color", Lib::setColor},
		{"__get@align", Lib::getAlign},
		{"__set@align", Lib::setAlign},
		{"__get@width", Lib::getWidth},
		{"__set@width", Lib::setWidth},
		{"__get@height", Lib::getHeight},
		{"__construct", Lib::newLabelBMFont},
		{}
	};

	pushGlobals();
	pushString("LabelBMFont");
	pushUserdata(labelBMFont_class_crc, 0);
	setFuncs(list);
	setProperty();
}

void MarmaladeOS::registerKeyEvent(int key, bool pressed)
{
	getGlobal("app");
	getProperty("registerKeyEvent");
	getGlobal("app"); // push 'this' for registerTouchEvent
	pushNumber(key);
	pushBool(pressed);
	call(2, 0);
}

void MarmaladeOS::registerTouchEvent(int x, int y, ETouchPhase phase, int id)
{
	getGlobal("app");
	getProperty("registerTouchEvent");
	getGlobal("app"); // push 'this' for registerTouchEvent
	pushNumber(x);
	pushNumber(y);
	switch(phase){
	case TOUCH_PHASE_START:
		pushString("start");
		break;

	case TOUCH_PHASE_MOVE:
		pushString("move");
		break;

	case TOUCH_PHASE_END:
		pushString("end");
		break;

	default:
	case TOUCH_PHASE_CANCEL:
		pushString("cancel");
		break;
	}
	pushNumber(id);
	call(4, 0);
}

int32 MarmaladeOS::touchEventHandler(void* system_data, void* user_data)
{
	MarmaladeOS * os = (MarmaladeOS*)user_data;
	s3ePointerEvent * ev = (s3ePointerEvent*)system_data;
	switch(ev->m_Pressed){
	case S3E_POINTER_STATE_DOWN:
		os->registerTouchEvent(ev->m_x, ev->m_y, TOUCH_PHASE_START, 0);
		break;

	case S3E_POINTER_STATE_UP:
		os->registerTouchEvent(ev->m_x, ev->m_y, TOUCH_PHASE_END, 0);
		break;
	}
	return 0;
}

int32 MarmaladeOS::motionEventHandler(void* system_data, void* user_data)
{
	MarmaladeOS * os = (MarmaladeOS*)user_data;
	s3ePointerMotionEvent * ev = (s3ePointerMotionEvent*)system_data;
	os->registerTouchEvent(ev->m_x, ev->m_y, TOUCH_PHASE_MOVE, 0);
	return 0;
}

int32 MarmaladeOS::multiTouchEventHandler(void* system_data, void* user_data)
{
	MarmaladeOS * os = (MarmaladeOS*)user_data;
	s3ePointerTouchEvent * ev = (s3ePointerTouchEvent*)system_data;
	switch(ev->m_Pressed){
	case S3E_POINTER_STATE_DOWN:
		os->registerTouchEvent(ev->m_x, ev->m_y, TOUCH_PHASE_START, ev->m_TouchID);
		break;

	case S3E_POINTER_STATE_UP:
		os->registerTouchEvent(ev->m_x, ev->m_y, TOUCH_PHASE_END, ev->m_TouchID);
		break;
	}
	return 0;
}

int32 MarmaladeOS::multiMotionEventHandler(void* system_data, void* user_data)
{
	MarmaladeOS * os = (MarmaladeOS*)user_data;
	s3ePointerTouchMotionEvent * ev = (s3ePointerTouchMotionEvent*)system_data;
	os->registerTouchEvent(ev->m_x, ev->m_y, TOUCH_PHASE_MOVE, ev->m_TouchID);
	return 0;
}

int32 MarmaladeOS::keyEventHandler(void* system_data, void* user_data)
{
	MarmaladeOS * os = (MarmaladeOS*)user_data;
	s3eKeyboardEvent * ev = (s3eKeyboardEvent*)system_data;
	os->registerKeyEvent(ev->m_Key, ev->m_Pressed != 0);
	return 0;
}

int32 MarmaladeOS::charEventHandler(void* system_data, void* user_data)
{
	MarmaladeOS * os = (MarmaladeOS*)user_data;
	s3eKeyboardCharEvent * ev = (s3eKeyboardCharEvent*)system_data;
	return 0;
}

/*
void * openFile(const OS_CHAR * filename, const OS_CHAR * mode)
{
	return s3eFileOpen(filename, mode);
}

int readFile(void * buf, int size, void * f)
{
	return s3eFileRead(buf, size, 1, (s3eFile*)f);
}

int writeFile(const void * buf, int size, void * f)
{
	return s3eFileWrite(buf, size, 1, (s3eFile*)f);
}

int seekFile(void * f, int offset, int whence)
{
	s3eFileSeek((s3eFile*)f, offset, (s3eFileSeekOrigin)whence);
	return s3eFileTell((s3eFile*)f);
}

void closeFile(void * f)
{
	s3eFileClose((s3eFile*)f);
}
*/

bool MarmaladeOS::isFileExist(const OS_CHAR * filename)
{
	return s3eFileCheckExists(filename) ? true : false;
}

OS::String MarmaladeOS::resolvePath(const String& p_filename, const String& cur_path)
{
	String resolved_path = p_filename;
	if(!isAbsolutePath(p_filename) && cur_path.getDataSize()){
		resolved_path = cur_path + OS_PATH_SEPARATOR + p_filename;
	}
	if(isFileExist(resolved_path)){
		return resolved_path;
	}
	String filename = changeFilenameExt(getFilename(p_filename), OS_SOURCECODE_EXT);
	for(int i = 0; os_paths[i]; i++){
		String cur_path(this, os_paths[i]);
		resolved_path = cur_path + OS_PATH_SEPARATOR + filename;
		if(isFileExist(resolved_path)){
			return resolved_path;
		}
	}
	if(isFileExist(getCompiledFilename(filename))){
		return filename;
	}
	core->error(OS_E_WARNING, String::format(this, OS_TEXT("filename %s is not resolved"), p_filename.toChar()));
	return String(this);
}

OS::String MarmaladeOS::getCompiledFilename(const String& resolved_filename)
{
	String filename = changeFilenameExt(getFilename(resolved_filename), OS_COMPILED_EXT);
	if(compiled_files_path[0]){
		String cur_path(this, compiled_files_path);
		return cur_path + OS_PATH_SEPARATOR + filename;
	}
	return filename;
}

void MarmaladeOS::printf(const OS_CHAR * format, ...)
{
	va_list va;
	va_start(va, format);
	FILE * f = fopen(output_filename, "a");
	OS_ASSERT(f);
	vfprintf(f, format, va);
	fclose(f);
}

void MarmaladeOS::startFrame()
{
 	// release cocos2d-x objects
 	cocos2d::CCPoolManager::getInstance()->pop();		
}

static double clamp(double a, double min, double max)
{
	if(a < min) return min;
	if(a > max) return max;
	return a;
}

void MarmaladeOS::onEnterGC()
{
	gc_start_time = s3eTimerGetMs();
}

void MarmaladeOS::onExitGC()
{
	gc_frame_time = (int)(s3eTimerGetMs() - gc_start_time);
}

int MarmaladeOS::run(const OS_CHAR * main_stript, const OS_CHAR * os_paths[], const OS_CHAR * compiled_files_path, const OS_CHAR * output_filename)
{
	return run(new MarmaladeOS(os_paths, compiled_files_path, output_filename), main_stript);
}

int MarmaladeOS::run(MarmaladeOS * p_os, const OS_CHAR * main_stript)
{
	MarmaladeOS * os = OS::create(p_os);
	// os->setSetting(OS_SETTING_PRIMARY_COMPILED_FILE, true);
	os->require(main_stript);
	for(;;){ 
		uint64 start_time_ms = s3eTimerGetMs();
		
		os->startFrame();
			
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
			
		// ccAccelerationUpdate();

		if(s3eDeviceCheckQuitRequest() || os->isTerminated()){
			break;
		}

		os->getGlobal("triggerEvent");
		os->pushGlobals(); // this
		os->pushString("enterFrame");
		os->call(1);

		os->getGlobal("director");
		os->getProperty("animationInterval");
		int animation_ms = (int)(1000.0f * clamp(os->popNumber(), 0.005, 0.2));
		int frame_ms = (int)(s3eTimerGetMs() - start_time_ms);
		if(animation_ms > frame_ms){
			s3eDeviceYield(animation_ms - frame_ms);
		}else{
			s3eDeviceYield(1);
		}
	}
	int code = os->getTerminatedCode();
	os->release();
	return code;
}
