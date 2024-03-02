﻿#include "PRMenuManager.h"
#include "Menu/PRBaseMenuWidget.h"

void APRMenuManager::Init(TSubclassOf<UPRBaseMenuWidget> InitMenuClass)
{
	if(!IsValid(InitMenuClass)) return;

	UPRBaseMenuWidget* InitMenu = CreateWidget<UPRBaseMenuWidget>(GetWorld(), InitMenuClass);
	if(IsValid(InitMenu))
	{
		InitMenu->SetManager(this);
		InitMenu->CustomAddToViewport();
		bIsPauseMenu = InitMenu->GetIsPauseMenu();
		bIsMenuOpen = true;
	}
}

void APRMenuManager::SetIsMenuOpen(bool bNewIsMenuOpen, bool bIsNewPauseMenu/* = bIsNewPauseMenu*/)
{
	bIsMenuOpen = bNewIsMenuOpen;
	bIsPauseMenu = bIsNewPauseMenu;
}

bool APRMenuManager::OpenPauseMenu()
{
	if(!IsValid(PauseMenuClass)) return false;
	PauseMenuRef = CreateWidget<UPRBaseMenuWidget>(GetWorld(), PauseMenuClass);
	if(!IsValid(PauseMenuRef)) return false;
	PauseMenuRef->SetManager(this);
	PauseMenuRef->CustomAddToViewport();
	SetIsMenuOpen(true, true);
	return true;
}

bool APRMenuManager::ClosePauseMenu()
{
	if(!IsValid(PauseMenuRef)) return false;
	PauseMenuRef->RemoveFromParent();
	SetIsMenuOpen(false, false);
	return true;
}

void APRMenuManager::LevelWin()
{
	if(!IsValid(WinScreenClass)) return;
	UPRBaseMenuWidget* WinScreen = CreateWidget<UPRBaseMenuWidget>(GetWorld(), WinScreenClass);
	LevelCommon(WinScreen);
}

void APRMenuManager::LevelGameOver()
{
	if(!IsValid(GameOverScreenClass)) return;
	UPRBaseMenuWidget* GameOverScreen = CreateWidget<UPRBaseMenuWidget>(GetWorld(), GameOverScreenClass);
	LevelCommon(GameOverScreen);
}

void APRMenuManager::LevelCommon(UPRBaseMenuWidget* Screen)
{
	if (!IsValid(Screen)) return;
	Screen->SetManager(this);
	Screen->CustomAddToViewport();
	SetIsMenuOpen(true, false);
	OnLevelStatusChanged.Broadcast();
}
