#include "CDoAction_Trap.h"
#include "Global.h"
#include "Trap/CTrap.h"
#include "Grid/CGridTrigger.h"
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
			StaticMesh = CHelpers::GetComponent<UStaticMeshComponent>(actor);
			break;
		}
	}
}

void ACDoAction_Trap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StaticMesh == nullptr) return;
	if (GetCursorLocationAndRotation(DecalLocation, DecalRotation))
	{
		StaticMesh->SetVisibility(true);
		StaticMesh->SetWorldLocation(DecalLocation);
		StaticMesh->SetWorldRotation(DecalRotation);
	}
	else
	{
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
		ACGridTrigger* gridTrigger = Cast<ACGridTrigger>(hitResult.GetActor());
		float snapX = UKismetMathLibrary::GridSnap_Float(hitResult.Location.X, gridTrigger->GetGridSize() * 2);
		float snapY = UKismetMathLibrary::GridSnap_Float(hitResult.Location.Y, gridTrigger->GetGridSize() * 2);
		
		
		OutLocation = FVector(snapX, snapY, 0);
		OutRotation = gridTrigger->GetActorRotation();
		
		return true;
	}

	return false;
}
