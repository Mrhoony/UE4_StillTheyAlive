#include "CServerRow.h"
#include "Widgets/CUserWidget_MainMenu.h"
#include "Components/Button.h"

void UCServerRow::Setup(UCUserWidget_MainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;


	RowButton->OnClicked.AddDynamic(this, &UCServerRow::OnClicked);
}

void UCServerRow::OnClicked()
{
	Parent->SetSelectedIndex(Index);
}

