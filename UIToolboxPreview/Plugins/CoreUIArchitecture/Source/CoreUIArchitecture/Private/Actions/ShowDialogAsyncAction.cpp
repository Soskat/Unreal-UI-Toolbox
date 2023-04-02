#include "CoreUIArchitecture/Public/Actions/ShowDialogAsyncAction.h"

#include "Blueprint/UserWidget.h"
#include "Messaging/GameDialogDescriptor.h"
#include "Messaging/MessagingSubsystem.h"

UShowDialogAsyncAction* UShowDialogAsyncAction::ShowErrorOk(UObject* InWorldContextObject, FText Title, FText Message)
{
	UShowDialogAsyncAction* Action = NewObject<UShowDialogAsyncAction>();
	Action->WorldContextObject = InWorldContextObject;
	Action->RegisterWithGameInstance(InWorldContextObject);
	Action->Descriptor = UGameDialogDescriptor::CreateConfirmationOk(Title, Message);
	Action->bIsConfirmation = false;
	return Action;
}

UShowDialogAsyncAction* UShowDialogAsyncAction::ShowConfirmationOk(UObject* InWorldContextObject, FText Title, FText Message)
{
	UShowDialogAsyncAction* Action = NewObject<UShowDialogAsyncAction>();
	Action->WorldContextObject = InWorldContextObject;
	Action->RegisterWithGameInstance(InWorldContextObject);
	Action->Descriptor = UGameDialogDescriptor::CreateConfirmationOk(Title, Message);
	return Action;
}

UShowDialogAsyncAction* UShowDialogAsyncAction::ShowConfirmationOkCancel(UObject* InWorldContextObject,
	FText Title,
	FText Message)
{
	UShowDialogAsyncAction* Action = NewObject<UShowDialogAsyncAction>();
	Action->WorldContextObject = InWorldContextObject;
	Action->RegisterWithGameInstance(InWorldContextObject);
	Action->Descriptor = UGameDialogDescriptor::CreateConfirmationOkCancel(Title, Message);
	return Action;
}

UShowDialogAsyncAction* UShowDialogAsyncAction::ShowConfirmationYesNo(UObject* InWorldContextObject,
	FText Title,
	FText Message)
{
	UShowDialogAsyncAction* Action = NewObject<UShowDialogAsyncAction>();
	Action->WorldContextObject = InWorldContextObject;
	Action->RegisterWithGameInstance(InWorldContextObject);
	Action->Descriptor = UGameDialogDescriptor::CreateConfirmationYesNo(Title, Message);
	return Action;
}

UShowDialogAsyncAction* UShowDialogAsyncAction::ShowConfirmationCustom(UObject* InWorldContextObject,
	UGameDialogDescriptor* Descriptor)
{
	UShowDialogAsyncAction* Action = NewObject<UShowDialogAsyncAction>();
	Action->WorldContextObject = InWorldContextObject;
	Action->RegisterWithGameInstance(InWorldContextObject);
	Action->Descriptor = Descriptor;

	return Action;
}

void UShowDialogAsyncAction::Activate()
{
	Super::Activate();

	if (IsValid(this->TargetLocalPlayer) == false)
	{
		this->TargetLocalPlayer = TryGetLocalPlayer();
	}

	if (IsValid(this->TargetLocalPlayer))
	{
		auto* MessagingSubsystem = this->TargetLocalPlayer->GetSubsystem<UMessagingSubsystem>();
		check(MessagingSubsystem);

		const FDialogResultDelegate ResultCallback = FDialogResultDelegate::CreateUObject(
			this,
			&ThisClass::HandleDialogResult);

		if (this->bIsConfirmation)
		{
			MessagingSubsystem->ShowConfirmation(this->Descriptor, ResultCallback);
		}
		else
		{
			MessagingSubsystem->ShowError(this->Descriptor, ResultCallback);
		}
		return;
	}
	
	// If we couldn't make the dialog, just handle an unknown result and broadcast nothing
	HandleDialogResult(EDialogResult::Unknown);
}

TObjectPtr<ULocalPlayer> UShowDialogAsyncAction::TryGetLocalPlayer()
{
	if (IsValid(this->WorldContextObject))
	{
		const UUserWidget* UserWidget = Cast<UUserWidget>(this->WorldContextObject);
		if (IsValid(UserWidget))
		{
			return UserWidget->GetOwningLocalPlayer<ULocalPlayer>();
		}

		const APlayerController* PlayerController = Cast<APlayerController>(WorldContextObject);
		if (IsValid(PlayerController))
		{
			return PlayerController->GetLocalPlayer();
		}

		const UWorld* World = WorldContextObject->GetWorld();
		if (IsValid(World))
		{
			const UGameInstance* GameInstance = World->GetGameInstance<UGameInstance>();
			if (IsValid(GameInstance))
			{
				return GameInstance->GetPrimaryPlayerController(false)->GetLocalPlayer();
			}
		}
	}
	return TObjectPtr<ULocalPlayer>{};
}

void UShowDialogAsyncAction::HandleDialogResult(EDialogResult ConfirmationResult)
{
	if (this->OnResult.IsBound())
	{
		this->OnResult.Broadcast(ConfirmationResult);
	}

	SetReadyToDestroy();
}
