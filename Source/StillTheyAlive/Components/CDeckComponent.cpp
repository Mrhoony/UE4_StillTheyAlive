#include "CDeckComponent.h"
#include "Global.h"
#include "Perk/CPerk.h"
#include "Perk/CDoAction.h"
#include "Perk/CAttachment.h"
#include "Perk/CEquipment.h"

UCDeckComponent::UCDeckComponent()
<<<<<<< HEAD
{
=======
{	

>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b
}

void UCDeckComponent::BeginPlay()
{
	Super::BeginPlay();
	FTransform transform;
	if (!!PerkClass)
	{
		Perks.Add(GetOwner()->GetWorld()->SpawnActorDeferred<ACPerk>(PerkClass, transform, GetOwner()));
	
		UGameplayStatics::FinishSpawningActor(Perks[0], transform);
	}
<<<<<<< HEAD
}

=======

}



>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b
void UCDeckComponent::PerkAction()
{
	ACDoAction* doAction = Perks[DeckNumber]->GetCurrent()->GetDoAction();

<<<<<<< HEAD
	//TODO: Perk 동작에 대한 코드 없음
=======

>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b
}

void UCDeckComponent::SetCurrentPerk(int index)
{
	ChangePerk(Perks[DeckNumber], Perks[index]);
	DeckNumber = index;
}

void UCDeckComponent::Begin_Perk(ACPerk* InNewPerk)
{
	if (InNewPerk->GetCurrent()->GetAttachment())
	{
		InNewPerk->GetCurrent()->GetAttachment()->OnEquip();
		if (InNewPerk->GetCurrent()->GetEquipment())
			InNewPerk->GetCurrent()->GetEquipment()->Equip();
	}
}

void UCDeckComponent::End_Perk(ACPerk* InPrevPerk)
{
	if(InPrevPerk->GetCurrent()->GetAttachment())
	InPrevPerk->GetCurrent()->GetAttachment()->OnUnequip();
	//히든 상태 만들기
}

void UCDeckComponent::ChangePerk(ACPerk* InPrevPerk, ACPerk* InNewPerk)
{
	End_Perk(InPrevPerk);
	Begin_Perk(InNewPerk);
}
<<<<<<< HEAD
=======

>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b
