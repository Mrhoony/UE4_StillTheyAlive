#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "CAIController.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACAIController();

public:
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	void SetLoactionKey(FVector InLoaction);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorComponent* Behavior;

	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(EditAnywhere)
		float BehaviorRange = 150.f;

private:
	class ACEnemy* OwnerEnemy;
	class UAISenseConfig_Sight* Sight;
};
