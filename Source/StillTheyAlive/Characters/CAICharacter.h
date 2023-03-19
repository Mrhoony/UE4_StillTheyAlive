#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "AIController.h"
#include "CAICharacter.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACAICharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

public:
	UFUNCTION()
		virtual void OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType) {} ;

public:
	// Actor Components
	UPROPERTY(VisibleDefaultsOnly) class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly) class UCDeckComponent* Deck;
	UPROPERTY(VisibleDefaultsOnly) class UCStateComponent* State;
	// Scene Components
	UPROPERTY(VisibleDefaultsOnly) class UWidgetComponent* NameWidget;
	UPROPERTY(VisibleDefaultsOnly) class UWidgetComponent* HealthWidget;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
	float ActionMaxCoolTime = 2.f;
	float ActionCoolTime = 0;

	class UCUserWidget_Health* HealthBar;
	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;
};
