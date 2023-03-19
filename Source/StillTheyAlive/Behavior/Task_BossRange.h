#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_BossRange.generated.h"

UCLASS()
class STILLTHEYALIVE_API UTask_BossRange : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_BossRange();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
