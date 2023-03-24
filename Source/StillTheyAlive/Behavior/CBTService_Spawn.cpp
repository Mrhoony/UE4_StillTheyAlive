#include "CBTService_Spawn.h"
#include "Global.h"
#include "Characters/Players/CSpawnCharacter.h"
#include "Characters/Players/CAIControllerSpawn.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "GameFrameWork/Character.h"

UCBTService_Spawn::UCBTService_Spawn()
{
	NodeName = "Spawn";
}

void UCBTService_Spawn::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIControllerSpawn* controller = Cast<ACAIControllerSpawn>(OwnerComp.GetOwner());
	CheckNull(controller);
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behavior);
	ACSpawnCharacter* aiPawn = Cast<ACSpawnCharacter>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	/*if (state->IsHit())
	{
		behavior->SetHittedMode();
		return;
	}*/
	
	ACharacter* target = behavior->GetTarget();
	if (target == nullptr)
	{
		behavior->SetWaitMode();
		return;
	}
	else
	{
		UCStateComponent* targetState = CHelpers::GetComponent<UCStateComponent>(target);
		if (targetState->IsDead())
		{
			behavior->SetPatrolMode();
			return;
		}
	}

	float distane = aiPawn->GetDistanceTo(target);

	if (distane < 150.f)
	{
		behavior->SetActionMode();
		
		return;
	}
	else
	{
		behavior->SetApproachMode();
		return;
	}
}
