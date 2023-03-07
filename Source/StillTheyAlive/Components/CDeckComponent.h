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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)		FORCEINLINE bool IsPerkUnarmed() { return Type == EPerkType::Unarmed; }
	UFUNCTION(BlueprintPure)		FORCEINLINE bool IsPerkWeapon() { return Type == EPerkType::Weapon; }
	UFUNCTION(BlueprintPure)		FORCEINLINE bool IsPerkTrap() { return Type == EPerkType::Trap; }
	UFUNCTION(BlueprintPure)		FORCEINLINE bool IsPerkSpawn() { return Type == EPerkType::Spawn; }
	UFUNCTION(BlueprintPure)		FORCEINLINE bool IsPerkTrinket() { return Type == EPerkType::Trinket; }

public:
	FORCEINLINE class ACPerk* GetCurrentPerk() { return CurrentPerk; }
	FORCEINLINE TArray<class ACPerk*> GetPerks() { return Perks; }
	FORCEINLINE class UCUserWidget_Deck* GetWidget() { return Widget; }

public:
	void SetUnarmed();
	void SetWeapon();
	void SetTrap();
	void SetSpawn();
	void SetTrinket();

public:
	UFUNCTION(NetMulticast, Reliable)
		void PerkAction();
		void PerkAction_Implementation();

	UFUNCTION(Reliable, Server)
		void ServerPerkAction();
		void ServerPerkAction_Implementation();

	UFUNCTION(NetMulticast, Reliable)
		void PerkEndAction();
		void PerkEndAction_Implementation();

	UFUNCTION(Reliable, Server) 
		void ServerPerkEndAction();
		void ServerPerkEndAction_Implementation();

	UFUNCTION(NetMulticast, Reliable) 
		void PerkTechAction();
		void PerkTechAction_Implementation();

	UFUNCTION(Reliable, Server) 
		void ServerPerkTechAction();
		void ServerPerkTechAction_Implementation();

	UFUNCTION(NetMulticast, Reliable)
		void PerkTechOffAction();
		void PerkTechOffAction_Implementation();

	UFUNCTION(Reliable, Server) 
		void ServerPerkTechOffAction();
		void ServerPerkTechOffAction_Implementation();

	UFUNCTION(NetMulticast, Reliable) 
		void PerkUltimate();
	void PerkUltimate_Implementation();

	UFUNCTION(Reliable, Server) 
		void ServerPerkUltimate();
		void ServerPerkUltimate_Implementation();

	UFUNCTION(Reliable, Server)
		void SetCurrentPerk(int index);
		void SetCurrentPerk_Implementation(int index);

	UFUNCTION(NetMulticast, Reliable)
		void MultiSetCurrentPerk(int index);
		void MultiSetCurrentPerk_Implementation(int index);

	void ChangePerk(class ACPerk* InPrevPerk, class  ACPerk* InNewPerk);
	void Dead();
	void EndDead();
	void CreateDeckWidget(class UCHUD* HUD);

private:
	void ChangeType(EPerkType InType);
//=======================================================
// [Variables]
//=======================================================
private:
	UPROPERTY(EditAnywhere, Category = "Perk")	TArray<TSubclassOf<class ACPerk>> PerkClass;

public:	
	UPROPERTY(BlueprintAssignable)
	FPerkTypeChanged OnPerkTypeChanged;

	//UPROPERTY(Replicated)
	class ACharacter* OwnerCharacter;
private:
	//UPROPERTY(Replicated)
	uint32 DeckNumber;

	//UPROPERTY(Replicated)
	class ACPerk* CurrentPerk;

	//UPROPERTY(Replicated)
	class ACPerk* BeforePerk;

	//UPROPERTY(Replicated)
	EPerkType Type;

	UPROPERTY(Replicated)
	class UCStateComponent* OwnerState;


	TArray<class ACPerk*> Perks;
	class UCUserWidget_Deck* Widget;
	TSubclassOf<class UCUserWidget_Deck> WidgetClass;
};
