#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/CEnemy.h"
#include "CEnemy_Boss.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACEnemy_Boss : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemy_Boss();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Dead() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE bool IsRangeAttack() { return bRangeAttack; }
	FORCEINLINE bool IsSkill() { return bSkill; }
	FORCEINLINE bool IsSkill2() { return bSkill2; }
	FORCEINLINE bool IsSkill3() { return Page2; }


	UFUNCTION(NetMulticast, Reliable)
		void PlayRangeAttack();
		void PlayRangeAttack_Implementation();
		UFUNCTION(NetMulticast, Reliable)
		void BeginRangeAttack();

	UFUNCTION(NetMulticast, Reliable)
		void PlaySkill();
		void PlaySkill_Implementation();
		void BeginSkill();

	UFUNCTION(NetMulticast, Reliable)
		void PlaySkill2();
		void PlaySkill2_Implementation();
		void BeginSkill2();
	UFUNCTION(NetMulticast, Reliable)
		void Page2Skill();
		void Page2Skill_Implementation();
	UFUNCTION()
		void BeginPage2Skill();
	UFUNCTION()
		void TimerSkill();
	UFUNCTION()
		void TimerEndSkill();

	UFUNCTION(NetMulticast, Reliable)
	void PlayAttack();
	void PlayAttack_Implementation();

	void BeginAttack();
	void EndAttack();
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	float MAXCT_RangeAttack = 15.f;
	float CT_RangeAttack;
	bool bRangeAttack = false;

	UPROPERTY(EditAnywhere)
	float MAXCT_Skill = 20.f;
	float CT_Skill;
	bool bSkill = false;

	UPROPERTY(EditAnywhere)
	float MAXCT_Skill2 = 25.f;
	float CT_Skill2;
	bool bSkill2 = false;

	float MAXCT_Skill3 = 45.f;
	float CT_Skill3;
	bool Page2 = false;

	UPROPERTY(EditAnywhere)
		UAnimMontage* Attack;
	UPROPERTY(EditAnywhere)
		UAnimMontage* RangeAttack;
	UPROPERTY(EditAnywhere )
		UAnimMontage* Skill1;
	UPROPERTY(EditAnywhere)
		UAnimMontage* Skill2;
	UPROPERTY(EditAnywhere)
		UAnimMontage* Skill3;
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	class UCBehaviorComponent* Behavior;
	TSubclassOf<class ABossThrowStone> ThrowStone;
	TSubclassOf<class ABossFallingStone> FallingStone;
	TSubclassOf<class ABossFloor> BossFloor;
	UPROPERTY(Replicated)
	FVector TargetLocation;
	TSubclassOf<class UBossHealth> HealthWidgetClass;
public:
	class UBossHealth* BossHealth;
};
