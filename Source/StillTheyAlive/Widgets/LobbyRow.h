#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyRow.generated.h"

UCLASS()
class STILLTHEYALIVE_API ULobbyRow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ReadyColor(bool CheckReady);

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PlayerName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PlayerReady;
};
