#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "AIController.h"
#include "CAIControllerSpawn.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACAIControllerSpawn : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIControllerSpawn();

public:
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

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
	class ACSpawnCharacter* OwnerCharacter;
	class UAISenseConfig_Sight* Sight;
};
