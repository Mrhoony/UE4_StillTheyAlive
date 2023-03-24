#include "Task_Boss2Page.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/Enemies/CEnemy_Boss.h"

UTask_Boss2Page::UTask_Boss2Page()
{
	NodeName = "2Page";

	bNotifyTick = true;
}

EBTNodeResult::Type UTask_Boss2Page::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());
	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);
	if (state->IsIdle())
	{
		state->SetAction();
		aiPawn->Page2Skill();
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UTask_Boss2Page::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	if (state->IsIdle())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

