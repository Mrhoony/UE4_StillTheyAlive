#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossThrowStone.generated.h"

UCLASS()
class STILLTHEYALIVE_API ABossThrowStone : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossThrowStone();

protected:
	virtual void BeginPlay() override;

public:
	void Throw(FVector Location);
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnThrow();
private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

	class ACharacter* OwnerCharacter;
	FVector TargetLocation;
};
