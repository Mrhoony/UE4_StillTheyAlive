#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACEnemy : public ACharacter , public IICharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

public:
	virtual void Hitted() override;
	virtual void Dead() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Move(FVector InMoveDest);
	void SetMoveDest(FVector InMoveDest);

protected:
	virtual void BeginPlay() override;


private:
	// Actor Components
	UPROPERTY(VisibleDefaultsOnly) class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly) class UCDeckComponent* Deck;
	UPROPERTY(VisibleDefaultsOnly) class UCStateComponent* State;
	// Scene Components
	UPROPERTY(VisibleDefaultsOnly) class UWidgetComponent* NameWidget;
	UPROPERTY(VisibleDefaultsOnly) class UWidgetComponent* HealthWidget;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;

private:
	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;
	FVector MovePoint;
};
