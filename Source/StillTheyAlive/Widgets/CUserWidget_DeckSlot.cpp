#include "CUserWidget_DeckSlot.h"
#include "Global.h"

#include "Components/Image.h"

void UCUserWidget_DeckSlot::SetIcon(UTexture2D* IconImage)
{
	CheckNull(IconImage);

	Icon->SetColorAndOpacity(FLinearColor::White);
	Icon->SetBrushFromTexture(IconImage);
}

void UCUserWidget_DeckSlot::SetSelected()
{
	Border->SetColorAndOpacity(FLinearColor::Red);
}

void UCUserWidget_DeckSlot::SetCleared()
{
	Border->SetColorAndOpacity(FLinearColor::White);
}
