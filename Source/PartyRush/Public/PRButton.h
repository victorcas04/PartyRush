// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/Button.h"
#include "PRButton.generated.h"

/**
 * 
 */
UCLASS()
class PARTYRUSH_API UPRButton : public UButton
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CallOnHover();

	UFUNCTION(BlueprintCallable)
	void CallOnUnhover();

	UFUNCTION(BlueprintCallable)
	void CallOnPressed();

	UFUNCTION(BlueprintCallable)
	void CallOnReleased();
};
