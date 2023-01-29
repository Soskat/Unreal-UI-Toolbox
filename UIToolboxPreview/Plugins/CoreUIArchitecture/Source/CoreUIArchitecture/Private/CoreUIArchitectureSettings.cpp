#include "CoreUIArchitectureSettings.h"

TSubclassOf<UGameUIPolicy> UCoreUIArchitectureSettings::GetDefaultUIPolicyClass() const
{
	return this->DefaultUIPolicyClass.LoadSynchronous();
}
