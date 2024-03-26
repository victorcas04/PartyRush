#pragma once
#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "PRPlayerController.generated.h"

class APRGrid;
class APRMenuManager;
class UInputMappingContext;

UCLASS()
class PARTYRUSH_API APRPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	UInputMappingContext* ControllerInputContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	UInputAction* Input;

	// todo haus setup
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cursor")
	//TSubclassOf<UPRCursorWidget> CursorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector2D CursorSpeedMux{ FVector2D(20.0f, 20.0f) };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector2D MouseSpeedMux{ FVector2D(10.0f, 10.0f) };

	UFUNCTION()
	void Init(APRGrid* Map, APRMenuManager* NewMenuManager);

	UFUNCTION(BlueprintCallable)
	void PauseMenu();
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

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
	void InputFunction(const FInputActionValue& Value);

	UFUNCTION()
	void LevelStatusChanged();
	
	UFUNCTION()
	bool IsMenuInput() const;
	
	UPROPERTY()
	APRGrid* Grid;
	
	UPROPERTY()
	APRMenuManager* MenuManager;

	// todo haus setup
	//UPROPERTY()
	//UPRCursorWidget* CursorRef;
};
