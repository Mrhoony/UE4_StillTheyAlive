#include "CBTTaskNode_Speed.h"
#include "Global.h"
#include "Characters/CAICharacter.h"
#include "AIController.h"
#include "Components/CStatusComponent.h"


UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());
	ACAICharacter* aiPawn = Cast<ACAICharacter>(controller->GetPawn());
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(aiPawn);

	status->SetSpeed(Type);

	return EBTNodeResult::Succeeded;
}