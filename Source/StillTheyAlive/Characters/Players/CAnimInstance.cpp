#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	UCDeckComponent* deck = CHelpers::GetComponent<UCDeckComponent>(character);
	CheckNull(deck);
	
	deck->OnPerkTypeChanged.AddDynamic(this, &UCAnimInstance::OnPerkTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());
	IsFalling = character->GetCharacterMovement()->IsFalling();
}

void UCAnimInstance::OnPerkTypeChanged(EPerkType InPrevType, EPerkType InNewType)
{
	PerkType = InNewType;
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InNewType)
{
	WeaponType = InNewType;
}
