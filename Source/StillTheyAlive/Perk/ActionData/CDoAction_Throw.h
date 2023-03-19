#pragma once

#include "CoreMinimal.h"
#include "CDoAction.h"
#include "CDoAction_Throw.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACDoAction_Throw : public ACDoAction
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void DoAction_L() override;
	virtual void End_DoAction_L() override;

	virtual void DoAction_R() override;
	virtual void Begin_DoAction_R() override;

	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void UltimateAction() override;
	virtual void Begin_Ultimate() override;

private:
	UFUNCTION()
		void OnThrowBeginOverlap(FHitResult InHitResult);

private:
	class ACThrow* ThrowObject;
};
