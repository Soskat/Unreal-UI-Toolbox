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
	/** Used for handling unexpected errors */
	Unknown UMETA(Hidden)
};


/** Dialog option characteristics. */
USTRUCT(BlueprintType)
struct FGameDialogAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogResult Result = EDialogResult::Unknown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayText = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDesiredFocusTarget = false;
};


/** A set of information needed to display a dialog widget. */
UCLASS(BlueprintType, Blueprintable)
class COREUIARCHITECTURE_API UGameDialogDescriptor : public UObject
{
	GENERATED_BODY()

public:
	static TObjectPtr<UGameDialogDescriptor> CreateConfirmationOk(const FText& Header, const FText& Body);
	static TObjectPtr<UGameDialogDescriptor> CreateConfirmationOkCancel(const FText& Header, const FText& Body);
	static TObjectPtr<UGameDialogDescriptor> CreateConfirmationYesNo(const FText& Header, const FText& Body);
	
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

DECLARE_DELEGATE_OneParam(FDialogResultDelegate, EDialogResult /* Result */);
