#include "CGridTrigger.h"
#include "CGridSection.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACGridTrigger::ACGridTrigger()
{
	//GridScale 기본값 //추후 에디터에서 조정
	GridScale = FVector(1);

	//Create Component
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	InstanceMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("InstanceMesh");
	InstanceMesh->SetupAttachment(Scene);

}

void ACGridTrigger::BeginPlay()
{
	Super::BeginPlay();

	CreateGrid(10, 10);
}

void ACGridTrigger::CreateGrid(int32 Width, int32 Depth)
{
	GridX = Width;
	GridY = Depth;
	FVector gridLocation;
	FTransform gridTransform;

	for (int32 i = 0; i < GridX; i++)
	{
		for (int32 j = 0; j < GridY; j++)
		{
			float gridWidth = i * GridSize;
			float gridDepth = j * GridSize;
			gridLocation = FVector(gridWidth, gridDepth, 0.0f);
			gridTransform = UKismetMathLibrary::MakeTransform(gridLocation, FRotator(0.0f), GridScale);
			
			InstanceMesh->AddInstance(gridTransform);
			GridIndex.Add(j);
		}
	}
}
