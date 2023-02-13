#pragma once

#include "CoreMinimal.h"
#include "Perk/CDoAction.h"
#include "CDoAction_Trap.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACDoAction_Trap : public ACDoAction
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void DoAction_L() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation);

private:
	class APlayerController* PlayerController;
	class UStaticMeshComponent* StaticMesh;

	class ACTrap* TrapObject;

	FVector DecalLocation;
	FRotator DecalRotation;
};
