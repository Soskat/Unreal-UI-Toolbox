#pragma once

#include "CoreMinimal.h"

#define DEBUG_LOG_BASE(category, mode, format, ...)							\
		UE_LOG(category,													\
			mode,															\
			TEXT("%s [Line: %i]: ") TEXT(format), TEXT(__FILE__), __LINE__,	\
			##__VA_ARGS__)

#define DEBUG_LOG(category, format, ...) DEBUG_LOG_BASE(category, Log, format, ##__VA_ARGS__)
#define DEBUG_WARNING(category, format, ...) DEBUG_LOG_BASE(category, Warning, format, ##__VA_ARGS__)
#define DEBUG_ERROR(category, format, ...) DEBUG_LOG_BASE(category, Error, format, ##__VA_ARGS__)
