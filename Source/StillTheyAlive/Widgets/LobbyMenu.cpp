#include "LobbyMenu.h"
#include "Global.h"
#include "Components/Button.h"
#include "Widgets/LobbyRow.h"
#include "Components/TextBlock.h"

ULobbyMenu::ULobbyMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	CHelpers::GetClass<UUserWidget>(&LobbyRowClass, "WidgetBlueprint'/Game/_Project/Widgets/WB_LobbyRow.WB_LobbyRow_C'");
}

bool ULobbyMenu::Initialize()
{
	bool success = Super::Initialize();
	if (success == false) return false;
	CheckNullResult(ReadyButton, false);

	ReadyButton->OnClicked.AddDynamic(this, &ULobbyMenu::TextReady);
	return true;
}

void ULobbyMenu::SetLobbyList(FString Name)
{
	ULobbyRow* row = CreateWidget<ULobbyRow>(this, LobbyRowClass);
	if (row == nullptr) return;

	row->PlayerName->SetText(FText::FromString(Name));
	UserState->AddChild(row);
}

void ULobbyMenu::Setup()
{
	AddToViewport();
	//bIsFocusable = true;

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* world = GetWorld();
	if (world == nullptr) return;

	APlayerController* controller = world->GetFirstPlayerController();
	if (controller == nullptr) return;
	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = true;
}

void ULobbyMenu::TextReady()
{

}
