// Fill out your copyright notice in the Description page of Project Settings.

#include "PRButton.h"

void UPRButton::CallOnHover()
{
	SlateHandleHovered();
}

void UPRButton::CallOnUnhover()
{
	SlateHandleUnhovered();
}

void UPRButton::CallOnPressed()
{
	SlateHandlePressed();
}

void UPRButton::CallOnReleased()
{
	SlateHandleReleased();
}
