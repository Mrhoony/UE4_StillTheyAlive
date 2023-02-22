#include "CAIControllerSpawn.h"
#include "Global.h"
#include "Components/CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFrameWork/Character.h"
#include "Characters/Players/CSpawnCharacter.h"
#include "Characters/Players/CPlayer.h"

ACAIControllerSpawn::ACAIControllerSpawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent<UCBehaviorComponent>(this, &Behavior, "Behavior");
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1000.f;
	Sight->PeripheralVisionAngleDegrees = 180.0f;
	Sight->SetMaxAge(2.f);

	//Team
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());

	SetGenericTeamId(FGenericTeamId(0));
}

void ACAIControllerSpawn::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerCharacter = Cast<ACSpawnCharacter>(InPawn);
	UseBlackboard(OwnerCharacter->GetBehaviorTree()->BlackboardAsset, Blackboard);

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIControllerSpawn::OnPerceptionUpdated);

	Behavior->SetBlackBoard(Blackboard);

	RunBehaviorTree(OwnerCharacter->GetBehaviorTree());

}

ETeamAttitude::Type ACAIControllerSpawn::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (APawn const* OtherPawn = Cast<APawn>(&Other))
	{
		if (Cast<ACPlayer>(OtherPawn))
			return ETeamAttitude::Friendly;
		if (auto const TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			if (TeamAgent->GetGenericTeamId() == FGenericTeamId(0))
			{
				return ETeamAttitude::Friendly;
			}
			else
			{
				return ETeamAttitude::Hostile;
			}
		}
	}
	return ETeamAttitude::Neutral;
}

void ACAIControllerSpawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIControllerSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACAIControllerSpawn::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}

void ACAIControllerSpawn::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	ACharacter* target = nullptr;

	for (AActor* actor : actors)
	{
		target = Cast<ACharacter>(actor);

		if (!!target)
			break;
	}

	Blackboard->SetValueAsObject("Target", target);
}
