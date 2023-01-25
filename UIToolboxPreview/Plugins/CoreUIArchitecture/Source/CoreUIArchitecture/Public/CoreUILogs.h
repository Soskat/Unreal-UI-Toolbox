#pragma once

#include "CoreMinimal.h"
#include "DebugLogs.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCoreUI, Log, Log);

#define CORE_UI_LOG(format, ...) DEBUG_LOG(LogCoreUI, format, ##__VA_ARGS__)
#define CORE_UI_WARNING(format, ...) DEBUG_WARNING(LogCoreUI, format, ##__VA_ARGS__)
#define CORE_UI_ERROR(format, ...) DEBUG_ERROR(LogCoreUI, format, ##__VA_ARGS__)
