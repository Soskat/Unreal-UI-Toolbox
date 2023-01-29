#include "GameUIPolicy.h"

TSubclassOf<UUI_GameLayout> UGameUIPolicy::GetGameLayoutWidgetClass() const
{
	return this->GameLayoutWidgetClass.LoadSynchronous();
}
