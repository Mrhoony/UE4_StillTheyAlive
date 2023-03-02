#pragma once

#include "CoreMinimal.h"
#include "Perk/Weapons/CFloorAttack.h"
#include "CFloorGreat.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACFloorGreat : public ACFloorAttack
{
	GENERATED_BODY()

public:
	ACFloorGreat();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void End_Action();
	UFUNCTION()
	void DamageAction();
	UFUNCTION()
	void Finish();

private:
	TArray<class ACharacter*> HittedCharacters;
};
