#include "CStateComponent.h"

UCStateComponent::UCStateComponent()
{
}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCStateComponent::SetIdle()	{ ChangeType(EStateTypes::Idle); }
void UCStateComponent::SetAction()	{ ChangeType(EStateTypes::Action); }
void UCStateComponent::SetHit()		{ ChangeType(EStateTypes::Hit); }
void UCStateComponent::SetDead()	{ ChangeType(EStateTypes::Dead); }

void UCStateComponent::ChangeType(EStateTypes InNewType)
{
	EStateTypes prevType = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prevType, Type);
}
