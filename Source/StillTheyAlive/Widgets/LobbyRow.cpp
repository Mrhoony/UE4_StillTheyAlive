#include "LobbyRow.h"
#include "Components/TextBlock.h"
#include "Styling/SlateColor.h"

void ULobbyRow::ReadyColor(bool CheckReady)
{
	CheckReady ? PlayerReady->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0.f, 0.f))) : PlayerReady->SetColorAndOpacity(FSlateColor(FLinearColor(0.f, 1.f, 0.f)));
}