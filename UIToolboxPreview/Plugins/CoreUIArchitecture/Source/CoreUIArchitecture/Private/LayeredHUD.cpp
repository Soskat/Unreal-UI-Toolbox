#include "LayeredHUD.h"

#include "GameLayoutWidget.h"

ALayeredHUD::ALayeredHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ALayeredHUD::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = GetOwningPlayerController())
	{
		if (const TSubclassOf<UGameLayoutWidget> LayoutWidgetClass = this->LayoutClass.LoadSynchronous())
		{
			this->RootLayout = CreateWidget<UGameLayoutWidget>(PC, LayoutWidgetClass, "LayeredHUD");
			if (this->RootLayout != nullptr)
			{
				this->RootLayout->AddToPlayerScreen(0);
			}
		}
	}
}

void ALayeredHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (IsValid(this->RootLayout))
	{
		this->RootLayout->RemoveFromParent();
	}
}

UGameLayoutWidget* ALayeredHUD::GetGameLayoutWidget() const
{
	return this->RootLayout;
}
