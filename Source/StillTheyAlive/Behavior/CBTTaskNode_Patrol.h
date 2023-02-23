#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Patrol.generated.h"


UCLASS()
class STILLTHEYALIVE_API UCBTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_Patrol();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
