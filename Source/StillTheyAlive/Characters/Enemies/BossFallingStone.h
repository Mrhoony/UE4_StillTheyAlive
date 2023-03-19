#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossFallingStone.generated.h"

UCLASS()
class STILLTHEYALIVE_API ABossFallingStone : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossFallingStone();

protected:
	virtual void BeginPlay() override;

public:
	void OnStone();
	UFUNCTION()
	void OnFalling();
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstanceConstant* DecalMaterial;

	class ACharacter* OwnerCharacter;
};
