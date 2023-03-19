#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_BossSkill1.generated.h"

UCLASS()
class STILLTHEYALIVE_API UTask_BossSkill1 : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_BossSkill1();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
