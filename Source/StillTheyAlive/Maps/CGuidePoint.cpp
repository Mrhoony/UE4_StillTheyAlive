#include "CGuidePoint.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACGuidePoint::ACGuidePoint()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	CHelpers::CreateSceneComponent(this, &Box, "CheckBox", Scene);
	CHelpers::CreateSceneComponent(this, &TextRender, "TextRender", Scene);

	Box->SetBoxExtent(FVector(500, 500, 300));
	Box->SetRelativeLocation(FVector(0, 0, 290));

	TextRender->TextRenderColor = FColor::Red;
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRender->WorldSize = 100.f;
	
}