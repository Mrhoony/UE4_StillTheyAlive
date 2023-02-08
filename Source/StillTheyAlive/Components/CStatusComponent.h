#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

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
	FORCEINLINE float GetSneakSpeed() { return SneakSpeed; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() { return RunSpeed; }
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	void SetMove();
	void SetStop();

	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);

//=======================================================
// [Variables]
//=======================================================
private:
	UPROPERTY(EditAnywhere, Category = "Speed")		float SneakSpeed = 200;
	UPROPERTY(EditAnywhere, Category = "Speed")		float WalkSpeed = 400;
	UPROPERTY(EditAnywhere, Category = "Speed")		float RunSpeed = 600;
	UPROPERTY(EditAnywhere, Category = "Health")	float MaxHealth = 100;

private:
	bool bCanMove = true;
	float Health;
	TSubclassOf<class UCUserWidget_PlayerStatus> WidgetClass;
	class UCUserWidget_PlayerStatus* Widget;
};
