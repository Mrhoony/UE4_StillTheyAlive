#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FStoryMapData.generated.h"

USTRUCT(BlueprintType)
struct FStoryMapData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)		FString Map;
	UPROPERTY(EditAnywhere)		FString DataPath;
	UPROPERTY(EditAnywhere)		float Money;
	UPROPERTY(EditAnywhere)		int Lifes;
};

UCLASS()
class STILLTHEYALIVE_API UFStoryMapData : public UObject { GENERATED_BODY() };
