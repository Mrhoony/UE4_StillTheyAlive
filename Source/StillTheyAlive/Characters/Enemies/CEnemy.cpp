#include "CEnemy.h"
#include "Global.h"

#include "Components/CUltimateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CDeckComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CDissolveComponent.h"
#include "Core/GameModes/CStoryGameMode.h"
#include "Core/GameModes/CPlayGameMode.h"
#include "Characters/Enemies/CAIController.h"

#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Health.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perk/ActionData/CThrow.h"


ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent(this, &Dissolve, "Dissolve");
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
}

EPathFollowingRequestResult::Type ACEnemy::Move(FVector GoalPoint)
{
	AAIController* aiController = Cast<AAIController>(GetController());
	if (aiController == nullptr) return EPathFollowingRequestResult::Failed;
	return aiController->MoveToLocation(GoalPoint, 50.f, false);
}

void ACEnemy::OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType)
{
	switch (InNewType)
	{
	case EStateTypes::Hit:		Hitted();	break;
	case EStateTypes::Dead:		Dead();		break;
	}
}

void ACEnemy::Hitted()
{
}

void ACEnemy::Dead()
{
	CheckFalse(State->IsDead());

	//NameWidget->SetVisibility(false);
	HealthWidget->SetVisibility(false);

	//All Weapon Collision Disable
	Deck->Dead();


	FVector location = (GetActorForwardVector() + GetActorUpVector() + GetActorRightVector()) * 300;
	location.Rotation();

	for (int32 i = 1; i < 4; i++)
	{
		location * i;
		ACUltimate* ultimate = GetWorld()->SpawnActorDeferred<ACUltimate>(SpawnUltimate, GetActorTransform());
		ultimate->SetDirection(location);
		UGameplayStatics::FinishSpawningActor(ultimate, GetActorTransform());
	}

	Dissolve->Play();

	ACStoryGameMode* gameMode = Cast<ACStoryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!!gameMode)
		gameMode->DecreaseRoundCount();

	//Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->GlobalAnimRateScale = 0.f;
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Dissolve->Play();


	//End_Dead
	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 3.f, false);
}

void ACEnemy::End_Dead()
{
	Dissolve->Stop();

	Deck->EndDead();

	Destroy();
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Causer = DamageCauser;
	if(EventInstigator != nullptr)
		Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		const FRadialDamageEvent* radialDamageEvent = static_cast<const FRadialDamageEvent*>(&DamageEvent);
		Status->DecreaseHealth(DamageValue);
	}
	else
	{
		Status->DecreaseHealth(DamageValue);
	}

	UCUserWidget_Health* healthWidgetObject = Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidgetObject)
		healthWidgetObject->Update(Status->GetHealth(), Status->GetMaxHealth());

	if (Status->GetHealth() <= 0.f)
	{
		State->SetDead();
		return DamageValue;
	}

	//State->SetHit();

	return DamageValue;
}
