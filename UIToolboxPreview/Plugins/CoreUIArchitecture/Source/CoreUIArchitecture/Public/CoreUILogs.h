#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCoreUI, Log, Log);

#define DEBUG_LOG_BASE(mode, format, ...)									\
		UE_LOG(LogCoreUI,													\
			mode,															\
			TEXT("%s [Line: %i]: ") TEXT(format), TEXT(__FILE__), __LINE__,	\
			##__VA_ARGS__)

#define CORE_UI_LOG(format, ...) DEBUG_LOG_BASE(Log, format, ##__VA_ARGS__)
#define CORE_UI_WARNING(format, ...) DEBUG_LOG_BASE(Warning, format, ##__VA_ARGS__)
#define CORE_UI_ERROR(format, ...) DEBUG_LOG_BASE(Error, format, ##__VA_ARGS__)
