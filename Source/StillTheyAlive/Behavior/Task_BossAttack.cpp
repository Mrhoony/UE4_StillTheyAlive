#include "Task_BossAttack.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/Enemies/CEnemy_Boss.h"

UTask_BossAttack::UTask_BossAttack()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());
	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);
	if (state->IsIdle())
	{
		state->SetAction();
		aiPawn->PlayAttack();
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UTask_BossAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	if (state->IsIdle())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
