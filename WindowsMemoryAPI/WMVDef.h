#pragma once

#include "ProjInfo.h"
#include <winerror.h>

#if defined( _WIN32 )
#   ifdef __PROJ_WMV_LIB__
#       define __WMV_API__    __declspec(dllexport)
#   else
#       define __WMV_API__    __declspec(dllimport)
#   endif
#else
#   ifdef __PROJ_WMV_LIB__
#       define __WMV_API__    
#   else
#       define __WMV_API__    
#   endif
#endif
