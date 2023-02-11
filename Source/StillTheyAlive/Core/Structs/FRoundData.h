#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FWaveData.h"
#include "FRoundData.generated.h"

USTRUCT(BlueprintType)
struct FRoundData : public FTableRowBase
{
	GENERATED_BODY()

		/*
		* ¹«½¼¿þÀÌºê
		*/

public:
	

public:
	UPROPERTY(EditAnywhere)
		FWaveData Wave;

	UPROPERTY(EditAnywhere)
		int SpawnCount;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> MonsterRef;
};

UCLASS()
class STILLTHEYALIVE_API UFRoundData : public UObject { GENERATED_BODY() };
