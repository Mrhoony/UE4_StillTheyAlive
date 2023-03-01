#include "CEnemy.h"
#include "Global.h"

#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CDeckComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CDissolveComponent.h"
#include "Components/CUltimateComponent.h"
#include "Core/GameModes/CStoryGameMode.h"
#include "Core/GameModes/CPlayGameMode.h"
#include "Characters/Enemies/CAIController.h"
#include "Characters/Players/CUltimate.h"

#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Health.h"
#include "GameFramework/CharacterMovementComponent.h"

ACEnemy::ACEnemy()
{
	CHelpers::CreateActorComponent(this, &Dissolve, "Dissolve");
	CHelpers::GetClass<ACUltimate>(&SpawnUltimate, "Blueprint'/Game/_Project/Perks/BP_CUltimate.BP_CUltimate_C'");
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
	
	isDead = true;
	
	//NameWidget->SetVisibility(false);
	HealthWidget->SetVisibility(false);

	//All Weapon Collision Disable
	Deck->Dead();

	//Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->GlobalAnimRateScale = 0.f;
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Ultimate
	FVector location = (GetActorForwardVector() + GetActorUpVector() + GetActorRightVector()) * 300;
	location.Rotation();

	for (int32 i = 1; i < 4; i++)
	{
		location* i;
		ACUltimate* ultimate = GetWorld()->SpawnActorDeferred<ACUltimate>(SpawnUltimate, GetActorTransform());
		ultimate->SetDirection(location);
		UGameplayStatics::FinishSpawningActor(ultimate, GetActorTransform());
	}

	Dissolve->Play();

	//End_Dead
	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 3.f, false);
}

void ACEnemy::End_Dead()
{
	Dissolve->Stop();

	Deck->EndDead();

	ACStoryGameMode* gameMode = Cast<ACStoryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->DecreaseLifes();

	Destroy();
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Causer = DamageCauser;
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

	//AddImpulse를 위한 준비
	FVector attackerForward = Attacker->GetActorForwardVector();
	FVector attackerUp = Attacker->GetActorUpVector();
	attackerForward.Normalize();
	attackerUp.Normalize();

	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		const FRadialDamageEvent* radialDamageEvent = static_cast<const FRadialDamageEvent*>(&DamageEvent);
		GetCharacterMovement()->AddImpulse((attackerForward + attackerUp) * 300.0f, true);
	//	CLog::Print("TakeRadialDamage");
	//	CLog::Print(DamageValue);
	}
	else
	{
	//	CLog::Print("TakeNormalDamage");
		Status->DecreaseHealth(DamageValue);
	}

	UCUserWidget_Health* healthWidgetObject = Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidgetObject)
		healthWidgetObject->Update(Status->GetHealth(), Status->GetMaxHealth());

	// Ultimate
	UCUltimateComponent* ultimate = CHelpers::GetComponent<UCUltimateComponent>(Attacker);
	

	if (Status->GetHealth() <= 0.f)
	{
		if (isDead == true) return DamageValue;

		State->SetDead();
		return DamageValue;
	}

	//State->SetHit();

	return DamageValue;
}
