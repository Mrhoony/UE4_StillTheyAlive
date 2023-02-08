#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FPlayerCharacter.generated.h"

USTRUCT(BlueprintType)
struct FPlayerCharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere) FString	Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	TArray<TSubclassOf<class ACPerk>> HasPerks;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	TArray<bool> HasSkins;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	TSubclassOf<class ACPlayer> character;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	int KillScore;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	int Money;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	bool IsLastCharacter;
};

UCLASS()
class STILLTHEYALIVE_API UFPlayerCharacter : public UObject { GENERATED_BODY() };
