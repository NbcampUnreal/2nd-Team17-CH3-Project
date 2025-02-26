#include "UI/Controller/SUIPlayerController.h"
#include "Blueprint/UserWidget.h"

/*
 * ASUIPlayerController::BeginPlay()

 * - 게임이 시작될 때 호출됨.
 * - UI 위젯을 생성하고 화면에 추가한 후, 입력 모드를 UI 전용으로 변경.
 */

void ASUIPlayerController::BeginPlay()
{
	Super::BeginPlay(); // 부모 클래스의 BeginPlay() 실행.

	// UI 위젯 클래스가 유효한지 확인
	if (true == ::IsValid(UIWidgetClass))
	{
		// UI 위젯 인스턴스를 생성 (this: 현재 컨트롤러가 소유자로 설정)
		UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);

		// CreateWidget()이 호출될 때 UIWidgetInstance->NativeOnInitialize() 함수가 내부적으로 호출됨.

		// UI 위젯 인스턴스가 정상적으로 생성되었는지 확인
		if (true == ::IsValid(UIWidgetInstance))
		{
			// UI 위젯을 화면(Viewport)에 추가
			UIWidgetInstance->AddToViewport();

			// AddToViewport()가 호출될 때 UIWidgetInstance->NativeConstruct() 함수가 내부적으로 호출됨.

			// UI 전용 입력 모드 설정 (플레이어 입력을 UI 위젯으로 제한)
			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget()); // UI 위젯을 포커스로 지정
			//SetInputMode(Mode); // 플레이어 컨트롤러의 입력 모드를 UI 전용으로 변경/하면 안됨 그러면 안 움직임

			// 마우스 커서를 화면에 표시
			bShowMouseCursor = true;
		}
	}
}
