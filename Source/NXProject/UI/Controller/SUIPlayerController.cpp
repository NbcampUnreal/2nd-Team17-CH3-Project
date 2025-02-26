#include "UI/Controller/SUIPlayerController.h"
#include "Blueprint/UserWidget.h"

/*
 * ASUIPlayerController::BeginPlay()

 * - ������ ���۵� �� ȣ���.
 * - UI ������ �����ϰ� ȭ�鿡 �߰��� ��, �Է� ��带 UI �������� ����.
 */

void ASUIPlayerController::BeginPlay()
{
	Super::BeginPlay(); // �θ� Ŭ������ BeginPlay() ����.

	// UI ���� Ŭ������ ��ȿ���� Ȯ��
	if (true == ::IsValid(UIWidgetClass))
	{
		// UI ���� �ν��Ͻ��� ���� (this: ���� ��Ʈ�ѷ��� �����ڷ� ����)
		UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);

		// CreateWidget()�� ȣ��� �� UIWidgetInstance->NativeOnInitialize() �Լ��� ���������� ȣ���.

		// UI ���� �ν��Ͻ��� ���������� �����Ǿ����� Ȯ��
		if (true == ::IsValid(UIWidgetInstance))
		{
			// UI ������ ȭ��(Viewport)�� �߰�
			UIWidgetInstance->AddToViewport();

			// AddToViewport()�� ȣ��� �� UIWidgetInstance->NativeConstruct() �Լ��� ���������� ȣ���.

			// UI ���� �Է� ��� ���� (�÷��̾� �Է��� UI �������� ����)
			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget()); // UI ������ ��Ŀ���� ����
			//SetInputMode(Mode); // �÷��̾� ��Ʈ�ѷ��� �Է� ��带 UI �������� ����/�ϸ� �ȵ� �׷��� �� ������

			// ���콺 Ŀ���� ȭ�鿡 ǥ��
			bShowMouseCursor = true;
		}
	}
}
