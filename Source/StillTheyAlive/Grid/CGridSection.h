#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGridSection.generated.h"


UCLASS()
class STILLTHEYALIVE_API ACGridSection : public AActor
{
	GENERATED_BODY()
	
public:	
	ACGridSection();

	FORCEINLINE bool IsCanbuild() { return bCanBuild; }
	FORCEINLINE void SetbuildTrue() { bCanBuild = true; }
	FORCEINLINE void SetbuildFalse() { bCanBuild = false; }

	void SetScale(float scale);
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceDynamic* DynamicMaterial;

private:
	bool bCanBuild;
	FVector Scale;
};
