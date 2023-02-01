#pragma once

#include "CoreMinimal.h"
#include "GameDialogDescriptor.generated.h"

/** Possible results from a dialog */
UENUM(BlueprintType)
enum class EDialogResult : uint8
{
	/** The "yes" button was pressed */
	Confirmed,
	/** The "no" button was pressed */
	Declined,
	/** The "ignore/cancel" button was pressed */
	Cancelled,
	/** The dialog was explicitly killed (no user input) */
	Killed,
	Unknown UMETA(Hidden)
};


USTRUCT(BlueprintType)
struct FGameDialogAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogResult Result = EDialogResult::Unknown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayText = {};
};


UCLASS(BlueprintType, Blueprintable)
class COREUIARCHITECTURE_API UGameDialogDescriptor : public UObject
{
	GENERATED_BODY()

public:
	/** The header of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Header = {};

	/** The body of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Body = {};
	
	/** Possible actions to perform withing given dialog */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameDialogAction> PossibleActions = {};
};

DECLARE_DELEGATE_OneParam(FMessagingResultDelegate, EDialogResult /* Result */);
