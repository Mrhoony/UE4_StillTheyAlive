#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CPlayerState.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetReady() { bReady ? bReady = false : bReady = true; }

	void SetPlayerNum(int InNum) { PlayerNum = InNum; }

public:
	int PlayerNum;
	bool bReady = false;
};
