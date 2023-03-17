#include "CLobbyGameMode.h"
#include "Global.h"
#include "core/CGameInstance.h"

ACLobbyGameMode::ACLobbyGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/BP_CPlayer.BP_CPlayer_C'");
}

void ACLobbyGameMode::IncreaseReady()
{
	ReadyPlayer++;
	if (ReadyPlayer == 2)
		StartGame();
}

void ACLobbyGameMode::DecreaseReady()
{
	ReadyPlayer--;
}

void ACLobbyGameMode::StartGame()
{
	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetGameInstance());
	if (gameInstance == nullptr) return;
	gameInstance->StartSession();


	UWorld* world = GetWorld();
	if (world == nullptr) return;

	bUseSeamlessTravel = true;
	world->ServerTravel("/Game/Maps/TwoWays?listen");
}