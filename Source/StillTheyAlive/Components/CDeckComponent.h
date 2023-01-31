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

protected:
	virtual void BeginPlay() override;

public:

	//void AddPerkInfo(FPerkInfo InPerkInfo);

private:
	//class FPerkInfo* PerkInfo[9];
};
