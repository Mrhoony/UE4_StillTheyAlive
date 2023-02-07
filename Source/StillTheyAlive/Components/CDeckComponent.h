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
	void GetCurrentPerkData();

public:
	void PerkAction();
	void SetCurrentPerk(int index);
	void Begin_Perk(class ACPerk* InNewPerk);
	void End_Perk(class ACPerk* InPrevPerk);

	void ChangePerk(class ACPerk* InPrevPerk,class  ACPerk* InNewPerk);
//=======================================================
// [Variables]
//=======================================================
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Perk")	TSubclassOf<class ACPerk> PerkClass;

private:
	uint32 DeckNumber;
	TArray<class ACPerk*> Perks;
	class ACPerk* CurrentPerk;

};
