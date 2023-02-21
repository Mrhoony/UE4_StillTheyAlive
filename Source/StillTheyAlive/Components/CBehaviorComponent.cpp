#include "CBehaviorComponent.h"
#include "Global.h"
#include "Characters/Players/CPlayer.h"
#include "Characters/Enemies/CEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFrameWork/Character.h"

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

bool UCBehaviorComponent::IsWaitMode()		{	return GetType() == EBehaviorType::Wait;	}
bool UCBehaviorComponent::IsApproachMode()	{	return GetType() == EBehaviorType::Approach;}
bool UCBehaviorComponent::IsActionMode()	{	return GetType() == EBehaviorType::Action;	}
bool UCBehaviorComponent::IsPatrolMode()	{	return GetType() == EBehaviorType::Patrol;	}
bool UCBehaviorComponent::IsHittedMode()	{	return GetType() == EBehaviorType::Hitted;	}
bool UCBehaviorComponent::IsReturnMode()	{	return GetType() == EBehaviorType::Return;	}
void UCBehaviorComponent::SetWaitMode()		{	ChangeType(EBehaviorType::Wait);			}
void UCBehaviorComponent::SetApproachMode()	{	ChangeType(EBehaviorType::Approach);		}
void UCBehaviorComponent::SetActionMode()	{	ChangeType(EBehaviorType::Action);			}
void UCBehaviorComponent::SetPatrolMode()	{	ChangeType(EBehaviorType::Patrol);			}
void UCBehaviorComponent::SetHittedMode()	{	ChangeType(EBehaviorType::Hitted);			}
void UCBehaviorComponent::SetReturnMode()	{	ChangeType(EBehaviorType::Return);			}
ACharacter* UCBehaviorComponent::GetTarget()
{
	return Cast<ACharacter>(Blackboard->GetValueAsObject(TargetKey));
}

FVector UCBehaviorComponent::GetLocation()
{
	return Blackboard->GetValueAsVector(LocationKey);
}
