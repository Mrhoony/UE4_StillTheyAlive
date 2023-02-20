#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Patrol, Approach, Action, Hitted , Return
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, ChangeType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STILLTHEYALIVE_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION(BlueprintPure) bool IsWaitMode();
	UFUNCTION(BlueprintPure) bool IsApproachMode();
	UFUNCTION(BlueprintPure) bool IsActionMode();
	UFUNCTION(BlueprintPure) bool IsPatrolMode();
	UFUNCTION(BlueprintPure) bool IsHittedMode();
	UFUNCTION(BlueprintPure) bool IsReturnMode();
		
public:
	FORCEINLINE void SetBlackBoard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

	class ACharacter* GetTarget();
	FVector GetLocation();

	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode(); 
	void SetReturnMode(); 

private:
	void ChangeType(EBehaviorType InType);
	EBehaviorType GetType();

public:
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChanged OnBehaviorTypeChanged;

private:
	UPROPERTY(EditAnywhere) FName BehaviorKey = "Behavior";
	UPROPERTY(EditAnywhere) FName TargetKey = "Target";
	UPROPERTY(EditAnywhere) FName LocationKey = "Location";

private:
	class UBlackboardComponent* Blackboard;
};
