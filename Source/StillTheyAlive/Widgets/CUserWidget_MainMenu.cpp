#include "CUserWidget_MainMenu.h"
#include "Global.h"

#include "Core/CGameInstance.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"

UCUserWidget_MainMenu::UCUserWidget_MainMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	CHelpers::GetClass(&MapListItemClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_MapListItem.WB_MapListItem_C'");
	CHelpers::GetAsset<UDataTable>(&StoryMapList, "DataTable'/Game/_Project/DataTables/DT_StoryMapList.DT_StoryMapList'");
}

bool UCUserWidget_MainMenu::Initialize()
{
	bool success = Super::Initialize();
	if(success == false) return false;

	CheckNullResult(PlayMenuButton, false);
	CheckNullResult(PlayMenuBackButton, false);
	CheckNullResult(PlayGameButton, false);

	PlayMenuButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::OpenPlayMenu);
	PlayMenuBackButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::OpenMainMenu);
	PlayGameButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::PlayGame);

	SetMapList();

	return true;
}

void UCUserWidget_MainMenu::OpenPlayMenu()
{
	CheckNull(MenuSwitcher);

	MenuSwitcher->SetActiveWidget(PlayMenu);
}

void UCUserWidget_MainMenu::OpenMainMenu()
{
	CheckNull(MenuSwitcher);

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UCUserWidget_MainMenu::PlayGame()
{	
	APlayerController* controller = GetWorld()->GetGameInstance()->GetFirstLocalPlayerController();
	//APlayerController* controller = MenuInterface->GetFirstLocalPlayerController();
	CheckNull(controller);

	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());
	CheckNull(gameInstance);
	gameInstance->SetCurrentStoryMap(SelectedStoryMap);

	FInputModeGameOnly inputmode;
	controller->SetInputMode(inputmode);
	controller->ClientTravel(SelectedStoryMap->Map, ETravelType::TRAVEL_Absolute);	
}

//void UCUserWidget_MainMenu::Character()
//{
//	CLog::Print("Character");
//}
//void UCUserWidget_MainMenu::Option()
//{
//	CLog::Print("Option");
//}
//void UCUserWidget_MainMenu::Quit()
//{
//	CLog::Print("Quit");
//}

void UCUserWidget_MainMenu::Setup()
{
	AddToViewport();
	bIsFocusable = true;

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* world = GetWorld();
	CheckNull(world);

	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);
	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = true;
}

void UCUserWidget_MainMenu::Teardown()
{
	RemoveFromParent();
	bIsFocusable = false;

	FInputModeGameOnly inputMode;

	UWorld* world = GetWorld();
	CheckNull(world);

	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);
	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = false;
}

void UCUserWidget_MainMenu::SetSelectedIndex(uint32 Index)
{
	SelectedIndex = Index;
}

void UCUserWidget_MainMenu::SetMapList()
{
	MapList->ClearChildren();

	TArray<FStoryMapData*> datas;
	StoryMapList->GetAllRows<FStoryMapData>("GetAllRows", datas);

	for (FStoryMapData* data : datas)
	{
		UCMapListItem* item = CreateWidget<UCMapListItem>(this, MapListItemClass);
		CheckNull(item);

		item->MapName->SetText(FText::FromString(data->Map));
		item->Setup(this, MapList->GetAllChildren().Num());
		
		MapList->AddChild(item);
	}
}

void UCUserWidget_MainMenu::SetSelectedMap(FString InText)
{
	SelectedStoryMap = StoryMapList->FindRow<FStoryMapData>(*InText, InText);
}
