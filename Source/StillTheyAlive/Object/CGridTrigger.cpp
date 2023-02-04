#include "CGridTrigger.h"
#include "CGridSection.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACGridTrigger::ACGridTrigger()
{
	GridScale = FVector(1);
	GridSize = 100.f;

	//Create Component
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;
	Scene->SetVisibility(true);

	InstanceMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("InstanceMesh");
	InstanceMesh->SetupAttachment(Scene);
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/Meshes/Plane.Plane'"));
	if (meshAsset.Succeeded())
		InstanceMesh->SetStaticMesh(meshAsset.Object);
	ConstructorHelpers::FObjectFinder<UMaterialInstance> materialAsset(TEXT("MaterialInstanceConstant'/Game/Material/MAT_Demo_Inst.MAT_Demo_Inst'"));
	if (materialAsset.Succeeded())
		InstanceMesh->SetMaterial(0, materialAsset.Object);

	InstanceMesh->SetVisibility(true);
}

void ACGridTrigger::BeginPlay()
{
	Super::BeginPlay();

	CreateGrid(10, 10);

	for (int i = 0; i < GridIndex.Num(); i++)
	{
		FTransform gridTransform;
		InstanceMesh->GetInstanceTransform(i, gridTransform, true);
		if (!GetWorld()) return;
		
		GridClass.Emplace(Cast<ACGridSection>(GetWorld()->SpawnActor(ACGridSection::StaticClass(), &gridTransform)));
		GridClass.Top()->SetScale(0.1f);
	}
}

void ACGridTrigger::CreateGrid(int32 Width, int32 Depth)
{
	GridX = Width;
	GridY = Depth;
	FTransform gridTransform;

	for (int32 i = 0; i < GridX; i++)
	{
		for (int32 j = 0; j < GridY; j++)
		{
			float gridWidth = i * GridSize;
			float gridDepth = j * GridSize;
			GridLocation.Emplace(FVector(gridWidth, gridDepth, 0.0f));
			gridTransform = UKismetMathLibrary::MakeTransform(GridLocation.Top(), FRotator(0.0f), GridScale);
			
			InstanceMesh->AddInstance(gridTransform);
			GridIndex.Add(j);
		}
	}
}
