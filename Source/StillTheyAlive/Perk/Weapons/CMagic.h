#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CWeapon.h"
#include "CMagic.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACMagic : public ACWeapon
{
	GENERATED_BODY()

public:
	ACMagic();

	virtual void WeaponTypeChanged() override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void TechAction() override;

};
