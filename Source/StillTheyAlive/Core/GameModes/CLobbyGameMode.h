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
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	void IncreaseReady();
	void DecreaseReady();
private:
	void StartGame();

private:
	int PlayerNum = 0;
	int ReadyPlayer = 0;
	FTimerHandle GameStartTimer;
};
