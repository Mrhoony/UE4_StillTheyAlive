#include "CAnimInstance.h"
#include "Global.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

<<<<<<< HEAD
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(character);
	CheckNull(state);

	/*
	* CurrentPerk의 PerkType에 따라 AnimInstance에서 분기해주려고 함
	* TODO: 22, 23, 26 해결필요, 해결되면 17~20 주석 삭제
	*/

	//UDeckComponent* deck = CHelpers::GetComponent<UDeckComponent>(character);
	//CheckNull(deck);

	state->OnStateTypeChanged.AddDynamic(this, &UCAnimInstance::OnStateTypeChanged);
	//deck->OnPerkTypeChanged.AddDynamic(this, &UCAnimInstance::OnDeckTypeChanged);
=======
	//UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(character);
	//CheckNull(action);

//	action->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b
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

<<<<<<< HEAD
void UCAnimInstance::OnPerkTypeChanged(EPerkType InPrevType, EPerkType InNewType) { PerkType = InNewType; }
void UCAnimInstance::OnStateTypeChanged(EStateTypes InPrevType, EStateTypes InNewType) { StateType = InNewType; }
=======
//void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
//{
//	ActionType = InNewType;
//}
>>>>>>> 0e1781a0c5016e450e78998f9717c3714d1d314b
