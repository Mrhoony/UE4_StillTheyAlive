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
			
protected:
	virtual void BeginPlay() override;

public:
	void SetScale(float scale);

public:
	FORCEINLINE bool IsCanbuild() { return bCanBuild; }
	FORCEINLINE void SetbuildTrue() { bCanBuild = true; }
	FORCEINLINE void SetbuildFalse() { bCanBuild = false; }

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
