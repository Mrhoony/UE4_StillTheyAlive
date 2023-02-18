#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CWeapon.h"
#include "CRocketLauncher.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACRocketLauncher : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACRocketLauncher();
protected:
	virtual void BeginPlay() override;
public:
	virtual void WeaponTypeChanged() override;

	virtual void TechAction() override;

private:
	bool Zoomin = false;
};
