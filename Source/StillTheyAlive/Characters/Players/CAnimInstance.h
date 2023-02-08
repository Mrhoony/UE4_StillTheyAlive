#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Perk/CPerk.h"
#include "Components/CStateComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	//UFUNCTION()
		//void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

	//UFUNCTION()
	//	void OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType);

//=======================================================
// [Variables]
//=======================================================
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere) float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere) float Direction;
	//UPROPERTY(BlueprintReadOnly, EditAnywhere) EActionType ActionType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere) bool IsFalling;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere) EStateTypes StateType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere) EPerkType PerkType;
};
