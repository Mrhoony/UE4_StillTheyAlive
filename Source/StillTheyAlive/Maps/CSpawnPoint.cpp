#include "CSpawnPoint.h"
#include "Global.h"
#include "CWayPoint.h"
#include "Components/BoxComponent.h"
#include "Characters/Enemies/CEnemy.h"
#include "Characters/Enemies/CAIController.h"

void ACSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACSpawnPoint::OnComponentBeginOverlap);
}

void ACSpawnPoint::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	CheckNull(enemy);
	ACAIController* aicontoller = Cast<ACAIController>(enemy->GetController());
	if (!!FirstPoint)
		aicontoller->SetLoactionKey(FirstPoint->GetActorLocation());
}
