#pragma once

#include "CoreMinimal.h"
#include "Perk/CPerk.h"
#include "CTrap.generated.h"

UENUM(BlueprintType)
enum class ETrapType : uint8
{
	Floor,
	Wall,
	Ceiling,
	Max
};

UCLASS()
class STILLTHEYALIVE_API ACTrap : public ACPerk
{
	GENERATED_BODY()

//=======================================================
// [Variables]
//=======================================================
};
