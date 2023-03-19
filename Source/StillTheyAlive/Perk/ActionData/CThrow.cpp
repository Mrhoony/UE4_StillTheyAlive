#include "CThrow.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ACThrow::ACThrow()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere");
	CHelpers::CreateSceneComponent(this, &ThrowParticle, "ThrowParticle", Sphere);
	CHelpers::CreateSceneComponent(this, &RadialForce, "RadialForce", Sphere);
	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	Projectile->InitialSpeed = 4000.f;
	Projectile->MaxSpeed = 8000.f;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bSweepCollision = false;

	RadialForce->Radius = 300.0f;
	RadialForce->Falloff = ERadialImpulseFalloff::RIF_Constant;
	RadialForce->RemoveObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery3);
	RadialForce->RemoveObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery4);
	RadialForce->RemoveObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery5);
	RadialForce->RemoveObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery6);
	RadialForce->AddObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery8);
	RadialForce->ImpulseStrength = 500.0f;
	RadialForce->bImpulseVelChange = true;

	InitialLifeSpan = 5.f;
}

void ACThrow::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACThrow::OnComponentBeginOverlap);
}

void ACThrow::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == GetOwner() || OtherActor == this);
	if (!!ImpactParticle)
	{
		FTransform transform = ImpactParticleTransform;
		transform.AddToTranslation(bFromSweep ? SweepResult.Location : GetActorLocation());
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, transform);
	}

	if (OnThrowBeginOverlap.IsBound())
		OnThrowBeginOverlap.Broadcast(SweepResult);
}

void ACThrow::Impulse()
{
	RadialForce->FireImpulse();
}
