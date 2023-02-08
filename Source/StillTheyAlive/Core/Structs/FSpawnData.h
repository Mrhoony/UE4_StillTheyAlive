#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSpawnData.generated.h"

USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere) int	Round;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int	Wave;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TSubclassOf<class ACharacter> Monster;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int Num;
};

UCLASS()
class STILLTHEYALIVE_API UFSpawnData : public UObject { GENERATED_BODY() };
