#include "CBTService_Enemy.h"
#include "Global.h"

#include "Characters/Players/CPlayer.h"
#include "Characters/Enemies/CEnemy.h"
#include "Characters/Enemies/CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"

#include "GameFrameWork/Character.h"

UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "Enemy";
}

void UCBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(controller);
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behavior);
	ACEnemy* aiPawn = Cast<ACEnemy>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	/*if (state->IsHit())
	{
		behavior->SetHittedMode();
		return;
	}*/

	ACharacter* target = behavior->GetTarget();
	if (target == nullptr)
	{
		controller->K2_ClearFocus();
		if (!behavior->GetLocation().IsNearlyZero())
		{
			behavior->SetPatrolMode();
			return;
		}
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

	controller->K2_SetFocus(target);
	if (distane < controller->GetBehaviorRange())
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
