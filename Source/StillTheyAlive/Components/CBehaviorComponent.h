#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Patrol, Approch, Action, Hitted
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, ChangeType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STILLTHEYALIVE_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION(BlueprintPure) bool IsApprochMode();
	UFUNCTION(BlueprintPure) bool IsActionMode();
	UFUNCTION(BlueprintPure) bool IsPatrolMode();
	UFUNCTION(BlueprintPure) bool IsHittedMode();
		
public:
	FORCEINLINE void SetBlackBoard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

	class ACPlayer* GetTargetPlayer();

	void SetApprochMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();

private:
	void ChangeType(EBehaviorType InType);
	EBehaviorType GetType();

public:
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChanged OnBehaviorTypeChanged;

private:
	UPROPERTY(EditAnywhere) FName BehaviorKey = "Behavior";
	UPROPERTY(EditAnywhere) FName PlayerKey = "Player";

private:
	class UBlackboardComponent* Blackboard;
};
