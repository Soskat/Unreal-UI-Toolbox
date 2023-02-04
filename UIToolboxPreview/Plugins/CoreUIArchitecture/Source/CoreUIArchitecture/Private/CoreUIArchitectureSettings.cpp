#include "CoreUIArchitectureSettings.h"

TSubclassOf<UUI_GameLayout> UCoreUIArchitectureSettings::GetGameLayoutWidgetClass() const
{
	if (this->GameLayoutWidgetClass != nullptr)
	{
		return this->GameLayoutWidgetClass.LoadSynchronous();
	}
	return nullptr;
}
