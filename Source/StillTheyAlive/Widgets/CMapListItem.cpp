#include "CMapListItem.h"

#include "CUserWidget_MainMenu.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCMapListItem::Setup(class UCUserWidget_MainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;

	ItemButton->OnClicked.AddDynamic(this, &UCMapListItem::OnClicked);
}

void UCMapListItem::OnClicked()
{
	Parent->SetSelectedIndex(Index);

	Parent->SetSelectedMap(MapName->Text.ToString());
}
