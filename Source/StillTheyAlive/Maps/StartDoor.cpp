#include "StartDoor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

AStartDoor::AStartDoor()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;
	CHelpers::CreateSceneComponent<UStaticMeshComponent>(this, &Mesh, "Door",Scene);
	Mesh->SetRelativeRotation(FRotator(0, 90, 0));
	Mesh->SetRelativeScale3D(FVector(1.15, 1, 1.75));
}

void AStartDoor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AStartDoor::OpenDoor()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	Mesh->AddImpulse(GetActorForwardVector() * 500000.f);
	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "DestroyActor");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer,  3.f, false);
}

void AStartDoor::DestroyActor()
{
	PrintLine();
	Destroy();
}

