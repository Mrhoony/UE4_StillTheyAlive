#include "CGoalPoint.h"
#include "Components/BoxComponent.h"

void ACGoalPoint::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACGoalPoint::OnComponentBeginOverlap);
}

void ACGoalPoint::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
