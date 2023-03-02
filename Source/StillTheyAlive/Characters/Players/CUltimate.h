#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CUltimate.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACUltimate : public AActor
{
	GENERATED_BODY()
	
public:	
	ACUltimate();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE void SetDirection(FVector InDirection) { Direction = InDirection; }

	void SetUltimateGauge(float InGauge);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

private:
	FVector Direction;
	float UltimateGauge = 3.3f;
};
