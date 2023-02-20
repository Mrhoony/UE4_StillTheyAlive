#include "CGuidePoint.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ACGuidePoint::ACGuidePoint()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	CHelpers::CreateSceneComponent(this, &Box, "CheckBox", Scene);
}