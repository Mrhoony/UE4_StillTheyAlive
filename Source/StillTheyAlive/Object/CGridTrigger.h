#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGridTrigger.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACGridTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACGridTrigger();

protected:
	virtual void BeginPlay() override;

private:
	void CreateGrid(int32 Width, int32 Depth);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UInstancedStaticMeshComponent* InstanceMesh;

	UPROPERTY(EditAnywhere)
		FVector GridScale; //에디터에서 그리드 스케일 시행착오
private:
	int32 GridX, GridY;
	float GridSize;
	TArray<FVector> GridLocation;
	TArray<int32> GridIndex;
};
