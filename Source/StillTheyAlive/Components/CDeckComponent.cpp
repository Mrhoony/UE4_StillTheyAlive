#include "CDeckComponent.h"
#include "Global.h"

#include "Perk/ActionData/CDoAction.h"
#include "Perk/ActionData/CEquipment.h"
#include "Perk/Weapons/CWeapon.h"
#include "Characters/Players/CAnimInstance.h"
#include "Components/CStateComponent.h"
#include "Widgets/CUserWidget_Deck.h"
#include "Widgets/CHUD.h"

#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "Net/UnrealNetwork.h"

UCDeckComponent::UCDeckComponent()
{
	CHelpers::GetClass(&WidgetClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_Deck.WB_Deck_C'");
}

void UCDeckComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCDeckComponent, DeckNumber);
	DOREPLIFETIME(UCDeckComponent, CurrentPerk);
	DOREPLIFETIME(UCDeckComponent, BeforePerk);
	DOREPLIFETIME(UCDeckComponent, Type);
	DOREPLIFETIME(UCDeckComponent, OwnerCharacter);
}

void UCDeckComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerState = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	FTransform transform;
	for (int32 i = 0; i < PerkClass.Num(); i++)
	{
		if (!!PerkClass[i])
		{
			ACPerk* perk = GetOwner()->GetWorld()->SpawnActorDeferred<ACPerk>(PerkClass[i], transform, GetOwner());
			perk->BeginData(OwnerCharacter);
			UGameplayStatics::FinishSpawningActor(perk, transform);
			UKismetSystemLibrary::Delay(GetWorld(), 0.1f, FLatentActionInfo());
			Perks.Add(perk);
		}
	}

	//MakeWidget();
}
void UCDeckComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UCDeckComponent::PerkAction_Implementation()
{
	CheckFalse(CurrentPerk);
	CheckTrue(IsPerkUnarmed());
	if (!!CurrentPerk->GetCurrent()->GetDoAction())
	{
		ACDoAction* doAction = CurrentPerk->GetCurrent()->GetDoAction();
		
		doAction->DoAction_L();
	}
}

void UCDeckComponent::ServerPerkAction_Implementation()
{
	PerkAction();
}

void UCDeckComponent::PerkEndAction_Implementation()
{
	CheckNull(CurrentPerk);
	
	if (!!Perks[DeckNumber]->GetCurrent()->GetDoAction())
	{
		ACDoAction* doAction = Perks[DeckNumber]->GetCurrent()->GetDoAction();

		doAction->End_DoAction_L();
	}
}

void UCDeckComponent::ServerPerkEndAction_Implementation()
{
	PerkEndAction();
}

void UCDeckComponent::PerkTechAction_Implementation()
{
	CheckNull(CurrentPerk);
	if (Perks[DeckNumber]->GetCurrent()->GetDoAction())
	{
		ACDoAction* doAction = Perks[DeckNumber]->GetCurrent()->GetDoAction();

		doAction->DoAction_R();
	}
}

void UCDeckComponent::ServerPerkTechAction_Implementation()
{
	PerkTechAction();
}

void UCDeckComponent::PerkTechOffAction_Implementation()
{
	CheckNull(CurrentPerk);
	if (Perks[DeckNumber]->GetCurrent()->GetDoAction())
	{
		ACDoAction* doAction = Perks[DeckNumber]->GetCurrent()->GetDoAction();

		doAction->DoOffAction_R();
	}
}

void UCDeckComponent::ServerPerkTechOffAction_Implementation()
{
	PerkTechOffAction();
}

void UCDeckComponent::PerkUltimate_Implementation()
{
	CheckNull(CurrentPerk);
	if (Perks[DeckNumber]->GetCurrent()->GetDoAction())
	{
		ACDoAction* doAction = Perks[DeckNumber]->GetCurrent()->GetDoAction();

		doAction->UltimateAction();
	}
}

void UCDeckComponent::ServerPerkUltimate_Implementation()
{
	PerkUltimate();
}

void UCDeckComponent::SetCurrentPerk_Implementation(int index)
{
	MultiSetCurrentPerk(index);
}

void UCDeckComponent::MultiSetCurrentPerk_Implementation(int index)
{
	if (Perks.Num() <= index) return;
	if (DeckNumber == index && !!CurrentPerk)
	{
		SetUnarmed();
		return;
	}
	else
	{
		DeckNumber = index;

		BeforePerk = CurrentPerk;

		CurrentPerk = Perks[DeckNumber];
	}
	ChangePerk(BeforePerk, CurrentPerk);
}

void UCDeckComponent::ChangePerk(ACPerk* InPrevPerk, ACPerk* InNewPerk)
{
	if(!!InPrevPerk)
	InPrevPerk->GetCurrent()->GetEquipment()->Unequip();
	CheckNull(InNewPerk);
	InNewPerk->GetCurrent()->GetEquipment()->Equip();
	switch (InNewPerk->GetPerkType())
	{
	case EPerkType::Weapon:SetWeapon();
		break;
	case EPerkType::Trap:SetTrap();
		break;
	case EPerkType::Spawn:SetSpawn();
		break;
	case EPerkType::Trinket:SetTrinket();
		break;
	}
}

void UCDeckComponent::SetUnarmed()
{
	CheckFalse(CurrentPerk);
	if(CurrentPerk->GetCurrent()->GetEquipment())
		CurrentPerk->GetCurrent()->GetEquipment()->Unequip();
	CurrentPerk = nullptr;
	ChangeType(EPerkType::Unarmed);
}

void UCDeckComponent::SetWeapon()
{
	ChangeType(EPerkType::Weapon);
}

void UCDeckComponent::SetTrap()
{
	ChangeType(EPerkType::Trap);
}

void UCDeckComponent::SetSpawn()
{
	ChangeType(EPerkType::Spawn);
}

void UCDeckComponent::SetTrinket()
{
	ChangeType(EPerkType::Trinket);
}

void UCDeckComponent::ChangeType(EPerkType InType)
{
	EPerkType prevType = Type;
	Type = InType;

	if (OnPerkTypeChanged.IsBound())
		OnPerkTypeChanged.Broadcast(prevType, InType);


	if (Type == EPerkType::Weapon)
	{
		UCAnimInstance* oweneranim = Cast<UCAnimInstance>(OwnerCharacter->GetMesh()->GetAnimInstance());
		oweneranim->OnWeaponTypeChanged(Cast<ACWeapon>(CurrentPerk)->GetWeaponType());
	}
}

void UCDeckComponent::Dead()
{
	for (int32 i = 0; i < Perks.Num(); i++)
	{
		Perks[i]->Dead();
	}
}

void UCDeckComponent::EndDead()
{
	for (int32 i = 0; i < Perks.Num(); i++)
	{
		Perks[i]->End_Dead();
	}
}

void UCDeckComponent::CreateDeckWidget(UCHUD* HUD)
{
	CheckNull(WidgetClass);
	CheckNull(HUD);

	APlayerController* playerController = Cast<APlayerController>(OwnerCharacter->GetController());
	CheckNull(playerController);

	Widget = CreateWidget<UCUserWidget_Deck, APlayerController>(playerController, WidgetClass);
	Widget->SetOwnerComponent(this);
	
	HUD->Slot_Deck->AddChild(Widget);
}
