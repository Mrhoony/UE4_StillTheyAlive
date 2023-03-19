#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Boss.generated.h"

UCLASS()
class STILLTHEYALIVE_API UBTService_Boss : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_Boss();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float AttackRange = 300.f;
};
