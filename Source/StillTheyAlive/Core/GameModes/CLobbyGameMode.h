#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CLobbyGameMode.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACLobbyGameMode();

	void IncreaseReady();
	void DecreaseReady();
private:
	void StartGame();

private:
	int ReadyPlayer = 0;
};
