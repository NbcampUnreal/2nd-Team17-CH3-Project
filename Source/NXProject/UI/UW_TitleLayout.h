#pragma once  // ��� ������ ���� �� ���ԵǴ� ���� �����ϴ� ��ó���� ���ù�

#include "CoreMinimal.h"  // �𸮾� ������ �⺻ �ʼ� ��� ���� ����
#include "Blueprint/UserWidget.h"  // UUserWidget�� ����ϱ� ���� �ʿ��� ��� ���� ����
#include "UW_TitleLayout.generated.h"  // �ش� Ŭ������ ���� �ڵ� ���� �� ���÷��� �ý��� ����

// UButton Ŭ������ �̸� ���� (��� ������ �ּ������� �����Ͽ� ������ �ӵ� ���)
class UButton;

/**
 * UUW_TitleLayout
 * Ÿ��Ʋ ȭ���� UI ���̾ƿ��� ����ϴ� Ŭ����
 */
UCLASS()
class NXPROJECT_API UUW_TitleLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * ������
	 * - �⺻ ��ü �ʱ�ȭ ������ ���� ���
	 */
	UUW_TitleLayout(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	/**
	 * ������ Ŭ���� �� ȣ��Ǵ� �Լ�
	 * - �⺻������ �������̵� ����
	 */
	virtual void NativeConstruct();

	/**
	 * �÷��� ��ư Ŭ�� �� ����Ǵ� �Լ�
	 */
	UFUNCTION()
	void OnPlayButtonClicked();

	/**
	 * ���� ��ư Ŭ�� �� ����Ǵ� �Լ�
	 */
	UFUNCTION()
	void OnExitButtonClicked();

private:
	/**
	 * �÷��� ��ư (UI���� ���ε���)
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USTitleWidget, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> PlayButton;

	/**
	 * ���� ��ư (UI���� ���ε���)
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USTitleWidget, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> ExitButton;
};
