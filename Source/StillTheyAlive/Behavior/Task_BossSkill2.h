#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_BossSkill2.generated.h"

UCLASS()
class STILLTHEYALIVE_API UTask_BossSkill2 : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_BossSkill2();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
