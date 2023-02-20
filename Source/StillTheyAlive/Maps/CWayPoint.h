#pragma once

#include "CoreMinimal.h"
#include "Maps/CGuidePoint.h"
#include "CWayPoint.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACWayPoint : public ACGuidePoint
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category = "Point")
	ACGuidePoint* NextPoint;
};
