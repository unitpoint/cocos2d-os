// Application main file.

#include "Main.h"
#include "objectscript.h"

#include "s3eOSExec.h"
#include "s3eSurface.h"
#include "s3eKeyboard.h"
#include "s3ePointer.h"
#include "IwGL.h"
#include "s3eAccelerometer.h"

#include "IwMemBucket.h"

using namespace ObjectScript;

void initOpenGLModule(OS * os)
{
}

OS_NUMBER getGlobalNumber(OS * os, const OS::String& name)
{
	os->getGlobal(name);
	OS_NUMBER val = os->toNumber();
	os->pop();
	return val;
}

OS_NUMBER popNumber(OS * os)
{
	OS_NUMBER val = os->toNumber();
	os->pop();
	return val;
}

bool getGlobalBool(OS * os, const OS::String& name)
{
	os->getGlobal(name);
	bool val = os->toBool();
	os->pop();
	return val;
}

bool getOSTerminated(OS*)
{
	return false;
}

class MarmaladeOSMemoryManager: public OS::MemoryManager
{
public:

	int allocated_bytes;
	int max_allocated_bytes;

	MarmaladeOSMemoryManager()
	{
		allocated_bytes = 0;
		max_allocated_bytes = 0;
	}

	void * malloc(int size OS_DBG_FILEPOS_DECL)
	{
		int * p = (int*)::malloc(size + sizeof(int));
		p[0] = size;
		allocated_bytes += size + sizeof(int);
		if(max_allocated_bytes < allocated_bytes){
			max_allocated_bytes = allocated_bytes;
		}
		OS_MEMSET(p+1, 0, size);
		return p+1;
	}

	void free(void * ptr)
	{
		if(ptr){
			int * p = (int*)ptr - 1;
			allocated_bytes -= p[0] + sizeof(int);
			OS_MEMSET(ptr, 0xde, p[0]);
			::free(p);
		}
	}

	void setBreakpointId(int id)
	{
	}

	int getAllocatedBytes()
	{
		return allocated_bytes;
	}

	int getMaxAllocatedBytes()
	{
		return max_allocated_bytes;
	}

	int getCachedBytes()
	{
		return 0;
	}
};

class MarmaladeOS: public OS
{
public:

	const OS_CHAR * output_filename;
	bool is_multi_touch;

	MarmaladeOS()
	{
		output_filename = "output.txt";
		s3eFileDelete(output_filename);

		IwGLInit();

		s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, 4);

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

	bool init()
	{
		if(!OS::init()){
			return false;
		}

		initAppModule();

		return true;
	}

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
		};
		Func list[] = {
			// {OS_TEXT("getScreenWidth"), App::getScreenWidth},
			{OS_TEXT("__get@screenWidth"), App::getScreenWidth},
			// {OS_TEXT("getScreenHeight"), App::getScreenHeight},
			{OS_TEXT("__get@screenHeight"), App::getScreenHeight},
			// {OS_TEXT("getIsMultiTouch"), App::getIsMultiTouch},
			{OS_TEXT("__get@isMultiTouch"), App::getIsMultiTouch},
			{OS_TEXT("__get@timeMS"), App::getTimeMS},
			{OS_TEXT("__get@timeSec"), App::getTimeSec},
			{OS_TEXT("__get@accelerometerX"), App::getAccelerometerX},
			{OS_TEXT("__get@accelerometerY"), App::getAccelerometerY},
			{OS_TEXT("__get@accelerometerZ"), App::getAccelerometerZ},
			{OS_TEXT("__get@hasAccelerometer"), App::getHasAccelerometer},
			{OS_TEXT("startAccelerometer"), App::startAccelerometer},
			{OS_TEXT("stopAccelerometer"), App::stopAccelerometer},
			{}
		};
		getGlobalObject(OS_TEXT("app"));
		setFuncs(list);
		pop();

		require("app"); // add some additional
	}

	static int32 touchEventHandler(void* system_data, void* user_data)
	{
		return 0;
	}

	static int32 motionEventHandler(void* system_data, void* user_data)
	{
		return 0;
	}

	static int32 multiTouchEventHandler(void* system_data, void* user_data)
	{
		return 0;
	}

	static int32 multiMotionEventHandler(void* system_data, void* user_data)
	{
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
};

int main()
{
	// IwMemBucketInit();
	// IwMemBucketDebugSetBreakpoint(2331);
	// IW_CALLSTACK("Main");
	// int32 checkpoint = IwMemBucketCheckpoint();

	OS * os = OS::create(new MarmaladeOS()); //, new MarmaladeOSMemoryManager());
	// os->setSetting(OS_SETTING_CREATE_DEBUG_OPCODES, false);
	{
		OS::String enterFrame(os, "enterFrame");
		OS::String triggerEvent(os, "triggerEvent");
		OS::String director(os, "director");
		OS::String animationIntervalSec(os, "animationIntervalSec");

		// os->require("core");
		os->require("main");
	
		uint64 updateTimeMS = 0;
		for(int i = 0; i < 10; i++){ 
			updateTimeMS = s3eTimerGetMs();
			
			// s3eDeviceYield(0);
			s3eKeyboardUpdate();
			s3ePointerUpdate();
			
			// ccAccelerationUpdate();

			if(s3eDeviceCheckQuitRequest() || getOSTerminated(os)){
				break;
			}

			os->getGlobal(triggerEvent);
			os->pushGlobals(); // this
			os->pushString(enterFrame);
			os->call(1);

			s3eDeviceYield(0);

			os->getGlobal(director);
			os->getProperty(animationIntervalSec);
			double animationIntervalSec = popNumber(os);
			if(animationIntervalSec < 0.01){
				animationIntervalSec = 0.01;
			}else if(animationIntervalSec > 0.2){
				animationIntervalSec = 0.2;
			}
			int animationIntervalMS = (int)(1.0f / animationIntervalSec);
			while((s3eTimerGetMs() - updateTimeMS) < animationIntervalMS){
				int yield = (int)(animationIntervalMS - (s3eTimerGetMs() - updateTimeMS));
				if(yield < 0){
					break;
				}
				s3eDeviceYield(yield);
			}
		}
	}
	os->release();

	// CCSharedFinalizer::finalizeAll();

	// IwMemBucketDebugCheck(0, checkpoint, "check-app-leak.txt");
	// IwMemBucketTerminate();
	return 0;
}
