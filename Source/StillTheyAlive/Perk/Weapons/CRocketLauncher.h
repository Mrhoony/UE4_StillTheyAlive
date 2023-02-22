#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CWeapon.h"
#include "CRocketLauncher.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACRocketLauncher : public ACWeapon
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void WeaponTypeChanged() override;
	virtual void TechAction() override;
	
public:
	ACRocketLauncher();

private:
	bool Zoomin = false;
};
