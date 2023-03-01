#include "CUserWidget_Deck.h"
#include "Global.h"

#include "Components/CDeckComponent.h"
#include "Perk/CPerk.h"

#include "Components/HorizontalBox.h"
#include "Components/Image.h"

void UCUserWidget_Deck::NativeConstruct()
{
	Super::NativeConstruct();
	TArray<UWidget*> slots;
	slots = Container->GetAllChildren();

	for (UWidget* slot : slots)
	{
		Slots.Add(Cast<UImage>(slot));
	}

	//CLog::Print("Construct Slots : " + FString::FromInt(Slots.Num()));

	SetIcons();
}

void UCUserWidget_Deck::SetIcons()
{
	CheckNull(OwnerComponent);

	TArray<ACPerk*> perks = OwnerComponent->GetPerks();

	//CLog::Print("perks : " + FString::FromInt(perks.Num()));
	//CLog::Print("Slots : " + FString::FromInt(Slots.Num()));

	Slots[0]->SetBrushFromTexture(perks[0]->Icon);

	for (int32 i = 0; i < perks.Num(); i++)
	{
		if (perks[i]->Icon == nullptr) continue;

		Slots[i]->SetBrushFromTexture(perks[i]->Icon);
	}
}