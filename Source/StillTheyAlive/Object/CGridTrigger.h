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

	FORCEINLINE float GetGridSize() { return GridSize; }
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
		FVector GridScale; //�����Ϳ��� �׸��� ������ ��������

	UPROPERTY(VisibleAnywhere)
		TArray<class ACGridSection*> GridClass;
private:
	int32 GridX, GridY;
	float GridSize;
	TArray<FVector> GridLocation;
	TArray<int32> GridIndex;
	class ACGridSection* Grid;
};
