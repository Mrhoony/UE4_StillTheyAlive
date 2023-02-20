#include "CEnemy.h"
#include "Global.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CDeckComponent.h"
#include "CAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ACEnemy::ACEnemy()
{
	// Component Settings
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/_Project/Characters/Players/Mannequin/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass<UAnimInstance>(&animInstanceClass, "AnimBlueprint'/Game/_Project/Characters/Players/AB_CPlayer.AB_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	// Create ActorComponent
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Deck, "Deck");
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultController();
}

void ACEnemy::Move(FVector GoalPoint)
{
	Cast<ACAIController>(GetController())->MoveToLocation(GoalPoint);
}

void ACEnemy::Hitted()
{
}

void ACEnemy::Dead()
{
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
		CLog::Print("TakeRadialDamage");
		CLog::Print(DamageValue);
	}
	else
	{
		CLog::Print("TakeNormalDamage");
		Status->DecreaseHealth(DamageValue);

		if (Status->GetHealth() <= 0.f)
		{
			State->SetDead();
			return DamageValue;
		}

		State->SetHit();
	}

	return DamageValue;
}
