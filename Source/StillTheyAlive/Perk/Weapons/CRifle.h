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

protected:
	virtual void BeginPlay() override;

public:
	virtual void TechAction() override;
	virtual void DivAction() override;
	virtual void EndAction() override;
	virtual void WeaponTypeChanged() override;
	virtual FVector SocketLocation() override;

private:
	void OnZoom();
	void OffZoom();
	void Fire();

private:
	class USpringArmComponent* OwnerSpringArm;
	class UCameraComponent* OwnerCamera;
private:
	bool Zoom;
	FTimerHandle AutoFireTimer;
};
