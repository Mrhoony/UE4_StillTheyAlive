#include "CGridSection.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"

ACGridSection::ACGridSection()
{
	bCanBuild = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));
	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
}

void ACGridSection::BeginPlay()
{
	Super::BeginPlay();
	
	UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Material/MAT_Demo_Inst.MAT_Demo_Inst'"));
	UMaterialInstanceConstant* materialInstance = Cast<UMaterialInstanceConstant>(obj);
	if (!materialInstance) return;
	
	DynamicMaterial = UMaterialInstanceDynamic::Create(materialInstance, nullptr);
	Mesh->SetMaterial(0, DynamicMaterial);
}

void ACGridSection::SetbuildTrue()
{
	bCanBuild = true;
}

void ACGridSection::SetbuildFalse()
{
	bCanBuild = false;
}