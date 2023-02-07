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

//=======================================================
// [Blueprintable]
//=======================================================
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

//=======================================================
// [CPPOnly]
//=======================================================
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

	void DoAction();

	void SelectDeck1();
	void SelectDeck2();
	void SelectDeck3();
	void SelectDeck4();
	void SelectDeck5();
	void SelectDeck6();
	void SelectDeck7();
	void SelectDeck8();
	void SelectDeck9();
	void SelectDeck0();

//=======================================================
// [Variables]
//=======================================================
private:
	// Scene Components
	UPROPERTY(VisibleDefaultsOnly) class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly) class UCameraComponent* Camera;

	// Actor Components
	UPROPERTY(VisibleDefaultsOnly) class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly) class UCOptionComponent* Option;
	UPROPERTY(VisibleDefaultsOnly) class UCDeckComponent* Deck;
<<<<<<< HEAD
	UPROPERTY(VisibleDefaultsOnly) class UCStateComponent* State;
=======
	//UPROPERTY(VisibleDefaultsOnly) class UCStateComponent* State;
	//UPROPERTY(VisibleDefaultsOnly) class UCMontagesComponent* Montages;
	//UPROPERTY(VisibleDefaultsOnly) class UCActionComponent* Action;
	//UPROPERTY(VisibleDefaultsOnly) class UCDeckComponent* Deck;
>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b
};
