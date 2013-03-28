// Application main file.

#include "main.h"
#include "marmaladeos.h"

int main()
{
	s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, 4);
	const char * os_paths[] = {
#if 1
		"raw://../../engine-os",
		"raw://../prog-os",
#endif
		NULL
	};
#if defined _MSC_VER
	const char * compiled_files_path = "raw://../assets";
#else
	const char * compiled_files_path = "";
#endif
	return MarmaladeOS::run("main.os", os_paths, compiled_files_path);
}
