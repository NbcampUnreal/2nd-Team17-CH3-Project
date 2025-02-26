#include "UI/UW_TitleLayout.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

/**
 * ������
 * - �θ� Ŭ������ �����ڸ� ȣ���Ͽ� ��ü�� �ʱ�ȭ
 */
UUW_TitleLayout::UUW_TitleLayout(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/**
 * ������ ������ �� ����Ǵ� �Լ� - ��ư Ŭ�� �̺�Ʈ�� ���ε���
 */
void UUW_TitleLayout::NativeConstruct()
{
	// ��ư�� ��ȿ���� Ȯ�� �� Ŭ�� �̺�Ʈ�� ���ε�
	PlayButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnPlayButtonClicked);
	ExitButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnPlayButtonClicked);

}

/**
 * �÷��� ��ư Ŭ�� �� ȣ��Ǵ� �Լ�
 * - "TitleLevel"�̶�� �̸��� ������ �ε���
 */
void UUW_TitleLayout::OnPlayButtonClicked()
{
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("undercity"));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Loading")), true, FString(TEXT("NextLevel=undercity")));
	// NextLevel�� Key, Example�� Value��. �׷� Loading ���������� NextLevel�� �Ľ��ؼ� Example ���� ���� ��.
}

/**
 * ���� ��ư Ŭ�� �� ȣ��Ǵ� �Լ�
 * - ������ ������
 */
void UUW_TitleLayout::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}