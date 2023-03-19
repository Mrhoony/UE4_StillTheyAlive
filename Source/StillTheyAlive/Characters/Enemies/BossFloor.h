#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CFloorAttack.h"
#include "BossFloor.generated.h"

UCLASS()
class STILLTHEYALIVE_API ABossFloor : public ACFloorAttack
{
	GENERATED_BODY()
public:
	ABossFloor();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void DamageAction();

	UFUNCTION()
		void Finish();

	void End_Action();
private:
	TArray<class ACharacter*> HittedCharacters;
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* SendStrom;

	UPROPERTY(EditDefaultsOnly)
		class UCurveFloat* Curve;

	float AroundSpeed = 300.f;
	float YawAngle;
};
