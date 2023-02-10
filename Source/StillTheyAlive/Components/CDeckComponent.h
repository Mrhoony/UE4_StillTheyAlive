#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDeckComponent.generated.h"

UENUM(BlueprintType)
enum class EPerkType : uint8
{
	Unarmed, Weapon, Trap, Spawn, Trinket, Max
};

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
	FORCEINLINE class ACPerk* GetCurrentPerk() { return CurrentPerk; }

private:
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

	void ChangePerk(class ACPerk* InPrevPerk, class  ACPerk* InNewPerk);

//=======================================================
// [Variables]
//=======================================================
private:
	UPROPERTY(EditAnywhere, Category = "Perk")	TArray<TSubclassOf<class ACPerk>> PerkClass;
public:
	
	class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintAssignable)
	FPerkTypeChanged OnPerkTypeChanged;

private:
	uint32 DeckNumber;
	TArray<class ACPerk*> DeckPerks;
	TArray<class ACPerk*> Perks;
	class ACPerk* CurrentPerk;
	class ACPerk* BeforePerk;

	EPerkType Type;
};
