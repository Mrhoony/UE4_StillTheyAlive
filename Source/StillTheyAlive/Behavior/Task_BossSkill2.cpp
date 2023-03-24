#include "Task_BossSkill2.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/Enemies/CEnemy_Boss.h"

UTask_BossSkill2::UTask_BossSkill2()
{
	NodeName = "Skill2";

	bNotifyTick = true;
}

EBTNodeResult::Type UTask_BossSkill2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());
	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);
	if (state->IsIdle())
	{
		state->SetAction();
		aiPawn->PlaySkill2();
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UTask_BossSkill2::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());

	ACEnemy_Boss* aiPawn = Cast<ACEnemy_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	if (state->IsIdle())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

