#ifndef __MARMALADE_OS_H__
#define __MARMALADE_OS_H__

/******************************************************************************
* Copyright (C) 2012 Evgeniy Golovin (evgeniy.golovin@unitpoint.ru)
*
* Latest source code: https://github.com/unitpoint/cocos2d-os
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/

#include "objectscript.h"

#include "CCAutoreleasePool.h"
#include "CCTexture2D.h"
#include "CCTextureCache.h"
#include "CCLabelBMFont.h"
#include "CCPointExtension.h"

using namespace ObjectScript;

class MarmaladeOS: public OS
{
public:

	const OS_CHAR ** os_paths;
	const OS_CHAR * compiled_files_path;
	const OS_CHAR * output_filename;

	bool is_multi_touch;

	int texture2d_class_crc;
	int texture2d_instance_crc;

	int labelBMFont_class_crc;
	int labelBMFont_instance_crc;

	int orientation;

	uint64 gc_start_time;
	int gc_frame_time;

	struct LabelBMFont
	{
		cocos2d::CCLabelBMFont * label;
		Core::String string;
		Core::String font;
		Core::String align;
		float color[4];
		float offs[2];

		LabelBMFont(OS * os, cocos2d::CCLabelBMFont * p_label);
		~LabelBMFont();

		void setColor(float color[4]);
	};

	MarmaladeOS(const OS_CHAR * os_paths[], const OS_CHAR * compiled_files_path, const OS_CHAR * output_filename = "output.txt");
	~MarmaladeOS();

	bool init(MemoryManager * mem);
	void shutdown();

	void initAppModule();
	void initTextureClass();
	void initLabelBMFontClass();

	OS_EFileUseType checkFileUsage(const String& sourcecode_filename, const String& compiled_filename);

	static float clampUnit(float f);

	bool getColor(int offs, float color[4]);

	void drawLabelBMFont(int params);
	void drawImage(int params);

	void drawImage(cocos2d::CCTexture2D * texture, float width, float height, 
		float frameX, float frameY, float frameWidth, float frameHeight, 
		bool flipX, bool flipY, float color[4], float opacity = 1.0f);

	enum ETouchPhase
	{
		TOUCH_PHASE_START,
		TOUCH_PHASE_MOVE,
		TOUCH_PHASE_END,
		TOUCH_PHASE_CANCEL,
	};

	void registerTouchEvent(int x, int y, ETouchPhase phase, int id);
	void registerKeyEvent(int key, bool pressed);
	
	static int32 touchEventHandler(void* system_data, void* user_data);
	static int32 motionEventHandler(void* system_data, void* user_data);
	static int32 multiTouchEventHandler(void* system_data, void* user_data);
	static int32 multiMotionEventHandler(void* system_data, void* user_data);
	static int32 keyEventHandler(void* system_data, void* user_data);
	static int32 charEventHandler(void* system_data, void* user_data);
	
	bool isFileExist(const OS_CHAR * filename);

	// String resolvePath(const String& p_filename, const String& cur_path);
	String getCompiledFilename(const String& resolved_filename);

	void echo(const void * buf, int size);
	void printf(const OS_CHAR * format, ...);

	// void startFrame();
	float update();
	
	static int run(MarmaladeOS*, const OS_CHAR * main_stript);
	static int run(const OS_CHAR * main_stript, const OS_CHAR * os_paths[], const OS_CHAR * compiled_files_path, const OS_CHAR * output_filename = "output.txt");
};

#endif // __MARMALADE_OS_H__
