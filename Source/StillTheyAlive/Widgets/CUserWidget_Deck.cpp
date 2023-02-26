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
}

void UCUserWidget_Deck::SetIcons()
{
	CheckNull(OwnerComponent);

	TArray<ACPerk*> perks = OwnerComponent->GetPerks();
	
	for (int32 i = 0; i < perks.Num(); i++)
	{
		Slots[i]->SetBrushFromTexture(perks[i]->Icon);
	}
}