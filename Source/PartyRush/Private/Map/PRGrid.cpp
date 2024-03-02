#include "PRGrid.h"
#include "PRConga.h"
#include "PRCongasManager.h"
#include "PRGameInstance.h"

bool APRGrid::InitGrid(const FVector2DInt NewSize, const FVector2DInt NewExitPos,
                       TSubclassOf<APRCell> NewFloorCellSubclass, TSubclassOf<APRCell> NewWallCellSubclass, TSubclassOf<APRCell> NewExitCellSubclass)
{
	if(!IsValid(NewFloorCellSubclass)) return false;
	if(!SetRealSize(NewSize)) return false;
	if(!SetRealExitPos(NewExitPos)) return false;

	// create and init cells
	for(int32 i = 0; i < NewSize.X + 2; ++i)
	{
		for(int32 j = 0; j < NewSize.Y + 2; ++j)
		{
			switch (const EPRCellType CellType = GetCellTypeByPos_Internal(FVector2DInt(i, j)))
			{
			case EPRCellType::Floor:
				SpawnCell(FVector2DInt(i, j), CellType, NewFloorCellSubclass);
				break;
			case EPRCellType::Wall:
				SpawnCell(FVector2DInt(i, j), CellType, NewWallCellSubclass);
				break;
			case EPRCellType::Exit:
				SpawnCell(FVector2DInt(i, j), CellType, NewExitCellSubclass);
				break;
			default: ;
			}
		}
	}
	return true;
}

void APRGrid::SpawnCell(FVector2DInt Coord, EPRCellType CellType, TSubclassOf<APRCell> CellSubclass)
{
	if(!IsValid(CellSubclass)) return;
	
	// create and init cell
	const FName NewCellName = FName(*FString("Cell_"+FString::FromInt(Coord.X)+"x"+FString::FromInt(Coord.Y)));;
	FActorSpawnParameters SpawnParams{};
	SpawnParams.Owner = this;
	SpawnParams.Name = NewCellName;
		
	APRCell* NewCell = GetWorld()->SpawnActor<APRCell>(CellSubclass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if(!IsValid(NewCell)) return;
#if WITH_EDITOR
	NewCell->SetActorLabel(NewCellName.ToString());
#endif
	NewCell->SetCellType(CellType);
	NewCell->SetLocationByCoord(Coord);
	NewCell->SetCellVisuals();
	AddCellToGrid(NewCell);

	if(NewCell->GetType() == EPRCellType::Exit)
	{
		CursorCoord = Coord;
		NewCell->SetSelected(true);
	}

#if WITH_EDITOR
	NewCell->SetFolderPath("Cells");
#endif
}

APRCell* APRGrid::GetCellFromPos(const FVector2DInt Pos)
{
	const int32 RealPos = GetRealPos(Pos);
	if(!Cells.IsValidIndex(RealPos)) return nullptr;
	return Cells[RealPos];
}

TArray<APRCell*> APRGrid::GetAllCellsOfType(const EPRCellType Type)
{
	TArray<APRCell*> FoundCells;
	for(auto Cell : Cells)
	{
		if(Cell->GetType() == Type)
		{
			FoundCells.Add(Cell);
		}
	}
	return FoundCells;
}

EPRCellType APRGrid::GetCellType(const FVector2DInt Pos)
{
	return Cells[GetRealPos(Pos)]->GetType();
}

APRCongaMember* APRGrid::GetMemberFromPos(const FVector2DInt Pos)
{
	return Cells[GetRealPos(Pos)]->GetMember();
}

void APRGrid::AssignMemberToCell(APRCell* Cell, APRCongaMember* NewMember/* = nullptr*/)
{
	if(!IsValid(Cell)) return;
	Cell->SetMember(NewMember);
}

void APRGrid::SelectCurrentMemberOnCell()
{
	APRCell* CurrentCell = GetCellFromPos(CursorCoord);
	if(bIsMemberSelected)
	{
		if(APRCongaMember* CellMember = CurrentCell->GetMember())
		{
			CellMember->GetCongaOwner()->SetSelected(CellMember, false);
		}
		CurrentCell->SetSelected(true);
		bIsMemberSelected = false;
	}
	else
	{
		if(!CurrentCell->IsEmpty())
		{
			APRCongaMember* CellMember = CurrentCell->GetMember();
			if(CellMember->IsHeadOrTail())
			{
				CurrentCell->SetSelected(false);
				CellMember->GetCongaOwner()->SetSelected(CellMember, true);
				bIsMemberSelected = true;
			}
		}
	}
}

void APRGrid::MovementReceived(EPRMovementType Direction)
{
	FVector2DInt NewPos = CursorCoord;
	switch (Direction)
	{
	case EPRMovementType::Up:
		--NewPos.X;
		break;
	case EPRMovementType::Down:
		++NewPos.X;
		break;
	case EPRMovementType::Right:
		++NewPos.Y;
		break;
	case EPRMovementType::Left:
		--NewPos.Y;
		break;
	default: return;
	}
	
	if(NewPos == CursorCoord)
	{
		// not a new position
		return;
	}

	APRCell* NewCell = GetCellFromPos(NewPos);
	if(!IsValid(NewCell)) return;
	
	if(bIsMemberSelected)
	{
		if(NewCell->GetType() == EPRCellType::Wall)
		{
			// stop at wall
			return;
		}

		if(APRCongaMember* CellMember = GetMemberFromPos(CursorCoord))
		{
			if(!CellMember->GetCongaOwner()->CheckCanMoveInDirection(Direction)) return;
			if(NewCell->GetType() == EPRCellType::Exit && !CellMember->IsPlayer())
			{
				// congas cannot go into the exit zone
				return;
			}
			
			if(!NewCell->IsEmpty())
            {
            	ManageCollision(NewPos);
            	return;
            }
			
			CellMember->GetCongaOwner()->MoveConga(Direction, NewPos);
			if(NewCell->GetType() == EPRCellType::Exit && CellMember->IsPlayer())
			{
				if (IsValid(GI))
				{
					GI->TriggerWin();
				}
			}
			CursorCoord = NewPos;
		}
	}
	else
	{
		GetCellFromPos(CursorCoord)->SetSelected(false);
		NewCell->SetSelected(true);
		CursorCoord = NewPos;
	}
}

bool APRGrid::IsCellEmpty(const FVector2DInt Pos)
{
	return Cells[GetRealPos(Pos)]->IsEmpty();
}

void APRGrid::AddCellToGrid(APRCell* NewCell)
{
	if(!IsValid(NewCell)) return;
	Cells.Add(NewCell);
}

void APRGrid::CellMemberChangedLocation(APRCongaMember* NewCongaMember, FVector2DInt NewCoord, FVector2DInt OldCoord, bool bClearPreviousCellOnMove)
{
	if(bClearPreviousCellOnMove)
	{
		APRCell* OldCell = GetCellFromPos(OldCoord);
		AssignMemberToCell(OldCell);
	}
	APRCell* NewCell = GetCellFromPos(NewCoord);
	AssignMemberToCell(NewCell, NewCongaMember);
}

void APRGrid::SetGIRef(UPRGameInstance* NewGIRef)
{
	GI = NewGIRef;
}

void APRGrid::SetLevelName(FName NewName)
{
	LevelName = NewName;
	GI->SetCurrentLevelName(LevelName);
}

void APRGrid::ManageCollision(FVector2DInt NewPos)
{
	APRCell* CurrentCell = GetCellFromPos(CursorCoord);
	APRCongaMember* CurrentMember = CurrentCell->GetMember();
	APRCell* NewCell = GetCellFromPos(NewPos);
	APRCongaMember* NewMember = NewCell->GetMember();

	if(!IsValid(CurrentMember) || !IsValid(NewMember)) return;
	
	if(CurrentMember->IsPlayer() != NewMember->IsPlayer())
	{
		if (IsValid(GI))
		{
			GI->TriggerGameOver();
		}
	}
	else
	{
		APRCongasManager::MergeCongas(this, CurrentMember, NewMember);	
	}
}

bool APRGrid::SetRealSize(const FVector2DInt NewSize)
{
	if(NewSize.X > 0 && NewSize.Y > 0)
	{
		RealSize = FVector2DInt{NewSize.X + 2, NewSize.Y + 2};
		return true;
	}
	// error not valid size
	return false;
}

bool APRGrid::SetRealExitPos(FVector2DInt NewExitPos)
{
	// no corners allowed
	if((NewExitPos.X == 1 && NewExitPos.Y == 1) ||
		(NewExitPos.X == 1 && NewExitPos.Y == RealSize.Y - 2) ||
		(NewExitPos.X == RealSize.X - 2 && NewExitPos.Y == 1) ||
		(NewExitPos.X == RealSize.X - 2 && NewExitPos.Y == RealSize.Y - 2))
	{
		// error not valid exit position
		return false;
	}
	
	if(NewExitPos.X == 1)
	{
		ExitPos = {0, NewExitPos.Y};
	}
	else if(NewExitPos.X == RealSize.X -2)
	{
		ExitPos = {RealSize.X - 1, NewExitPos.Y};
	}
	else if(NewExitPos.Y == 1)
	{
		ExitPos = {NewExitPos.X, 0};
	}
	else if(NewExitPos.Y == RealSize.Y - 2)
	{
		ExitPos = {NewExitPos.X, RealSize.Y - 1};
	}
	else
	{
		// error not valid exit position
		return false;
	}
	return true;
}

int32 APRGrid::GetRealPos(const FVector2DInt Pos) const
{
	return (Pos.X * RealSize.Y) + Pos.Y;
}

EPRCellType APRGrid::GetCellTypeByPos_Internal(FVector2DInt Coord)
{
	if(ExitPos == Coord)
	{
		return EPRCellType::Exit;
	}
	if(Coord.X == 0 || Coord.X == RealSize.X - 1 || Coord.Y == 0 || Coord.Y == RealSize.Y - 1)
	{
		return EPRCellType::Wall;
	}
	return EPRCellType::Floor;
}
