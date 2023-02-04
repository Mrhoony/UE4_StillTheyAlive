#pragma once

#include "CoreMinimal.h"
#include "Perk/Trap/CTrap.h"
#include "CTrap_Brimstone.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACTrap_Brimstone : public ACTrap
{
	GENERATED_BODY()

public:
	ACTrap_Brimstone();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
		void Burn(class AActor* OtherActor);

private:
	UFUNCTION()
		void RegenerateUseResource();

//=======================================================
// [Variables]
//=======================================================
private:
	FString Name;
	FString Description;
	ETrapType TrapType;
	int32 BuyPrice;
	int32 BuildCost;
	float MaxMana = 100.0f;
	float CurMana;
	float NeedMana = 30.0f;
	float BaseDamage;
	float FinalDamage;

	// 구현 예정
	//FString Upgrade;
	//int32 Upgrade1Cost;
	//int32 Upgrade2Cost;
	//int32 Upgrade3Cost;
	//FString Unique1;
	//FString Unique2;
	//int32 UniqueCost;
	//bool HasUnique;
};
