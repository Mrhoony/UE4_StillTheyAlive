#include "CStoryGameMode.h"
#include "Global.h"
#include "Core/CGameInstance.h"

void ACStoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;
	// Moeny = // CGameInstance���� ���������̺��� ���� �о�´�.
	// Lifes = // CGameInstance���� ���������̺��� ���� �о�´�.

	//GetGameInstance()->SetCurrnetGameMode();

	// Cast<UCGameInstance>(GetGameInstance())->SetGameModeTypeStory();
}

void ACStoryGameMode::StartNextRound()
{
	// NoticeUI �����
	// ���� ���� ���
	// ���������̺��� ���忡 �ش��ϴ� ���� �ҷ�����
	// ��ġ�� �ʰ� ��ȯ
}

/*
* �÷��̾ GŰ�� ������ ���尡 ���۵ȴ�.
* �÷��̾ GŰ�� ������ �� "Press G-Key to Start Next Round" �ؽ�Ʈ�� �����Ѵ�.
* ���Ӹ��� GŰ�� �������� ���带 �����ϴ� �Լ��� ȣ���ϰ� �ʿ� ������ ��ȯ�������� ���͸� ��ȯ�Ѵ�.
* << ��ȯ������ ��� �޾ƿ� ������?
* ���ʹ� ��ȯ�������� ������������ �̵��ϸ�, ���������� �����ϸ� �����ȴ�.
* ���Ͱ� ���������� �����ؼ� �����Ǹ� ���Ӹ�忡�� �������� 1�� ��´�.
* ���Ӹ���� �������� 0�̵Ǹ� �����й�.
*/