#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CThrow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FThrowBeginOverlap, FHitResult, InHitResult);

UCLASS()
class STILLTHEYALIVE_API ACThrow : public AActor
{
	GENERATED_BODY()
	
public:	
	ACThrow();

	FORCEINLINE bool IsRadial() { return bRadial; }
	FORCEINLINE void SetRadial() { bRadial = true; }
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly)
		FTransform ImpactParticleTransform;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* ThrowParticle;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

public:
	UPROPERTY(BlueprintAssignable)
		FThrowBeginOverlap OnThrowBeginOverlap;

private:
	bool bRadial = false;

};
