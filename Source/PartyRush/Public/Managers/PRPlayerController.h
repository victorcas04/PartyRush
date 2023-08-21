#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PRPlayerController.generated.h"

class APRGrid;
class APRMenuManager;

UCLASS()
class PARTYRUSH_API APRPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void Init(APRGrid* Map, APRMenuManager* NewMenuManager);

	UFUNCTION(BlueprintCallable)
	void PauseMenu();
	
protected:
	/*
	 * Input redirection from BP to c++
	 */
	UFUNCTION(BlueprintCallable)
	void Select();

	UFUNCTION(BlueprintCallable)
	void Menu_Select();
	
	UFUNCTION(BlueprintCallable)
	void Right();

	UFUNCTION(BlueprintCallable)
	void Left();
	
	UFUNCTION(BlueprintCallable)
	void Up();
	
	UFUNCTION(BlueprintCallable)
	void Down();
	
	UFUNCTION(BlueprintCallable)
	void Menu_Right();
	
	UFUNCTION(BlueprintCallable)
	void Menu_Left();
	
	UFUNCTION(BlueprintCallable)
	void Menu_Up();
	
	UFUNCTION(BlueprintCallable)
	void Menu_Down();
	
private:
	UFUNCTION()
	void LevelStatusChanged();
	
	UFUNCTION()
	bool IsMenuInput() const;
	
	UPROPERTY()
	APRGrid* Grid;
	
	UPROPERTY()
	APRMenuManager* MenuManager;
};
