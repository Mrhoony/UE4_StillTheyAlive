#pragma once

#include "CoreMinimal.h"
#include "Perk/CPerk.h"
#include "CWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Melee,Magic,Max
};

UCLASS()
class STILLTHEYALIVE_API ACWeapon : public ACPerk
{
	GENERATED_BODY()

public:
	ACWeapon();	
	
public:
	virtual void L_Action() override;

public:
	UPROPERTY(EditDefaultsOnly)
	EWeaponType WeaponType;


	float Damage = 5.f;
};
