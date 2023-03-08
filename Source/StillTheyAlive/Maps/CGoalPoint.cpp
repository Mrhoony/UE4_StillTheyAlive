#include "CGoalPoint.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Core/GameModes/CStoryGameMode.h"
#include "Characters/Enemies/CEnemy.h"

void ACGoalPoint::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACGoalPoint::OnComponentBeginOverlap);
}

void ACGoalPoint::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (!!enemy)
	{
		ACStoryGameMode* gameMode = Cast<ACStoryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (!!gameMode)
		{
			gameMode->DecreaseLifes();
			gameMode->DecreaseRoundCount();
			enemy->Destroy();
		}
	}
}
