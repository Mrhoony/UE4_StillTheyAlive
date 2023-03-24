#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_Boss2Page.generated.h"

UCLASS()
class STILLTHEYALIVE_API UTask_Boss2Page : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_Boss2Page();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
