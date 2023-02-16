#include "CEnemy.h"
#include "Global.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CDeckComponent.h"
#include "CAIController.h"

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

	CLog::Print(DamageValue);

	Status->DecreaseHealth(DamageValue);

	if (Status->GetHealth() <= 0.f)
	{
		State->SetDead();
		return DamageValue;
	}

	State->SetHit();

	return DamageValue;
}
