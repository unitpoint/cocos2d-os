#ifndef __MARMALADE_OS_H__
#define __MARMALADE_OS_H__

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

	static float clampUnit(float f);

	bool getColor(int offs, float color[4]);

	void drawLabelBMFont(int params);
	void drawImage(int params);

	enum ETouchPhase
	{
		TOUCH_PHASE_START,
		TOUCH_PHASE_MOVE,
		TOUCH_PHASE_END,
		TOUCH_PHASE_CANCEL,
	};

	void registerTouchEvent(int x, int y, ETouchPhase phase, int id);
	
	static int32 touchEventHandler(void* system_data, void* user_data);
	static int32 motionEventHandler(void* system_data, void* user_data);
	static int32 multiTouchEventHandler(void* system_data, void* user_data);
	static int32 multiMotionEventHandler(void* system_data, void* user_data);
	static int32 keyEventHandler(void* system_data, void* user_data);
	static int32 charEventHandler(void* system_data, void* user_data);
	
	bool isFileExist(const OS_CHAR * filename);

	String resolvePath(const String& p_filename, const String& cur_path);
	String getCompiledFilename(const String& resolved_filename);

	void printf(const OS_CHAR * format, ...);

	void startFrame();
	
	static int run(MarmaladeOS*, const OS_CHAR * main_stript);
	static int run(const OS_CHAR * main_stript, const OS_CHAR * os_paths[], const OS_CHAR * compiled_files_path, const OS_CHAR * output_filename = "output.txt");
};

#endif // __MARMALADE_OS_H__
