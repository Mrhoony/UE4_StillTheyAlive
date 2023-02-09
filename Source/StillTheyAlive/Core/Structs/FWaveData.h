#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "FWaveData.generated.h"

USTRUCT(BlueprintType)
struct FWaveData : public FTableRowBase
{
	GENERATED_BODY()

	/*
	* ��������
	* ���
	*/

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> MonsterRef;
		
	UPROPERTY(EditAnywhere)
		int SpawnAmount;
};

UCLASS()
class STILLTHEYALIVE_API UFWaveData : public UObject { GENERATED_BODY() };
