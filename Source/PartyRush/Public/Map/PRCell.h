#pragma once
#include "CoreMinimal.h"
#include "PRCellInfo.h"
#include "PRCongaMember.h"
#include "Vector2DInt.h"
#include "PRCell.generated.h"

UCLASS(BlueprintType)
class PARTYRUSH_API APRCell : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 Cell_GetSize() { return CELL_SIZE; }
	
	UFUNCTION()
	EPRCellType GetType() const { return CellType; }

	UFUNCTION()
	void SetLocationByCoord(FVector2DInt NewCoord);
	
	UFUNCTION()
	void SetCellType(EPRCellType NewCellType) { CellType = NewCellType; }

	UFUNCTION()
	void SetCellVisuals();
	
	UFUNCTION()
	void SetCellSize() { BP_SetCellSize((float)CELL_SIZE); }

	UFUNCTION()
	void SetSelected(bool bSelected) { BP_SetCellSelected(bSelected); }
	
	UFUNCTION()
	bool IsEmpty() const { return !IsValid(MemberOnCell); }

	UFUNCTION()
	APRCongaMember* GetMember() { return MemberOnCell; }

	UFUNCTION()
	void SetMember(APRCongaMember* NewMember = nullptr) { MemberOnCell = NewMember; }

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_SetCellColor(FLinearColor NewColor);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_SetCellSize(float NewSize);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_SetCellSelected(bool bSelected);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor MainColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor SecondaryColor = FLinearColor::Black;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor SelectedColor = FLinearColor::Green;
	
private:
	UFUNCTION()
	void SetCellColor(FLinearColor NewColor) { BP_SetCellColor(NewColor); }

	UPROPERTY()
	FVector2DInt Coord;
	
	UPROPERTY()
	EPRCellType CellType = EPRCellType::None;

	UPROPERTY()
	APRCongaMember* MemberOnCell;
};
