#include "CStoryGameMode.h"
#include "Global.h"
#include "Core/CGameInstance.h"

void ACStoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;
	// Moeny = // CGameInstance���� ���������̺��� ���� �о�´�.
	// Lifes = // CGameInstance���� ���������̺��� ���� �о�´�.
}

void ACStoryGameMode::PlayNextRound()
{
	// NoticeUI �����
	// ���� ���� ���
	// ���������̺��� ���忡 �ش��ϴ� ���� �ҷ�����
	// ��ġ�� �ʰ� 
}
