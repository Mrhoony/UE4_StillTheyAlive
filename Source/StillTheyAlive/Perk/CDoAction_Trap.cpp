#include "CDoAction_Trap.h"
#include "Global.h"
#include "Trap/CTrap.h"
#include "Object/CGridTrigger.h"
#include "Components/DecalComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"


void ACDoAction_Trap::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Trap"))
		{
		
			Decal = CHelpers::GetComponent<UDecalComponent>(actor);
			StaticMesh = CHelpers::GetComponent<UStaticMeshComponent>(actor);

			break;
		}
	}
}

void ACDoAction_Trap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Decal == nullptr || StaticMesh == nullptr) return;
	if (GetCursorLocationAndRotation(DecalLocation, DecalRotation))
	{
		Decal->SetVisibility(true);
		Decal->SetWorldLocation(DecalLocation);
		Decal->SetWorldRotation(DecalRotation);

		StaticMesh->SetVisibility(true);
		StaticMesh->SetWorldLocation(DecalLocation);
	}
	else
	{
		Decal->SetVisibility(false);
		StaticMesh->SetVisibility(false);
	}
}

void ACDoAction_Trap::DoAction_L()
{
	if (GetCursorLocationAndRotation(DecalLocation, DecalRotation))
	{
		//GetWorld()->SpawnActor
	}
}

void ACDoAction_Trap::Begin_DoAction()
{

}

void ACDoAction_Trap::End_DoAction()
{

}

bool ACDoAction_Trap::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery7);

	FHitResult hitResult;
	if (PlayerController->GetHitResultUnderCursorForObjects(objects, true, hitResult))
	{
		OutLocation = hitResult.Location;
		OutRotation = Cast<ACGridTrigger>(hitResult.GetActor())->GetActorRotation();

		return true;
	}

	return false;
}
