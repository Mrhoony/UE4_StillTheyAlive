#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CFloorAttack.h"
#include "CFloorBlackhole.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACFloorBlackhole : public ACFloorAttack
{
	GENERATED_BODY()

public:
	ACFloorBlackhole();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	void End_Action();
	UFUNCTION()
		void DamageAction();
	UFUNCTION()
		void Finish();

private:
	TArray<class ACharacter*> HittedCharacters;
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* BlackHole;
};
