#include "Task_BossRange.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/Enemies/CEnemy_Boss.h"

UTask_BossRange::UTask_BossRange()
{
	NodeName = "Range";

	bNotifyTick = true;
}

EBTNodeResult::Type UTask_BossRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());
	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	if (state->IsIdle())
	{
		state->SetAction();
		aiPawn->PlayRangeAttack();
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::InProgress;
}

void UTask_BossRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	if (state->IsIdle())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

