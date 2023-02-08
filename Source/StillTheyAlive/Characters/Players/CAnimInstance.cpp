#include "CAnimInstance.h"
#include "Global.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(character);
	CheckNull(state);

	/*
	* CurrentPerk�� PerkType�� ���� AnimInstance���� �б����ַ��� ��
	* TODO: 22, 23, 26 �ذ��ʿ�, �ذ�Ǹ� 17~20 �ּ� ����
	*/

	//UDeckComponent* deck = CHelpers::GetComponent<UDeckComponent>(character);
	//CheckNull(deck);

	state->OnStateTypeChanged.AddDynamic(this, &UCAnimInstance::OnStateTypeChanged);
	//deck->OnPerkTypeChanged.AddDynamic(this, &UCAnimInstance::OnDeckTypeChanged);
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

void UCAnimInstance::OnPerkTypeChanged(EPerkType InPrevType, EPerkType InNewType) { PerkType = InNewType; }
void UCAnimInstance::OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType) { StateType = InNewType; }
