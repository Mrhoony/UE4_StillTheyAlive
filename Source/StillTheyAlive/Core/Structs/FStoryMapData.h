#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FRoundData.h"
#include "FStoryMapData.generated.h"

USTRUCT(BlueprintType)
struct FStoryMapData : public FTableRowBase
{
	GENERATED_BODY()

		/*
		* 몇라운드
		* 몇웨이브
		* 소환위치인덱스
		* 몇마리
		* 무슨몬스터
		*/

public:
	UPROPERTY(EditAnywhere)
		int Round;

	UPROPERTY(EditAnywhere)
		int Wave;

	UPROPERTY(EditAnywhere)
		int SpawnLocationIndex;

	UPROPERTY(EditAnywhere)
		int SpawnCount;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> MonsterRef;
};

UCLASS()
class STILLTHEYALIVE_API UFStoryMapData : public UObject { GENERATED_BODY() };
