#pragma once

#include "CoreMinimal.h"

#include "GameUIManagerSubsystem.generated.h"

class UGameUIPolicy;
class UBaseLocalPlayer;
class UUI_GameLayout;

UCLASS()
class COREUIARCHITECTURE_API UGameUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	void SetGameUIPolicy(UGameUIPolicy* NewPolicy);
	UGameUIPolicy* GetCurrentGameUIPolicy() const
	{
		return this->CurrentUIPolicy;
	}

	UUI_GameLayout* GetGameLayoutForPlayer(ULocalPlayer* LocalPlayer);

private:
	UFUNCTION()
	void RegisterLocalPlayer(ULocalPlayer* LocalPlayer);
	UFUNCTION()
	void UnregisterLocalPlayer(ULocalPlayer* LocalPlayer);
	
	UPROPERTY(Transient)
	UGameUIPolicy* CurrentUIPolicy = nullptr;

	UPROPERTY(Transient)
	TMap<UBaseLocalPlayer*, UUI_GameLayout*> GameLayouts = {};
};