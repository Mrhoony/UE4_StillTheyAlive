#include "CBTService_Enemy.h"
#include "Global.h"
#include "Characters/Players/CPlayer.h"
#include "Characters/Enemies/CEnemy.h"
#include "Characters/Enemies/CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"


UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "Enemy";
}

void UCBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

	ACEnemy* aiPawn = Cast<ACEnemy>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	if (state->IsHit())
	{
		behavior->SetHittedMode();
		return;
	}

	ACPlayer* target = behavior->GetTargetPlayer();
	if (target == nullptr)
	{
		behavior->SetWaitMode();
		return;
	}
	float distane = aiPawn->GetDistanceTo(target);


	if (distane < controller->GetBehaviorRange())
	{
		behavior->SetActionMode();
		return;
	}

}
