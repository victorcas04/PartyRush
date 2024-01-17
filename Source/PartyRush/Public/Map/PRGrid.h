#pragma once
#include "CoreMinimal.h"
#include "PRCell.h"
#include "PRCongaMember.h"
#include "Vector2DInt.h"
#include "PRGrid.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelWin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelGameOver);

UCLASS(BlueprintType)
class PARTYRUSH_API APRGrid : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	bool InitGrid(FVector2DInt NewSize, FVector2DInt NewExitPos,
		TSubclassOf<APRCell> NewFloorCellSubclass, TSubclassOf<APRCell> NewWallCellSubclass, TSubclassOf<APRCell> NewExitCellSubclass);
	
	UFUNCTION()
	APRCell* GetCellFromPos(FVector2DInt Pos);

	UFUNCTION()
	TArray<APRCell*> GetAllCellsOfType(EPRCellType Type);

	UFUNCTION()
	EPRCellType GetCellType(FVector2DInt Pos);

	UFUNCTION()
	static int32 GetCellSize() { return APRCell::Cell_GetSize(); } 
	
	UFUNCTION()
	APRCongaMember* GetMemberFromPos(FVector2DInt Pos);

	UFUNCTION()
	void AssignMemberToCell(APRCell* Cell, APRCongaMember* NewMember = nullptr);

	UFUNCTION()
	void SelectCurrentMemberOnCell();

	UFUNCTION()
	void MovementReceived(EPRMovementType Direction);
	
	UFUNCTION()
	bool IsCellEmpty(FVector2DInt Pos);

	UFUNCTION()
	bool IsValidExitPos() const { return ExitPos != FVector2DInt(); }
	
	UFUNCTION()
	void AddCellToGrid(APRCell* NewCell);

	UFUNCTION()
	void CellMemberChangedLocation(APRCongaMember* NewCongaMember, FVector2DInt NewCoord, FVector2DInt OldCoord, bool bClearPreviousCellOnMove);

	FOnLevelGameOver OnLevelGameOver;
	FOnLevelWin OnLevelWin;
	
private:
	UPROPERTY()
	FVector2DInt CursorCoord;

	UPROPERTY()
	bool bIsMemberSelected {false};
	
	UPROPERTY()
	FVector2DInt RealSize;

	UPROPERTY()
	FVector2DInt ExitPos;

	UPROPERTY()
	TArray<APRCell*> Cells;

	// returns False if we need to deselect current conga. Returns True if we can maintain current conga selected.
	UFUNCTION()
	void ManageCollision(FVector2DInt NewPos);
	
	UFUNCTION()
    bool SetRealSize(FVector2DInt NewSize);
  
    UFUNCTION()
    bool SetRealExitPos(FVector2DInt NewExitPos);

	UFUNCTION()
	void SpawnCell(FVector2DInt Coord, EPRCellType CellType, TSubclassOf<APRCell> CellSubclass);
	
    UFUNCTION()
    int32 GetRealPos(FVector2DInt Pos) const;

	UFUNCTION()
	EPRCellType GetCellTypeByPos_Internal(FVector2DInt Coord);
};
