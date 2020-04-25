#pragma once

#ifdef IMP_WINDOWS
	#ifdef IMP_BUILD_DLL
		#define IMP_API __declspec(dllexport)
	#else
		#define IMP_API __declspec(dllimport)
	#endif	
#else
	#error Not on windows
#endif