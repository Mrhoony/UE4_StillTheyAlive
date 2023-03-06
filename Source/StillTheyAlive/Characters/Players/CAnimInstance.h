#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CStateComponent.h"
#include "Components/CDeckComponent.h"
#include "Perk/Weapons/CWeapon.h"
#include "Perk/CPerk.h"
#include "CAnimInstance.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	UFUNCTION()
		void OnWeaponTypeChanged(EWeaponType InNewType);
	UFUNCTION(NetMulticast, Reliable)
		void ServerOnWeaponTypeChanged(EWeaponType InNewType);

//=======================================================
// [Variables]
//=======================================================
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere) float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere) float Direction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere) bool IsFalling;	
	UPROPERTY(BlueprintReadOnly, EditAnywhere) EStateTypes StateType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated) EPerkType PerkType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated) EWeaponType WeaponType;
private:
	UFUNCTION()
		void OnPerkTypeChanged(EPerkType InPrevType, EPerkType InNewType);
	UFUNCTION(NetMulticast, Reliable)
		void ServerOnPerkTypeChanged(EPerkType InPrevType, EPerkType InNewType);
};
