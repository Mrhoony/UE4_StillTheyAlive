#pragma once

#include "CoreMinimal.h"
#include "Characters/CAICharacter.h"
#include "Characters/ICharacter.h"
#include "CSpawnCharacter.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACSpawnCharacter : public ACAICharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACSpawnCharacter();

public:
	virtual void Hitted() override;
	virtual void Dead() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType) override;
protected:
	virtual void BeginPlay() override;


private:
	void End_Dead();
};
