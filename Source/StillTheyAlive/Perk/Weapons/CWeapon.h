#pragma once

#include "CoreMinimal.h"
#include "Perk/CPerk.h"
#include "CWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Rifle,Magic,Max
};

UCLASS()
class STILLTHEYALIVE_API ACWeapon : public ACPerk
{
	GENERATED_BODY()

public:
	ACWeapon();	
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
	EWeaponType WeaponType;


	float Damage = 5.f;
};
