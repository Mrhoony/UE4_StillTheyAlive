#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CWeapon.h"
#include "CSword_bbadda.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACSword_bbadda : public ACWeapon
{
	GENERATED_BODY()

public:
	ACSword_bbadda();

	virtual void WeaponTypeChanged() override;

protected:
	virtual void BeginPlay() override;
};
