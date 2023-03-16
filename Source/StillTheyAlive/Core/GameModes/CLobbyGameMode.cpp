#include "CLobbyGameMode.h"
#include "core/CGameInstance.h"

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