#pragma once

#include "CoreMinimal.h"
#include "Perk/ActionData/CDoAction.h"
#include "CDoAction_Melee.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void DoAction_L() override;
	virtual void DoAction_R() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
	virtual void DoOffAction_R() override;
	virtual void UltimateAction() override;
	virtual void Begin_Ultimate() override;
	
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;

public:
	FORCEINLINE void EnableCombo() { bCanCombo = true; }
	FORCEINLINE void DisableCombo() { bCanCombo = false; }
	FORCEINLINE void ClearHittedCharacters() { HittedCharacters.Empty(); }
	FORCEINLINE FString GetSpecificCollisionName() { return Datas[ComboCount].SpecificCollisionName; }

private:
	UFUNCTION()
		void RestoreGlobalTimeDilation();

private:
	int32 ComboCount;
	bool bCanCombo;
	bool bSucceed;

	TArray<class ACharacter*> HittedCharacters;
};
