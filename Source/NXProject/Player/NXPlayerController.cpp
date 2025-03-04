#include "Player/NXPlayerController.h"
#include "EnhancedInputSubsystems.h"

ANXPlayerController::ANXPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	WalkAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	CrouchAction(nullptr),
	AttackAction(nullptr),
	ReloadAction(nullptr),
	DashAction(nullptr)
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
}
