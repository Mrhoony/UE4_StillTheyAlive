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
	void PerkAction();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Perk")
		TSubclassOf<class ACPerk> PerkClass;

protected:

private:
	TArray<class ACPerk*> Perk;
	//class FPerkInfo* PerkInfo[9];
};
