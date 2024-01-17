#include "PRPlayerController.h"
#include "PRGrid.h"
#include "PRMenuManager.h"

void APRPlayerController::Init(APRGrid* Map, APRMenuManager* NewMenuManager)
{
	Grid = Map;
	MenuManager = NewMenuManager;
	if(IsMenuInput())
	{
		const FInputModeGameAndUI GameMode;
		SetShowMouseCursor(true);
		SetInputMode(GameMode);
	}
	else
	{
		const FInputModeGameOnly GameMode;
		SetShowMouseCursor(false);
		SetInputMode(GameMode);
	}
	MenuManager->OnLevelStatusChanged.AddDynamic(this, &APRPlayerController::LevelStatusChanged);
}

void APRPlayerController::Select()
{
	if(IsMenuInput()) return;
	Grid->SelectCurrentMemberOnCell();
}

void APRPlayerController::PauseMenu()
{
	if(!IsMenuInput())
	{
		if(MenuManager->OpenPauseMenu())
		{
			const FInputModeGameAndUI GameMode;
			SetShowMouseCursor(true);
			SetInputMode(GameMode);
		}
	}
	else if(MenuManager->GetIsPauseMenu())
	{
		if(MenuManager->ClosePauseMenu())
		{
			const FInputModeGameOnly GameMode;
			SetShowMouseCursor(false);
			SetInputMode(GameMode);
		}
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
	Grid->MovementReceived(EPRMovementType::Right);
}

void APRPlayerController::Left()
{
	if(IsMenuInput()) return;
	Grid->MovementReceived(EPRMovementType::Left);
}

void APRPlayerController::Up()
{
	if(IsMenuInput()) return;
	Grid->MovementReceived(EPRMovementType::Up);
}

void APRPlayerController::Down()
{
	if(IsMenuInput()) return;
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
	const FInputModeGameAndUI GameMode;
	SetShowMouseCursor(true);
	SetInputMode(GameMode);
}

bool APRPlayerController::IsMenuInput() const
{
	return IsValid(MenuManager) && MenuManager->GetIsMenuOpen();
}
