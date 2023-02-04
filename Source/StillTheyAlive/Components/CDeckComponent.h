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
	void PerkAction();
	void SetCurrentPerk(int index);

//=======================================================
// [Variables]
//=======================================================
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Perk")	TSubclassOf<class ACPerk> PerkClass;

private:
	TArray<class ACPerk*> Perks;
	class ACPerk* CurrentPerk;
	//class FPerkInfo* PerkInfo[9];
};
