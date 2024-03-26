#include "PRPlayerController.h"
#include "PRGrid.h"
#include "PRMenuManager.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#define CURSORTHRESHOLD .25f
#define MOUSEMODETHRESHOLD .05f

void APRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* EPS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EPS->AddMappingContext(ControllerInputContext, 0);
	}

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(Input, ETriggerEvent::Triggered, this, &APRPlayerController::InputFunction);
	}
}

void APRPlayerController::InputFunction(const FInputActionValue& Value)
{

}

void APRPlayerController::Init(APRGrid* Map, APRMenuManager* NewMenuManager)
{
	Grid = Map;
	MenuManager = NewMenuManager;

	MenuManager->OnLevelStatusChanged.AddDynamic(this, &APRPlayerController::LevelStatusChanged);
}

void APRPlayerController::Select()
{
	if(IsMenuInput()) return;
	if(!IsValid(Grid)) return;
	Grid->SelectCurrentMemberOnCell();
}

void APRPlayerController::PauseMenu()
{
	if (!IsMenuInput()) MenuManager->OpenPauseMenu();
	else if (MenuManager->GetIsPopup()) MenuManager->ClosePopup(); 
	else if (MenuManager->GetIsPauseMenu()) MenuManager->ClosePauseMenu();
}

void APRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FVector2D InitialCursorPos = FVector2D(.0f, .0f);
	const ULocalPlayer* LP = Cast<ULocalPlayer>(Player);
	if (LP)
	{
		UGameViewportClient* GVC = LP->ViewportClient;
		if (GVC)
		{
			//GVC->SetMouseCaptureMode(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
			GVC->SetMouseCaptureMode(EMouseCaptureMode::NoCapture);
			GVC->SetMouseLockMode(EMouseLockMode::LockAlways);
			FViewport* VP = GVC->Viewport;
			if (VP)
			{
				//VP->CaptureMouse(true);
				VP->CaptureMouse(false);

				FVector2D Viewportsize;
				GVC->GetViewportSize(Viewportsize);

				InitialCursorPos = FVector2D(Viewportsize.X * 0.5f, Viewportsize.Y * 0.5f);
				VP->SetMouse(static_cast<int32>(InitialCursorPos.X), static_cast<int32>(InitialCursorPos.Y));
			}
		}

		SetInputMode(FInputModeGameOnly());
		//SetShowMouseCursor(true);
		SetShowMouseCursor(false);
		// todo haus setup
		/*
		if (CursorClass)
		{
			CursorRef = CreateWidget<UREDCursorWidget_OpenLobby>(this, CursorClass, "CursorWidget");
			CursorRef->AddToViewport();
			CursorRef->SetCursorPos(InitialCursorPos);
		}
		*/
	}
}

void APRPlayerController::Menu_Select()
{
	if(!IsMenuInput()) return;
	// menu management is done in BP through widgets
}

void APRPlayerController::Right()
{
	if(IsMenuInput()) return;
	if (!IsValid(Grid)) return;
	Grid->MovementReceived(EPRMovementType::Right);
}

void APRPlayerController::Left()
{
	if(IsMenuInput()) return;
	if (!IsValid(Grid)) return;
	Grid->MovementReceived(EPRMovementType::Left);
}

void APRPlayerController::Up()
{
	if (IsMenuInput()) return;
	if (!IsValid(Grid)) return;
	Grid->MovementReceived(EPRMovementType::Up);
}

void APRPlayerController::Down()
{
	if (IsMenuInput()) return;
	if (!IsValid(Grid)) return;
	Grid->MovementReceived(EPRMovementType::Down);
}

void APRPlayerController::Menu_Right()
{
	if(!IsMenuInput()) return;
	// menu management is done in BP through widgets
}

void APRPlayerController::Menu_Left()
{
	if(!IsMenuInput()) return;
	// menu management is done in BP through widgets
}

void APRPlayerController::Menu_Up()
{
	if(!IsMenuInput()) return;
	// menu management is done in BP through widgets
}

void APRPlayerController::Menu_Down()
{
	if(!IsMenuInput()) return;
	// menu management is done in BP through widgets
}

void APRPlayerController::LevelStatusChanged()
{
	// todo remove this?
	/*
	const FInputModeGameAndUI GameMode;
	SetShowMouseCursor(true);
	SetInputMode(GameMode);
	*/
}

bool APRPlayerController::IsMenuInput() const
{
	return IsValid(MenuManager) && MenuManager->GetIsMenuOpen();
}

// todo haus setup
/*
void APRPlayerController::MoveCursor(const FInputActionValue& Value)
{
	if (!CanMoveCursor()) return;

	const FVector2D MoveVector = Value.Get<FVector2D>();
	if (FMath::Abs(MoveVector.X) <= CURSORTHRESHOLD && FMath::Abs(MoveVector.Y) <= CURSORTHRESHOLD) return;

	MoveCursor_Common(MoveVector, CursorSpeedMux);
}

void APRPlayerController::MoveMouse(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	if (FMath::Abs(MoveVector.X) <= MOUSEMODETHRESHOLD && FMath::Abs(MoveVector.Y) <= MOUSEMODETHRESHOLD) return;

	SwitchControllerMode(EOpenLobbyControllerMode::MouseMode);
	MoveCursor_Common(MoveVector, MouseSpeedMux);
}

void APRPlayerController::MoveCursor_Common(FVector2D MoveVector, FVector2D SpeedMux)
{
	const ULocalPlayer* LP = Cast<ULocalPlayer>(Player);
	if (!LP) return;
	UGameViewportClient* GVC = LP->ViewportClient;
	if (!GVC) return;
	FViewport* VP = GVC->Viewport;
	if (!VP) return;

	FVector2D Viewportsize;
	GVC->GetViewportSize(Viewportsize);
	FVector2D NewPos;
	GVC->GetMousePosition(NewPos);
	FVector2D CursorSize;
	if (IsValid(CursorRef)) CursorSize = CursorRef->GetCursorSize();

	NewPos.X = FMath::Clamp(NewPos.X + (MoveVector.X * SpeedMux.X), .01f, Viewportsize.X - (.01f + CursorSize.X));
	NewPos.Y = FMath::Clamp(NewPos.Y + (MoveVector.Y * SpeedMux.Y), .01f, Viewportsize.Y - (.01f + CursorSize.Y));

	// set unreal's internal mouse position (for interactions and other events)
	VP->SetMouse(NewPos.X, NewPos.Y);
	// set visual cursor position
	if (IsValid(CursorRef)) CursorRef->SetCursorPos(NewPos);

	// debug
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, .07f, FColor::Cyan, "NEW CURSOR LOC: " + NewPos.ToString());
}
*/