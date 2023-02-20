#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD_Aim.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACHUD_Aim : public AHUD
{
	GENERATED_BODY()
	
public:
	ACHUD_Aim();

	virtual void DrawHUD() override;

	FORCEINLINE void VisibleAim() { bVisibleAim = true; }
	FORCEINLINE void VisibleAimHidden() { bVisibleAim = false; }
private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;

private:
	bool bVisibleAim;
};
