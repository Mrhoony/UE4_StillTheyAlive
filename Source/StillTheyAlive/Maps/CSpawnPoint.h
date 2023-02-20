#pragma once

#include "CoreMinimal.h"
#include "Maps/CGuidePoint.h"
#include "CSpawnPoint.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACSpawnPoint : public ACGuidePoint
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	
private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Point")
		class ACWayPoint* FirstPoint;
};
