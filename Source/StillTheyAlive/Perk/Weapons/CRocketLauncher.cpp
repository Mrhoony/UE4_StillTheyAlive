#include "CRocketLauncher.h"
#include "Global.h"
#include "Characters/Players/CPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACRocketLauncher::ACRocketLauncher()
{
	WeaponType = EWeaponType::RocketLauncher;
}

void ACRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
}

void ACRocketLauncher::WeaponTypeChanged()
{
	Super::WeaponTypeChanged();
}

void ACRocketLauncher::TechAction()
{

}