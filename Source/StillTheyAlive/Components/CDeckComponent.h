#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDeckComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STILLTHEYALIVE_API UCDeckComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCDeckComponent();

	//void AddPerkInfo(FPerkInfo InPerkInfo);

protected:
	virtual void BeginPlay() override;
	
// -------------------------------------------------------
// Variables
// -------------------------------------------------------
public:
	
protected:

private:
	//class FPerkInfo* PerkInfo[9];
};
