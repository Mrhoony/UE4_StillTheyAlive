#pragma once

#include "CoreMinimal.h"
#include "Characters/CAICharacter.h"
#include "Characters/ICharacter.h"
#include "CEnemy.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACEnemy : public ACAICharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

public:
	virtual void Hitted() override;
	virtual void Dead() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType) override;

	EPathFollowingRequestResult::Type Move(FVector GoalPoint);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastDead();
		void MulticastDead_Implementation();

	UFUNCTION(NetMulticast, Reliable)
		void End_Dead();
		void End_Dead_Implementation();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCDissolveComponent* Dissolve;

	TSubclassOf<class ACUltimate> SpawnUltimate;
private:
	FVector MovePoint;
	bool isDead;
};
