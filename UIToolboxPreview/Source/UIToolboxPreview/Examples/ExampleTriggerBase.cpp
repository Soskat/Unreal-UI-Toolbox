#include "ExampleTriggerBase.h"

#include "CoreUIUtils.h"
#include "DebugReturnMacros.h"
#include "ExamplePlayerController.h"
#include "NativeGameplayTags.h"
#include "UI_InformationPrompt.h"
#include "Kismet/GameplayStatics.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_GAME, "UI.Layers.Game");

void AExampleTriggerBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (const auto* Pawn = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		RETURN_ON_FALSE(Pawn == OtherActor);
		
		if (AExamplePlayerController* PC = Cast<AExamplePlayerController>(Pawn->Controller))
		{
			PC->SetExampleTrigger(this);
		}

		if (this->InteractionPromptWidget != nullptr)
		{
			this->InteractionPrompt = Cast<UUI_InformationPrompt>(UCoreUIUtils::PushContentToLayer(this,
				TAG_UI_LAYER_GAME,
				this->InteractionPromptWidget));
			if (IsValid(this->InteractionPrompt))
			{
				this->InteractionPrompt->SetInformationText(this->InformationText);
			}
		}
	}
}

void AExampleTriggerBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (const auto* Pawn = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		RETURN_ON_FALSE(Pawn == OtherActor);
		
		if (AExamplePlayerController* PC = Cast<AExamplePlayerController>(Pawn->Controller))
		{
			PC->SetExampleTrigger(nullptr);
		}

		UCoreUIUtils::PopContentFromLayer(this->InteractionPrompt);
	}
}

void AExampleTriggerBase::ExecuteExample()
{
	OnExecuteExample();
}
