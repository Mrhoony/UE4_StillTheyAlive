#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "CPlayer.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

// -------------------------------------------------------
// Blueprintable Methods
// -------------------------------------------------------
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

// -------------------------------------------------------
// CPPOnly Methods
// -------------------------------------------------------
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Axis Mapping
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void OnZoom(float InAxis);
	void OnJump();

// -------------------------------------------------------
// Variables
// -------------------------------------------------------
private:
	// Scene Components
	UPROPERTY(VisibleDefaultsOnly) class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly) class UCameraComponent* Camera;

	// Actor Components
	UPROPERTY(VisibleDefaultsOnly) class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly) class UCOptionComponent* Option;
	//UPROPERTY(VisibleDefaultsOnly) class UCStateComponent* State;
	//UPROPERTY(VisibleDefaultsOnly) class UCMontagesComponent* Montages;
	//UPROPERTY(VisibleDefaultsOnly) class UCActionComponent* Action;
	UPROPERTY(VisibleDefaultsOnly) class UCDeckComponent* Deck;
};
