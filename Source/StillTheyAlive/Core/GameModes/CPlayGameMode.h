#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPlayGameMode.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACPlayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartNextRound() {};
};
