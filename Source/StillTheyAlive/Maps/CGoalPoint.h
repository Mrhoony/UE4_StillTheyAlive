#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "CGoalPoint.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACGoalPoint : public ATargetPoint
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		int Index;
};
