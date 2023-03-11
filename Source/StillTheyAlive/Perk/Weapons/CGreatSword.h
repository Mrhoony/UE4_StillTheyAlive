#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CWeapon.h"
#include "CGreatSword.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACGreatSword : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACGreatSword();

	virtual void WeaponTypeChanged() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TechAction() override;
	virtual void EndTechAction() override;
	virtual void Ultimate() override;
	virtual void Begin_Ultimate() override;

	virtual void ChargingMontage() override;
};
