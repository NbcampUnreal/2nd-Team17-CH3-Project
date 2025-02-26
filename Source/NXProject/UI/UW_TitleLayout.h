#pragma once  // 헤더 파일이 여러 번 포함되는 것을 방지하는 전처리기 지시문

#include "CoreMinimal.h"  // 언리얼 엔진의 기본 필수 헤더 파일 포함
#include "Blueprint/UserWidget.h"  // UUserWidget을 사용하기 위해 필요한 헤더 파일 포함
#include "UW_TitleLayout.generated.h"  // 해당 클래스에 대한 코드 생성 및 리플렉션 시스템 지원

// UButton 클래스를 미리 선언 (헤더 파일을 최소한으로 포함하여 컴파일 속도 향상)
class UButton;

/**
 * UUW_TitleLayout
 * 타이틀 화면의 UI 레이아웃을 담당하는 클래스
 */
UCLASS()
class NXPROJECT_API UUW_TitleLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * 생성자
	 * - 기본 객체 초기화 설정을 위해 사용
	 */
	UUW_TitleLayout(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	/**
	 * 위젯이 클릭될 때 호출되는 함수
	 * - 기본적으로 오버라이드 가능
	 */
	virtual void NativeConstruct();

	/**
	 * 플레이 버튼 클릭 시 실행되는 함수
	 */
	UFUNCTION()
	void OnPlayButtonClicked();

	/**
	 * 종료 버튼 클릭 시 실행되는 함수
	 */
	UFUNCTION()
	void OnExitButtonClicked();

private:
	/**
	 * 플레이 버튼 (UI에서 바인딩됨)
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USTitleWidget, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> PlayButton;

	/**
	 * 종료 버튼 (UI에서 바인딩됨)
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USTitleWidget, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> ExitButton;
};
