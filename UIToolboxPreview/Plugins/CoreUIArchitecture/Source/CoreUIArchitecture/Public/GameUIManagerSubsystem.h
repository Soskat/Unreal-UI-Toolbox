#pragma once

#include "CoreMinimal.h"

#include "GameUIManagerSubsystem.generated.h"

class UGameUIPolicy;
class UBaseLocalPlayer;
class UUI_GameLayout;

/**
 * This subsystem is responsible for managing game layouts widgets for all players.
 * It automatically assign a game layout widget per each local player added to the current game instance.
 */
UCLASS()
class COREUIARCHITECTURE_API UGameUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "Game UI Manager")
	UUI_GameLayout* GetGameLayoutForPlayer(ULocalPlayer* LocalPlayer);

private:
	UFUNCTION()
	void RegisterLocalPlayer(ULocalPlayer* LocalPlayer);

	UFUNCTION()
	void UnregisterLocalPlayer(ULocalPlayer* LocalPlayer);

	UPROPERTY(Transient)
	TSubclassOf<UUI_GameLayout> GameLayoutClass = nullptr;
	
	UPROPERTY(Transient)
	TMap<UBaseLocalPlayer*, UUI_GameLayout*> GameLayouts = {};
};