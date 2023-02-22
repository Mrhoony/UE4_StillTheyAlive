#include "CEquipment.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ACEquipment::ACEquipment()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
}

void ACEquipment::Equip_Implementation()
{
	State->SetEquip();

	if (!!Data.Montage.AnimMontage)
		OwnerCharacter->PlayAnimMontage(Data.Montage.AnimMontage, Data.Montage.PlayRate, Data.Montage.StartSection);
	else
	{
		Begin_Equip();
		End_Equip();
	}

	if (Data.bPawnControl == true)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void ACEquipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void ACEquipment::End_Equip_Implementation()
{
	State->SetIdle();
}

void ACEquipment::Unequip_Implementation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();
}
