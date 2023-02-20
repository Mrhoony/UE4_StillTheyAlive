#pragma once

#include "CoreMinimal.h"
#include "Perk/CDoAction.h"
#include "CDoAction_Spawn.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACDoAction_Spawn : public ACDoAction
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void DoAction_L() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
};
