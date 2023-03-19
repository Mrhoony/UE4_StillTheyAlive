#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FSpawnData.generated.h"

USTRUCT(BlueprintType) 
struct FSpawnData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)		int Round;
	UPROPERTY(EditAnywhere)		int Wave;
	UPROPERTY(EditAnywhere)		int SpawnLocationIndex;
	UPROPERTY(EditAnywhere)		int SpawnCount;
	UPROPERTY(EditAnywhere)		TSubclassOf<class ACharacter> MonsterRef;
};

UCLASS()
class STILLTHEYALIVE_API UFSpawnData : public UObject { GENERATED_BODY() };
