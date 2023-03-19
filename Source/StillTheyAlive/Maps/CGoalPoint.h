#pragma once

#include "CoreMinimal.h"
#include "Maps/CGuidePoint.h"
#include "CGoalPoint.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACGoalPoint : public ACGuidePoint
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
