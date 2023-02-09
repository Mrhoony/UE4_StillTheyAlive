#include "CPlayer.h"
#include "Global.h"

#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CDeckComponent.h"
#include "Core/CGameInstance.h"
#include "Core/GameModes/CStoryGameMode.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create SceneComponent
	CHelpers::CreateSceneComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateSceneComponent(this, &Camera, "Camera", SpringArm);

	// Create ActorComponent
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &Option, "Option");
	CHelpers::CreateActorComponent(this, &Deck, "Deck");

	// Component Settings
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/_Project/Characters/Players/Mannequin/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass<UAnimInstance>(&animInstanceClass, "AnimBlueprint'/Game/_Project/Characters/Players/AB_CPlayer.AB_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	// Movement Settings
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = 600; //Status->GetRunSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACPlayer::BeginPlay() { Super::BeginPlay(); }
void ACPlayer::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACPlayer::OnJump);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ACPlayer::DoAction);
	
	PlayerInputComponent->BindAction("Deck1", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck1);
	PlayerInputComponent->BindAction("Deck2", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck2);
	PlayerInputComponent->BindAction("Deck3", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck3);
	PlayerInputComponent->BindAction("Deck4", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck4);
	PlayerInputComponent->BindAction("Deck5", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck5);
	PlayerInputComponent->BindAction("Deck6", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck6);
	PlayerInputComponent->BindAction("Deck7", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck7);
	PlayerInputComponent->BindAction("Deck8", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck8);
	PlayerInputComponent->BindAction("Deck9", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck9);
	PlayerInputComponent->BindAction("Deck0", EInputEvent::IE_Pressed, this, &ACPlayer::SelectDeck0);
	
	PlayerInputComponent->BindAction("StartRound", EInputEvent::IE_Pressed, this, &ACPlayer::StartNextRound);
}

void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Status->IsCanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}
void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->IsCanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}
void ACPlayer::OnVerticalLook(float InAxis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}
void ACPlayer::OnZoom(float InAxis)
{
	SpringArm->TargetArmLength += Option->GetZoomSpeed() * InAxis * GetWorld()->GetDeltaSeconds();
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, Option->GetZoomRange().X, Option->GetZoomRange().Y);
}

void ACPlayer::OnJump() { this->Jump(); }
void ACPlayer::DoAction() { Deck->PerkAction(); }

void ACPlayer::SelectDeck1() { Deck->SetCurrentPerk(0); }
void ACPlayer::SelectDeck2() { Deck->SetCurrentPerk(1); }
void ACPlayer::SelectDeck3() { Deck->SetCurrentPerk(2); }
void ACPlayer::SelectDeck4() { Deck->SetCurrentPerk(3); }
void ACPlayer::SelectDeck5() { Deck->SetCurrentPerk(4); }
void ACPlayer::SelectDeck6() { Deck->SetCurrentPerk(5); }
void ACPlayer::SelectDeck7() { Deck->SetCurrentPerk(6); }
void ACPlayer::SelectDeck8() { Deck->SetCurrentPerk(7); }
void ACPlayer::SelectDeck9() { Deck->SetCurrentPerk(8); }
void ACPlayer::SelectDeck0() { Deck->SetCurrentPerk(9); }

void ACPlayer::StartNextRound()
{
	EGameModeTypes type = Cast<UCGameInstance>(GetGameInstance())->GetGameModeType();

	switch (type)
	{
		case EGameModeTypes::Story:
		{
			ACStoryGameMode* storyMode = Cast<ACStoryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			storyMode->StartNextRound();
		}break;
		case EGameModeTypes::Endless:
		{
			//Cast<ACEndlessGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->StartNextRound();
		}break;
	} // switch (type)
}
