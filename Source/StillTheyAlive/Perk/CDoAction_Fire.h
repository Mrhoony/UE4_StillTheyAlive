#pragma once

#include "CoreMinimal.h"
#include "Perk/CDoAction.h"
#include "CDoAction_Fire.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACDoAction_Fire : public ACDoAction
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void DoAction_L() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void DoAction_R() override;
	virtual void DoOffAction_R() override;
private:
	UFUNCTION()
		void OnThrowBeginOverlap(FHitResult InHitResult);

	UFUNCTION()
		void ABortByActionTypeChanged(EActionType InPrevType, EActionType InNewType);

private:
	UPROPERTY()
		class UCAimAction* Aim;

	class ACThrow* ThrowObject;
};
