// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSpawn.generated.h"

UCLASS()
class STILLTHEYALIVE_API ABossSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Scene;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
