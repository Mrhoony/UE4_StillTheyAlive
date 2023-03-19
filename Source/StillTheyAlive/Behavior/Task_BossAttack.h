#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_BossAttack.generated.h"

UCLASS()
class STILLTHEYALIVE_API UTask_BossAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_BossAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
