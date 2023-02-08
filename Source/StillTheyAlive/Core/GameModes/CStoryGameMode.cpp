#include "CStoryGameMode.h"
#include "Global.h"
#include "Core/CGameInstance.h"

void ACStoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;
	// Moeny = // CGameInstance에서 데이터테이블의 값을 읽어온다.
	// Lifes = // CGameInstance에서 데이터테이블의 값을 읽어온다.
}

void ACStoryGameMode::PlayNextRound()
{
	// NoticeUI 숨기기
	// 시작 음악 재생
	// 데이터테이블에서 라운드에 해당하는 몬스터 불러오기
	// 겹치지 않게 
}
