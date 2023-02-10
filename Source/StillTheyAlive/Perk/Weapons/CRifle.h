#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CWeapon.h"
#include "CRifle.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACRifle : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACRifle();

	virtual void WeaponTypeChanged() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TechAction() override;
};
