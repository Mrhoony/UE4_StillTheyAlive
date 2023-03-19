#include "CHUD_Aim.h"
#include "Global.h"
#include "Engine/Canvas.h"

ACHUD_Aim::ACHUD_Aim()
{

}

void ACHUD_Aim::DrawHUD()
{
	Super::DrawHUD();
	CheckNull(Texture);
	CheckFalse(bVisibleAim);

	FVector2D center = FVector2D(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D size = (Texture->GetSurfaceWidth()* 0.5f, Texture->GetSurfaceHeight()* 0.5f);
	FVector2D position = center - size;

	FCanvasTileItem item(position, Texture->Resource, FLinearColor::White);
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_Translucent;
	Canvas->DrawItem(item);
}
