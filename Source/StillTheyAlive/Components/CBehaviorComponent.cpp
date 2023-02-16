#include "CBehaviorComponent.h"
#include "Global.h"
#include "Characters/Players/CPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"


void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCBehaviorComponent::ChangeType(EBehaviorType InType)
{
	EBehaviorType type = GetType();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(type, InType);
}

EBehaviorType UCBehaviorComponent::GetType()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}


bool UCBehaviorComponent::IsApprochMode()
{
	return GetType() == EBehaviorType::Approch;
}

bool UCBehaviorComponent::IsActionMode()
{
	return GetType() == EBehaviorType::Action;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return GetType() == EBehaviorType::Patrol;
}

bool UCBehaviorComponent::IsHittedMode()
{
	return GetType() == EBehaviorType::Hitted;
}

void UCBehaviorComponent::SetApprochMode()
{
	ChangeType(EBehaviorType::Approch);
}

void UCBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UCBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UCBehaviorComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

ACPlayer* UCBehaviorComponent::GetTargetPlayer()
{
	return Cast<ACPlayer>(Blackboard->GetValueAsObject(PlayerKey));
}



