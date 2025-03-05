#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WInUserWidget.generated.h"

UCLASS()
class NXPROJECT_API UWInUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnExitClicked();

public:
	UPROPERTY(meta = (BindWidget))//블프 버튼 연결
		class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;
};
