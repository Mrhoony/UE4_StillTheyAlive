#include "CAIController.h"
#include "Global.h"

#include "CEnemy.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerEnemy = Cast<ACEnemy>(InPawn);

	MoveToLocation(FVector(-2300, 2000, 100));
	CLog::Log(this);
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
