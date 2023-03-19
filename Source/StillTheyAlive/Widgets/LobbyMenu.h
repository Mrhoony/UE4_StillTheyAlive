#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMenu.generated.h"

UCLASS()
class STILLTHEYALIVE_API ULobbyMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	ULobbyMenu(const FObjectInitializer& ObjectInitializer);
	virtual bool Initialize() override;

	void SetLobbyList(FString Name);

	void Setup();

	UFUNCTION()
		void TextReady();

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* UserState;

	UPROPERTY(meta = (BindWidget))
		class UButton* ReadyButton;

	TSubclassOf<class UUserWidget> LobbyRowClass;
};
