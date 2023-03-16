#include "CUserWidget_MainMenu.h"
#include "Global.h"

#include "Core/CGameInstance.h"
#include "Widgets/CServerRow.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "GameFramework/PlayerController.h"

UCUserWidget_MainMenu::UCUserWidget_MainMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	CHelpers::GetClass(&MapListItemClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_MapListItem.WB_MapListItem_C'");
	CHelpers::GetClass(&ServerRowClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_ServerRow.WB_ServerRow_C'");
	CHelpers::GetAsset<UDataTable>(&StoryMapList, "DataTable'/Game/_Project/DataTables/DT_StoryMapList.DT_StoryMapList'");
}

bool UCUserWidget_MainMenu::Initialize()
{
	bool success = Super::Initialize();
	if(success == false) return false;

	CheckNullResult(PlayMenuButton, false);
	CheckNullResult(PlayMenuBackButton, false);
	CheckNullResult(PlayGameButton, false);
	CheckNullResult(CancelSessionButton, false);
	CheckNullResult(MultiPlayButton, false);
	CheckNullResult(CreateSessionButton, false);
	CheckNullResult(JoinSessionButton, false);
	CheckNullResult(RefreshButton, false);
	CheckNullResult(CreateSession, false);
	CheckNullResult(CancleSession, false);

	PlayMenuButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::OpenPlayMenu);
	PlayMenuBackButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::OpenMainMenu);
	CancelSessionButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::OpenMainMenu);
	PlayGameButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::PlayGame);
	MultiPlayButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::OpenMultiMenu);
	CreateSessionButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::OpenCreateMenu);
	JoinSessionButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::JoinServer);
	RefreshButton->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::RefreshServer);
	CreateSession->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::HostServer);
	CancleSession->OnClicked.AddDynamic(this, &UCUserWidget_MainMenu::OpenMultiMenu);

	//SetMapList();

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

void UCUserWidget_MainMenu::OpenMultiMenu()
{
	CheckNull(MenuSwitcher);

	if (MenuInterface != nullptr)
		MenuInterface->RefreshServerList();

	MenuSwitcher->SetActiveWidget(MultiMenu);
}

void UCUserWidget_MainMenu::OpenCreateMenu()
{
	CheckNull(MenuSwitcher);

	MenuSwitcher->SetActiveWidget(CreateMenu);
}

void UCUserWidget_MainMenu::RefreshServer()
{
	if (MenuInterface != nullptr)
		MenuInterface->RefreshServerList();

	MenuSwitcher->SetActiveWidget(MultiMenu);
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

void UCUserWidget_MainMenu::HostServer()
{
	if (!!MenuInterface)
	{
		FString serverName = ServerHostName->Text.ToString();
		MenuInterface->Host(serverName);
	}
}

void UCUserWidget_MainMenu::JoinServer()
{
	if (SelectedIndex.IsSet() && !!MenuInterface)
	{
		UE_LOG(LogTemp, Display, TEXT("%d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("not set"));
	}
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

void UCUserWidget_MainMenu::SetServerList(TArray<FServerData> InServerNames)
{
	if (ServerList == nullptr) return;
	ServerList->ClearChildren();
	uint32 i = 0;
	for (const FServerData& serverData : InServerNames)
	{
		UCServerRow* row = CreateWidget<UCServerRow>(this, ServerRowClass);
		if (row == nullptr) return;

		row->ServerName->SetText(FText::FromString(serverData.Name));
		row->HostUser->SetText(FText::FromString(serverData.HostUserName));
		FString fractionText = FString::Printf(TEXT("%d/%d"), serverData.CurrentPlayers, serverData.MaxPlayers);
		row->Connection->SetText(FText::FromString(fractionText));
		row->Setup(this, i++);

		ServerList->AddChild(row);
	}
}

void UCUserWidget_MainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); i++)
	{
		UCServerRow* serverRow = Cast<UCServerRow>(ServerList->GetChildAt(i));
		if (!!serverRow)
		{
			serverRow->bSelected = (SelectedIndex.IsSet()) && (SelectedIndex.GetValue()) == i;
		}
	}
}
