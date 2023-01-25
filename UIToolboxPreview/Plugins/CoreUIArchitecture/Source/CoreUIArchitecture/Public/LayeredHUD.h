#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LayeredHUD.generated.h"

class UGameLayoutWidget;

UCLASS(Abstract)
class COREUIARCHITECTURE_API ALayeredHUD : public AHUD
{
	GENERATED_BODY()

public:
	ALayeredHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UGameLayoutWidget* GetGameLayoutWidget() const;

private:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UGameLayoutWidget> LayoutClass;

	UPROPERTY(Transient)
	UGameLayoutWidget* RootLayout = nullptr;
};
