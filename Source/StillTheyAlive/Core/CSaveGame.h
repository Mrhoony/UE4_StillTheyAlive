#pragma once

#include "Perk/CPerk.h"
#include "Structs/FPlayerCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CSaveGame.generated.h"

UCLASS()
class STILLTHEYALIVE_API UCSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	TArray<FPlayerCharacter> PlayerCharacters;
};
