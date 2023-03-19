#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartDoor.generated.h"

UCLASS()
class STILLTHEYALIVE_API AStartDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AStartDoor();

protected:
	virtual void BeginPlay() override;

public:
	void OpenDoor();

public:
	UFUNCTION()
		void DestroyActor();

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Mesh;
};
