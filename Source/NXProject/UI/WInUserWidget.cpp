#include "UI/WInUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UWInUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UWInUserWidget::OnRestartClicked);
    }

    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UWInUserWidget::OnExitClicked);
    }
}

void UWInUserWidget::OnRestartClicked()
{
    UGameplayStatics::OpenLevel(this, FName("TitleLevel")); // "Level" - 실제 갈 레벨 적기
}

void UWInUserWidget::OnExitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}