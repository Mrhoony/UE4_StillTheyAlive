#include "BTService_Boss.h"
#include "Global.h"

#include "Characters/Players/CPlayer.h"
#include "Characters/Enemies/CEnemy_Boss.h"
#include "Characters/Enemies/CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

#include "GameFrameWork/Character.h"

UBTService_Boss::UBTService_Boss()
{
	NodeName = "Boss";
}

void UBTService_Boss::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(controller);
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behavior);
	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(aiPawn);

	/*if (state->IsHit())
	{
		behavior->SetHittedMode();
		return;
	}*/

	ACharacter* target = behavior->GetTarget();
	if (target == nullptr)
	{
		controller->K2_ClearFocus();

		behavior->SetWaitMode();
		return;
	}

	if (aiPawn->IsSkill3())
	{
		behavior->Set2PageMode();
		return;
	}

	controller->K2_SetFocus(target);
	float distane = aiPawn->GetDistanceTo(target);
	if (aiPawn->IsSkill())
	{
		behavior->SetSkillMode();
		return;
	}
	if (aiPawn->IsSkill2())
	{
		behavior->SetSkill2Mode();
		return;
	}

	if (distane < AttackRange)
	{
		behavior->SetActionMode();
		return;
	}
	else
	{
		if (aiPawn->IsRangeAttack() == true)
		{
			behavior->SetRangeAttackMode();
			return;
		}
		
		if (state->IsIdle())
		{
			behavior->SetApproachMode();
			return;
		}

		behavior->SetWaitMode();
		return;
	}
}
