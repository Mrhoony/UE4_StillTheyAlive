#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CDeckComponent.h"
#include "CAttachment.h"
#include "CPerk.generated.h"

USTRUCT(BlueprintType)
struct FPerkInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UTexture2D* PerkImage;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACPerk> PerkClass;
};

UENUM(BlueprintType)
enum class EPerkType : uint8
{
	Unarmed, Weapon, Trap, Spawn, Trinket, Max
};

UCLASS()
class STILLTHEYALIVE_API ACPerk : public ACAttachment
{
	GENERATED_BODY()
	
public:	
	ACPerk();
	
protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UPerkActionData* GetCurrent() { return Data; }

public:
	UFUNCTION()
	virtual void L_Action();

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EPerkType::Unarmed; }

public:
	void SetUnarmed();
	void SetWeapon();
	void SetTrap();
	void SetSpawn();
	void SetTrinket();

private:
	void SetMode(EPerkType InType);
	void ChangeType(EPerkType InType);

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
	UPROPERTY(EditDefaultsOnly)
		EPerkType Type;

	UPROPERTY(EditDefaultsOnly)
		class UPerkActionData* Data;

private:
	class UCDeckComponent* Deck;


};