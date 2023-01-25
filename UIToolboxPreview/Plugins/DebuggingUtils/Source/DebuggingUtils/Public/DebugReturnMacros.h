#pragma once

#include "CoreMinimal.h"

#define RETURN_ARG_ON_INVALID(cond, ret)	\
	if (IsValid(cond) == false)				\
	{										\
		return ret;							\
	}
#define RETURN_ON_INVALID(cond)	\
	if (IsValid(cond) == false)	\
	{							\
		return;					\
	}

#define RETURN_ARG_ON_TRUE(cond, ret)	\
	if (cond)							\
	{									\
		return ret;						\
	}
#define RETURN_ON_TRUE(cond) RETURN_ARG_ON_TRUE(cond, )

#define RETURN_ARG_ON_FALSE(cond, ret)	\
	if (cond == false)					\
	{									\
		return ret;						\
	}
#define RETURN_ON_FALSE(cond) RETURN_ARG_ON_FALSE(cond, )

#define RETURN_ARG_ON_NOT_SET(opt, ret)	\
	if (opt.IsSet() == false)			\
	{									\
		return ret;						\
	}
#define RETURN_ON_NOT_SET(opt) RETURN_ARG_ON_NOT_SET(opt, )

#define RETURN_ARG_ON_EMPTY(list, ret)	\
	if (list.Num() == 0)				\
	{									\
		return ret;						\
	}
#define RETURN_ON_EMPTY(list) RETURN_ARG_ON_EMPTY(list, )
