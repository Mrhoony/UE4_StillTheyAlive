#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFloorAttack.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACFloorAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFloorAttack();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box;
protected:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Scene;

public:
	class ACWeapon* OwnerWeapon;
	class ACharacter* OwnerCharacter;
};
