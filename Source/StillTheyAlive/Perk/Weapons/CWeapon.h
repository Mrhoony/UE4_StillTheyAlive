#pragma once

#include "CoreMinimal.h"
#include "Perk/CPerk.h"
#include "CWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Rifle, Magic, GreatSword, RocketLauncher, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponTypeChanged, EWeaponType, InNewType);

UCLASS()
class STILLTHEYALIVE_API ACWeapon : public ACPerk
{
	GENERATED_BODY()

public:
	ACWeapon();	
		
public:
	UFUNCTION()
		virtual void WeaponTypeChanged();
	virtual void ChargingMontage() {};
	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
		EWeaponType WeaponType;

	UPROPERTY(BlueprintAssignable)
		FWeaponTypeChanged OnWeaponTypeChanged;

	float Damage = 5.f;
	int32 ChargingStack;
};
