#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMenuInterface.h"
#include "CMapListItem.h"
#include "Core/Structs/FStoryMapData.h"
#include "CUserWidget_MainMenu.generated.h"

USTRUCT(BlueprintType)
struct FServerData
{
	GENERATED_BODY()

public:
	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUserName;
};

UCLASS()
class STILLTHEYALIVE_API UCUserWidget_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UCUserWidget_MainMenu(const FObjectInitializer& ObjectInitializer);

public:
	virtual bool Initialize() override;

public:
	FORCEINLINE void SetMenuInterface(IIMenuInterface* InMenuInterface) { MenuInterface = InMenuInterface; }

private:
	UFUNCTION() void OpenPlayMenu();
	UFUNCTION() void OpenMainMenu();
	UFUNCTION() void OpenMultiMenu();
	UFUNCTION() void OpenCreateMenu();
	UFUNCTION() void RefreshServer();
	UFUNCTION() void PlayGame();
	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void JoinServer();

	//UFUNCTION() void Character();
	//UFUNCTION() void Option();
	//UFUNCTION() void Quit();

public:
	void Setup();
	void Teardown();
	void SetSelectedIndex(uint32 Index);
	void SetMapList();
	void SetSelectedMap(FString InText);
	void SetServerList(TArray<FServerData> InServerNames);

private:
	void UpdateChildren();

protected:
	IIMenuInterface* MenuInterface;

private:
	UPROPERTY(meta = (BindWidget))		class UButton* PlayMenuButton;
	UPROPERTY(meta = (BindWidget))		class UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(meta = (BindWidget))		class UVerticalBox* MainMenu;
	UPROPERTY(meta = (BindWidget))		class UHorizontalBox* PlayMenu;
	UPROPERTY(meta = (BindWidget))		class UButton* PlayMenuBackButton;
	UPROPERTY(meta = (BindWidget))		class UPanelWidget* MapList;
	UPROPERTY(meta = (BindWidget))		class UButton* PlayGameButton;

	UPROPERTY(meta = (BindWidget))		class UVerticalBox* MultiMenu;
	UPROPERTY(meta = (BindWidget))		class UButton* MultiPlayButton;
	UPROPERTY(meta = (BindWidget))		class UButton* CreateSessionButton;
	UPROPERTY(meta = (BindWidget))		class UButton* RefreshButton;
	UPROPERTY(meta = (BindWidget))		class UButton* JoinSessionButton;
	UPROPERTY(meta = (BindWidget))		class UButton* CancelSessionButton;
	UPROPERTY(meta = (BindWidget))		class UPanelWidget* ServerList;

	UPROPERTY(meta = (BindWidget))		class UVerticalBox* CreateMenu;
	UPROPERTY(meta = (BindWidget))		class UButton* CreateSession;
	UPROPERTY(meta = (BindWidget))		class UButton* CancleSession;
	UPROPERTY(meta = (BindWidget))		class UEditableTextBox* ServerHostName;
	//UPROPERTY(meta = (BindWidget))		class UButton* CharacterButton;
	//UPROPERTY(meta = (BindWidget))		class UButton* OptionButton;
	//UPROPERTY(meta = (BindWidget))		class UButton* QuitButton;

private:
	UPROPERTY(EditDefaultsOnly)		class UDataTable* StoryMapList;

private:
	TOptional<uint32> SelectedIndex;
	TSubclassOf<UCMapListItem> MapListItemClass;
	FStoryMapData* SelectedStoryMap;
	TSubclassOf<class UUserWidget> ServerRowClass;
};
