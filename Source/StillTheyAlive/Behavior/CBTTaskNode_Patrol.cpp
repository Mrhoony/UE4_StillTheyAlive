#include "CBTTaskNode_Patrol.h"
#include "Global.h"
#include "Characters/Enemies/CAIController.h"
#include "Characters/Enemies/CEnemy.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* aiPawn = Cast<ACEnemy>(controller->GetPawn());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	UCStateComponent* State = CHelpers::GetComponent<UCStateComponent>(aiPawn);
	
	if (State->IsIdle() == false) return  EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* aiPawn = Cast<ACEnemy>(controller->GetPawn());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	UCStateComponent* State = CHelpers::GetComponent<UCStateComponent>(aiPawn);
	if (State->IsIdle() == false) return FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	
	FVector location;
	location = behavior->GetLocation();

	EPathFollowingRequestResult::Type type = aiPawn->Move(location);

	if (type == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (type == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
}

