#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EWalkSpeedTpye : uint8
{
	Sneak, Walk, Run, Max
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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

	//=======================================================
	// [CPPOnly]
	//=======================================================
public:
	FORCEINLINE float GetSneakSpeed() { return  Speed[(int32)EWalkSpeedTpye::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return  Speed[(int32)EWalkSpeedTpye::Walk]; }
	FORCEINLINE float GetRunSpeed() { return  Speed[(int32)EWalkSpeedTpye::Run]; }
	FORCEINLINE bool IsCanMove() { return bCanMove; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE class UCUserWidget_PlayerStatus* GetWidget() { return Widget; }

	void SetMove();
	void SetStop();
	void SetSpeed(EWalkSpeedTpye InType);

	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);

	void CreateStatusWidget(class UCHUD* HUD);

	//=======================================================
	// [Variables]
	//=======================================================
public:
	class ACharacter* OwnerCharacter;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")		float Speed[(int32)EWalkSpeedTpye::Max] = { 200, 400, 600 };
	UPROPERTY(EditAnywhere, Category = "Health")	float MaxHealth = 100;

private:
	bool bCanMove = true;
	float Health;
	TSubclassOf<class UCUserWidget_PlayerStatus> WidgetClass;
	class UCUserWidget_PlayerStatus* Widget;
};