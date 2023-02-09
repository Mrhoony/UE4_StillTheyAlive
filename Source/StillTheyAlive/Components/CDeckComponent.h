#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perk/CPerk.h"
#include "CDeckComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPerkTypeChanged, EPerkType, InPrevType, EPerkType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STILLTHEYALIVE_API UCDeckComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCDeckComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EPerkType::Unarmed; }

	void GetCurrentPerkData();

private:
	void SetMode(EPerkType InType);
	void ChangeType(EPerkType InType);


public:
	void SetUnarmed();
	void SetWeapon();
	void SetTrap();
	void SetSpawn();
	void SetTrinket();

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsPerkUnarmed() { return Type == EPerkType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsPerkWeapon() { return Type == EPerkType::Weapon; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsPerkTrap() { return Type == EPerkType::Trap; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsPerkSpawn() { return Type == EPerkType::Spawn; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsPerkTrinket() { return Type == EPerkType::Trinket; }


public:
	void PerkAction();
	void PerkTechAction();
	void SetCurrentPerk(int index);
	void Begin_Perk(ACPerk* InNewPerk);
	void End_Perk(ACPerk* InPrevPerk);

	void ChangePerk(ACPerk* InPrevPerk, ACPerk* InNewPerk);
//=======================================================
// [Variables]
//=======================================================
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Perk")	TSubclassOf<ACPerk> PerkClass;
	class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintAssignable)
	FPerkTypeChanged OnPerkTypeChanged;
private:
	uint32 DeckNumber;
	TArray<ACPerk*> Perks;
	ACPerk* CurrentPerk;
	EPerkType Type;
};
