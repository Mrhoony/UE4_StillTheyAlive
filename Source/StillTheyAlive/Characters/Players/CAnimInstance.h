#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

<<<<<<< HEAD
#include "Components/CStateComponent.h"
#include "Perk/CPerk.h"
=======
//#include "Components/CActionComponent.h"
>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b

#include "CAnimInstance.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
<<<<<<< HEAD
	UFUNCTION()
		void OnPerkTypeChanged(EPerkType InPrevType, EPerkType InNewType);
=======
	//UFUNCTION()
		//void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);
>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b

	UFUNCTION()
		void OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType);

//=======================================================
// [Variables]
//=======================================================
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere) float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere) float Direction;
<<<<<<< HEAD
	UPROPERTY(BlueprintReadOnly, EditAnywhere) bool IsFalling;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere) EStateTypes StateType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere) EPerkType PerkType;
=======
	//UPROPERTY(BlueprintReadOnly, EditAnywhere) EActionType ActionType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere) bool IsFalling;
>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b
};
