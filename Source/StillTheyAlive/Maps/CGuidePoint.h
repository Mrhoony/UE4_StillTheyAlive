#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "CGuidePoint.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACGuidePoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:
	ACGuidePoint();

public:
	UPROPERTY(EditAnywhere, Category = "Point")
		class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, Category = "Point")
		int32 PathNum;
private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Scene;
};
