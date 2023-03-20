#include "CLobbyGameMode.h"
#include "Global.h"
#include "core/CGameInstance.h"
#include "core/CPlayerState.h"
#include "Characters/Players/CPlayer.h"

ACLobbyGameMode::ACLobbyGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/BP_CPlayer.BP_CPlayer_C'");
}

void ACLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ACPlayer* player = Cast<ACPlayer>(NewPlayer->GetPawn());
	ACPlayerState* playerState = Cast<ACPlayerState>(NewPlayer->PlayerState);
	PlayerNum++;
	if (playerState != nullptr && player != nullptr)
	{
		player->SetPlayerState(playerState);
		ACPlayerState* State = Cast<ACPlayerState>(player->GetPlayerState());
		State->SetPlayerNum(PlayerNum);
	}
	if (PlayerNum >= 3)
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ACLobbyGameMode::StartGame, 10);
}

void ACLobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
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

	world->ServerTravel("/Game/_Project/Maps/TwoWays?listen");
}