#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

public:
	void Move(FVector GoalPoint);

protected:
	virtual void BeginPlay() override;
};
