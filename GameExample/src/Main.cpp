// Application main file.

#include "Main.h"
#include "objectscript.h"
#include "OpenGLOS.h"
#include "stddef.h"

#include "s3eOSExec.h"
#include "s3eSurface.h"
#include "s3eKeyboard.h"
#include "s3ePointer.h"
#include "s3eAccelerometer.h"

#include "IwMemBucket.h"

#include "CCAutoreleasePool.h"
#include "CCTexture2D.h"
#include "CCTextureCache.h"
#include "CCLabelBMFont.h"
#include "CCPointExtension.h"

using namespace ObjectScript;

class MarmaladeOS: public OS
{
public:

	const OS_CHAR * output_filename;
	bool is_multi_touch;

	int texture2d_class_crc;
	int texture2d_instance_crc;

	int labelBMFont_class_crc;
	int labelBMFont_instance_crc;

	MarmaladeOS()
	{
		output_filename = "output.txt";
		s3eFileDelete(output_filename);

		texture2d_class_crc = (int)&texture2d_class_crc;
		texture2d_instance_crc = (int)&texture2d_instance_crc;

		labelBMFont_class_crc = (int)&labelBMFont_class_crc;
		labelBMFont_instance_crc = (int)&labelBMFont_instance_crc;

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

	~MarmaladeOS()
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

		 s3eDeviceRequestQuit();
	}

	bool init(MemoryManager * mem)
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

		return true;
	}

	void shutdown()
	{
		cocos2d::CCSharedFinalizer::finalizeAll();
		OS::shutdown();
	}

	int orientation;

	void initAppModule()
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
		FuncDef list[] = {
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
		setFuncs(list);
		pop();

		require("app"); // add some additional
	}

	static float clampUnit(float f)
	{
		if(f < 0.0f) return 0.0f;
		if(f > 1.0f) return 1.0f;
		return f;
	}

	bool getColor(int offs, float color[4])
	{
		if(isArray(offs)){
			for(int i = 0; i < 4; i++){
				pushStackValue(offs);
				pushNumber(i);
				getProperty(false, false);
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

	void drawLabelBMFont(int params)
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
			// glScalef(1, -1, 1);
			label->label->visit();
			// glScalef(1, -1, 1);
		}
	}

	void drawImage(int params)
	{
		if(!isObject(-params)) return;

		float opacity;
		if(params >= 2){
			opacity = isNumber(-params+1) ? 1.0f : clampUnit(toFloat(-params+1));
		}else{
			getProperty(-params, "opacity");
			opacity = isNumber() ? (pop(), 1.0f) : clampUnit(popFloat());
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

	void initTextureClass()
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
					os->pushNumber((OS_NUMBER)texture->getHasPremultipliedAlpha());
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

	struct LabelBMFont
	{
		cocos2d::CCLabelBMFont * label;
		Core::String string;
		Core::String font;
		Core::String align;
		float color[4];
		float offs[2];

		LabelBMFont(OS * os, cocos2d::CCLabelBMFont * p_label): string(os), font(os), align(os, "left")
		{
			label = p_label;
			label->retain();
			label->setScaleY(-1.0f);
			label->setAnchorPoint(ccp(0, 1));
		}

		~LabelBMFont()
		{
			label->release();
		}

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

		void setColor(float color[4])
		{
			OS_MEMCPY(this->color, color, sizeof(color));
			cocos2d::ccColor3B ccColor;
			ccColor.r = (GLubyte)(255 * color[0]);
			ccColor.g = (GLubyte)(255 * color[1]);
			ccColor.b = (GLubyte)(255 * color[2]);
			label->setColor(ccColor);
			label->setOpacity((GLubyte)(255 * color[3]));
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

				float color[4] = {0, 0, 0, 1};
				label->setColor(color);

				os->pushStackValue(-1);
				os->getGlobal("LabelBMFont");
				os->setPrototype(os->labelBMFont_instance_crc);
				return 1;
			}
			return 0;
		}
	};

	void initLabelBMFontClass()
	{
		FuncDef list[] = {
			{"__get@fontHeight", LabelBMFont::getFontHeight},
			{"__get@font", LabelBMFont::getFont},
			{"__set@font", LabelBMFont::setFont},
			{"__get@string", LabelBMFont::getString},
			{"__set@string", LabelBMFont::setString},
			{"__get@color", LabelBMFont::getColor},
			{"__set@color", LabelBMFont::setColor},
			{"__get@align", LabelBMFont::getAlign},
			{"__set@align", LabelBMFont::setAlign},
			{"__get@width", LabelBMFont::getWidth},
			{"__set@width", LabelBMFont::setWidth},
			{"__get@height", LabelBMFont::getHeight},
			{"__construct", LabelBMFont::newLabelBMFont},
			{}
		};

		pushGlobals();
		pushString("LabelBMFont");
		pushUserdata(labelBMFont_class_crc, 0);
		setFuncs(list);
		setProperty();
	}

	enum ETouchPhase
	{
		TOUCH_PHASE_START,
		TOUCH_PHASE_MOVE,
		TOUCH_PHASE_END,
		TOUCH_PHASE_CANCEL,
	};

	void registerTouchEvent(int x, int y, ETouchPhase phase, int id)
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

	static int32 touchEventHandler(void* system_data, void* user_data)
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

	static int32 motionEventHandler(void* system_data, void* user_data)
	{
		MarmaladeOS * os = (MarmaladeOS*)user_data;
		s3ePointerMotionEvent * ev = (s3ePointerMotionEvent*)system_data;
		os->registerTouchEvent(ev->m_x, ev->m_y, TOUCH_PHASE_MOVE, 0);
		return 0;
	}

	static int32 multiTouchEventHandler(void* system_data, void* user_data)
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

	static int32 multiMotionEventHandler(void* system_data, void* user_data)
	{
		MarmaladeOS * os = (MarmaladeOS*)user_data;
		s3ePointerTouchMotionEvent * ev = (s3ePointerTouchMotionEvent*)system_data;
		os->registerTouchEvent(ev->m_x, ev->m_y, TOUCH_PHASE_MOVE, ev->m_TouchID);
		return 0;
	}

	static int32 keyEventHandler(void* system_data, void* user_data)
	{
		return 0;
	}

	static int32 charEventHandler(void* system_data, void* user_data)
	{
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

	bool isFileExist(const String& filename)
	{
		return s3eFileCheckExists(filename) ? true : false;
	}

	String resolvePath(const String& p_filename, const String& cur_path, const String&)
	{
		String filename = p_filename;
		if(getFilenameExt(filename).getDataSize() == 0){
			filename = filename + OS_SOURCECODE_EXT;
		}
		const char * paths[] = {
			"",
			// "./assets/",
			NULL
		};
		for(int i = 0; paths[i]; i++){
			String assets_path(this, paths[i]);
			String resolved_filename = assets_path + filename;
			if(isFileExist(resolved_filename)){
				return resolved_filename;
			}
		}
		return String(this);
	}

	void printf(const OS_CHAR * format, ...)
	{
		va_list va;
		va_start(va, format);
		FILE * f = fopen(output_filename, "a");
		OS_ASSERT(f);
		vfprintf(f, format, va);
		fclose(f);
	}

	void startFrame()
	{
 		// release cocos2d-x objects
 		cocos2d::CCPoolManager::getInstance()->pop();		
	}
};

double clamp(double a, double min, double max)
{
	if(a < min) return min;
	if(a > max) return max;
	return a;
}

int main()
{
	MarmaladeOS * os = OS::create(new MarmaladeOS());
	os->require("main.os");
	
	for(;;){ 
		uint64 startFrameTimeMS = s3eTimerGetMs();
		
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
		int animationIntervalMS = (int)(1000.0f * clamp(os->popNumber(), 0.005, 0.2));
		int frameMS = (int)(s3eTimerGetMs() - startFrameTimeMS);
		if(animationIntervalMS > frameMS){
			s3eDeviceYield(animationIntervalMS - frameMS);
		}
	}
	int code = os->getTerminatedCode();
	os->release();
	return code;
}
