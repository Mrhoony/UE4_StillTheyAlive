#include "CBTTaskNode_Action.h"
#include "Global.h"
#include "Characters/Enemies/CEnemy.h"
#include "Characters/Enemies/CAIController.h"
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

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());

	ACEnemy* aiPawn = Cast<ACEnemy>(controller->GetPawn());
	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(aiPawn);

	TotalTime = 0.f;

	deck->PerkAction();

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());

	ACEnemy* aiPawn = Cast<ACEnemy>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	TotalTime += DeltaSeconds;

	if (state->IsIdle() && TotalTime > Delay)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
