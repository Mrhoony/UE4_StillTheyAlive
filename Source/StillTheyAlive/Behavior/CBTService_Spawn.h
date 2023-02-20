
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Spawn.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCBTService_Spawn : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_Spawn();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
