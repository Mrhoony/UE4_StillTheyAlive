#include "StillTheyAliveGameModeBase.h"
#include "Global.h"

AStillTheyAliveGameModeBase::AStillTheyAliveGameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/_Project/Characters/Players/BP_CPlayer.BP_CPlayer_C'");
}