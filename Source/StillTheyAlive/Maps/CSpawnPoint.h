#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "CSpawnPoint.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACSpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		int Index;
};
