#include "CBTTaskNode_Action.h"
#include "Global.h"

#include "Characters/CAICharacter.h"
#include "AIController.h"
#include "Components/CDeckComponent.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	NodeName = "Action";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	ACAICharacter* aiPawn = Cast<ACAICharacter>(controller->GetPawn());
	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(aiPawn);

	aiPawn->ActionCoolTime = aiPawn->ActionMaxCoolTime; // X
	controller->StopMovement();
	deck->PerkAction();
	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	ACAICharacter* aiPawn = Cast<ACAICharacter>(controller->GetPawn());
	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(aiPawn);
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	if (state->IsIdle() && aiPawn->ActionCoolTime == 0)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}		
}
