#include "BossSpawn.h"
#include "Global.h"
ABossSpawn::ABossSpawn()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;
}

void ABossSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

