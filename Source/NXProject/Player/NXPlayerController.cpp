#include "Player/NXPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Game/NXGameState.h"

ANXPlayerController::ANXPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	WalkAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	CrouchAction(nullptr),
	AttackAction(nullptr),
	ReloadAction(nullptr),
	DashAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr)
{
}

void ANXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
		CrosshairUI = CreateWidget<UUserWidget>(this, CrossHairClass);
		if (CrosshairUI)
		{
			CrosshairUI->AddToViewport();
		}
	}
}

UUserWidget* ANXPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

//void ANXPlayerController::ShowMainMenu(bool bIsRestart)
//{
//	if (bIsRestart)
//	{
//		UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
//		if (PlayAnimFunc)
//		{
//			MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
//		}
//	}
//}