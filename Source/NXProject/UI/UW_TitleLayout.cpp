#include "UI/UW_TitleLayout.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

/**
 * 생성자
 * - 부모 클래스의 생성자를 호출하여 객체를 초기화
 */
UUW_TitleLayout::UUW_TitleLayout(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/**
 * 위젯이 생성될 때 실행되는 함수 - 버튼 클릭 이벤트를 바인딩함
 */
void UUW_TitleLayout::NativeConstruct()
{
	// 버튼이 유효한지 확인 후 클릭 이벤트를 바인딩
	PlayButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnPlayButtonClicked);
	ExitButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnPlayButtonClicked);

}

/**
 * 플레이 버튼 클릭 시 호출되는 함수
 * - "TitleLevel"이라는 이름의 레벨을 로드함
 */
void UUW_TitleLayout::OnPlayButtonClicked()
{
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("undercity"));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Loading")), true, FString(TEXT("NextLevel=undercity")));
	// NextLevel이 Key, Example가 Value임. 그럼 Loading 레벨에서는 NextLevel을 파싱해서 Example 값을 얻어내면 됨.
}

/**
 * 종료 버튼 클릭 시 호출되는 함수
 * - 게임을 종료함
 */
void UUW_TitleLayout::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}