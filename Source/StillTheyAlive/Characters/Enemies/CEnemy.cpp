#include "CEnemy.h"
#include "Global.h"

#include "AIController.h"

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
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultController();
}

void ACEnemy::Move(FVector GoalPoint)
{
	Cast<AAIController>(GetController())->MoveToLocation(GoalPoint);
}