#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FRoundData.generated.h"

USTRUCT(BlueprintType)
struct FRoundData : public FTableRowBase
{
	GENERATED_BODY()
};

UCLASS()
class STILLTHEYALIVE_API UFRoundData : public UObject { GENERATED_BODY() };