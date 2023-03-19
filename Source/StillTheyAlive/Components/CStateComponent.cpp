#include "CStateComponent.h"
#include "Net/UnrealNetwork.h"

UCStateComponent::UCStateComponent()
{
}

void UCStateComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCStateComponent, Type);

}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCStateComponent::SetIdle()	{ ChangeType(EStateTypes::Idle);	}
void UCStateComponent::SetAction()	{ ChangeType(EStateTypes::Action);	}
void UCStateComponent::SetHit()		{ ChangeType(EStateTypes::Hit);		}
void UCStateComponent::SetDead()	{ ChangeType(EStateTypes::Dead);	}
void UCStateComponent::SetEquip()   { ChangeType(EStateTypes::Equip);	}

void UCStateComponent::ChangeType(EStateTypes InNewType)
{
	EStateTypes prevType = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prevType, Type);
}

