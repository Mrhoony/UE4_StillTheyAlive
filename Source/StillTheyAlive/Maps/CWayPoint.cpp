#include "CWayPoint.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Characters/Enemies/CEnemy.h"
#include "Characters/Enemies/CAIController.h"

void ACWayPoint::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACWayPoint::OnComponentBeginOverlap);
}

void ACWayPoint::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	CheckNull(enemy);
	ACAIController* aicontoller = Cast<ACAIController>(enemy->GetController());
	if (!!NextPoint)
	{
		if(!!aicontoller)
			aicontoller->SetLoactionKey(NextPoint->GetActorLocation());
	}
}