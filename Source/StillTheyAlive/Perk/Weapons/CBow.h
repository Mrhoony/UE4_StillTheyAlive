#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CWeapon.h"
#include "CBow.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACBow : public ACWeapon
{
	GENERATED_BODY()

public:
	ACBow();

protected:
	virtual void BeginPlay() override;

public:
	virtual void EndAction() override;
	virtual void WeaponTypeChanged() override;
	virtual FVector SocketLocation() override;

private:
	void Fire();

private:
	class USpringArmComponent* OwnerSpringArm;
	class UCameraComponent* OwnerCamera;
private:
	bool Zoom;
	FTimerHandle AutoFireTimer;
};
