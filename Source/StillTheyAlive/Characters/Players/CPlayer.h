#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

UCLASS()
class STILLTHEYALIVE_API ACPlayer : public ACharacter , public IICharacter, public IGenericTeamAgentInterface
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
	virtual void Hitted() override;
	virtual void Dead() override;
	FGenericTeamId GetGenericTeamId() const override;

private:
	// Axis Mapping
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void OnZoom(float InAxis);
	void OnJump();

	void DoAction();
	void TechDoAction();
	void TechOffAction();

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

	void StartNextRound();

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
	UPROPERTY(VisibleDefaultsOnly) class UCStateComponent* State;

private:
	UPROPERTY(EditDefaultsOnly)
		uint8 TeamID = 0;
};
