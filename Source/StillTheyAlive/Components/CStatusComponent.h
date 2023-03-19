#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EWalkSpeedTpye : uint8
{
	Sneak, Walk, Run, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STILLTHEYALIVE_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();
	
//=======================================================
// [Blueprint]
//=======================================================
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
		void CreateStatusWidget();

//=======================================================
// [CPPOnly]
//=======================================================
public:
	FORCEINLINE float GetSneakSpeed() { return  Speed[(int32)EWalkSpeedTpye::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return  Speed[(int32)EWalkSpeedTpye::Walk]; }
	FORCEINLINE float GetRunSpeed() { return  Speed[(int32)EWalkSpeedTpye::Run]; }
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return CurrentHealth; }
	FORCEINLINE float GetMaxMana() { return MaxMana; }
	FORCEINLINE float GetMana() { return CurrentMana; }

	void SetMove();
	void SetStop();
	void SetSpeed(EWalkSpeedTpye InType);

	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);

//=======================================================
// [Variables]
//=======================================================
private:
	UPROPERTY(EditAnywhere, Category = "Speed")		float Speed[(int32)EWalkSpeedTpye::Max] = { 200, 400, 600 };
	UPROPERTY(EditAnywhere, Category = "Health")	float MaxHealth = 100;
	UPROPERTY(EditAnywhere, Category = "Mana")	float MaxMana = 100;

private:
	bool bCanMove = true;
	float CurrentHealth;
	float CurrentMana;
	TSubclassOf<class UCUserWidget_PlayerStatus> WidgetClass;
	class UCUserWidget_PlayerStatus* Widget;
};
