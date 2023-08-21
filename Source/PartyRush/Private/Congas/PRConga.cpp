#include "PRConga.h"
#include "PRCongaMember.h"

bool APRConga::InitConga(TArray<FVector2DInt> NewCongaMembersPositions,
	TSubclassOf<APRCongaMember> NewCongaMemberSubclass, int32 NewCongaIdx, bool bPlayer/* = false*/)
{
	if(!IsValid(NewCongaMemberSubclass)) return false;
	CongaMemberSubclass = NewCongaMemberSubclass;

	CongaIdx = NewCongaIdx;
	
	// create and init conga members
	for(int32 i = 0; i < NewCongaMembersPositions.Num() ; ++i)
	{
		SpawnCongaMember(NewCongaMembersPositions[i], i, bPlayer);
	}
	return true;
}

void APRConga::FinishAddingMemberToConga(APRCongaMember* NewCongaMember)
{
	NewCongaMember->CongaMemberUpdateLocation_Delegate.AddDynamic(this, &APRConga::CongaMemberChangedLocation);
	NewCongaMember->SetCongaOwner(this);

#if WITH_EDITOR
	NewCongaMember->SetFolderPath("Conga_"+CongaIdx);
#endif
}

void APRConga::AddNewMembers(TArray<APRCongaMember*> NewMembers, const APRCongaMember* CurrentMember, const APRCongaMember* OtherMember)
{
	TArray<APRCongaMember*> TempMembersArray;
	
	// CurrentMember cannot be the new head or tail of the new conga
	if(Members[0] == CurrentMember)
	{
		for(int32 i = Members.Num() - 1; i >= 0; --i)
		{
			FinishAddingMemberToConga(Members[i]);
			TempMembersArray.Add(Members[i]);
		}
	}
	else
	{
		for(int32 i = 0; i < Members.Num(); ++i)
		{
			FinishAddingMemberToConga(Members[i]);
			TempMembersArray.Add(Members[i]);
		}
	}

	// OtherMember cannot be the new head or tail of the new conga
	if(NewMembers[0] == OtherMember)
	{
		for(int32 i = 0; i < NewMembers.Num(); ++i)
		{
			FinishAddingMemberToConga(NewMembers[i]);
			TempMembersArray.Add(NewMembers[i]);
		}
	}
	else
	{
		for(int32 i = NewMembers.Num() - 1; i >= 0; --i)
		{
			FinishAddingMemberToConga(NewMembers[i]);
			TempMembersArray.Add(NewMembers[i]);
		}
	}

	Members.Empty();
	for(APRCongaMember* Member : TempMembersArray)
	{
		AddCongaMemberToConga(Member);
	}
}

void APRConga::SpawnCongaMember(FVector2DInt Coord, int32 NewCongaMemberIdx, bool bPlayer/* = false*/)
{
	if(!IsValid(CongaMemberSubclass)) return;

	// create and init conga member
	const FName NewCongaMemberName = FName(*FString("Conga_"+FString::FromInt(CongaIdx)+"-"+FString::FromInt(NewCongaMemberIdx)));;
	FActorSpawnParameters SpawnParams{};
	SpawnParams.Owner = this;
	SpawnParams.Name = NewCongaMemberName;

	APRCongaMember* NewCongaMember = GetWorld()->SpawnActor<APRCongaMember>(CongaMemberSubclass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if(!IsValid(NewCongaMember)) return;

	//  this will be called again when merged with another conga
	FinishAddingMemberToConga(NewCongaMember);
	AddCongaMemberToConga(NewCongaMember);
	
	//  this will NOT be called again when merged with another conga
#if WITH_EDITOR
	NewCongaMember->SetActorLabel(NewCongaMemberName.ToString());
#endif
	NewCongaMember->SetLocationByCoord(Coord);
	NewCongaMember->SetCongaMemberSize();
	NewCongaMember->SetIsPlayer(bPlayer);
	NewCongaMember->SetCongaMemberColor();
	NewCongaMember->MoveFeedback(0);
}

APRCongaMember* APRConga::GetMemberFromPos(const int32 Pos)
{
	return Members[Pos];
}

bool APRConga::IsCongaMemberHeadOrTail(const APRCongaMember* CongaMember) const
{
	return Members[0] == CongaMember || Members[Members.Num() - 1] == CongaMember;
}

void APRConga::SetSelected(const APRCongaMember* CellMember, bool bSelected)
{
	for(APRCongaMember* Member : Members)
	{
		Member->SetSelected(bSelected, Member == CellMember);
	}
}

void APRConga::SetMerged()
{
	for(int32 i = 0; i < Members.Num(); ++i)
	{
		Members[i]->MergeFeedback(i);
	}
}

void APRConga::SetMovementTypeAllowed(EPRCongaMovementType NewMovementType)
{
	MovementTypeAllowed = NewMovementType;
}

bool APRConga::CheckCanMoveInDirection(EPRMovementType Direction) const
{
	switch (MovementTypeAllowed)
	{
	case EPRCongaMovementType::HorizontalAndVertical:
		return true;
	case EPRCongaMovementType::Horizontal:
		if(Direction == EPRMovementType::Left || Direction == EPRMovementType::Right) return true;
		break;
	case EPRCongaMovementType::Vertical:
		if(Direction == EPRMovementType::Up || Direction == EPRMovementType::Down) return true;
		break;
	default:;
	}
	return false;
}

void APRConga::MoveConga(EPRMovementType Direction, FVector2DInt NewPos)
{
	MoveMembersOnConga(Direction, NewPos);
}

void APRConga::UnbindMembers()
{
	for(APRCongaMember* Member : Members)
	{
		Member->CongaMemberUpdateLocation_Delegate.RemoveDynamic(this, &APRConga::CongaMemberChangedLocation);
	}
}

void APRConga::AddCongaMemberToConga(APRCongaMember* NewCongaMember)
{
	if(!IsValid(NewCongaMember)) return;
	Members.Add(NewCongaMember);
}

void APRConga::CongaMemberChangedLocation(APRCongaMember* NewCongaMember, FVector2DInt NewCoord,  FVector2DInt OldCoord, bool bClearPreviousCellOnMove)
{
	CongaMemberChangedLocation_Delegate.Broadcast(NewCongaMember, NewCoord, OldCoord, bClearPreviousCellOnMove);
}

void APRConga::MoveMembersOnConga(EPRMovementType Direction, FVector2DInt NewPos)
{
	// in case of congas with only 1 member (like player), we enter this IF statement
	if(Members.Num() == 1)
	{
		Members[0]->MoveLeader(NewPos);
		Members[0]->MoveFeedback(0);
		return;
	}
	
	// in case the member selected is the first one in the array
	if(Members[0]->IsLead())
	{
		for(int32 i = Members.Num() - 1; i > 0; --i)
		{
			// the last element on the conga will leave an empty cell
			Members[i]->SetClearPreviousCellOnMove(i == Members.Num() - 1);
			Members[i]->MoveNonLeader(Members[i - 1]);
		}
		Members[0]->MoveLeader(NewPos);
	}
	
	// in case the member selected is the last one in the array
	if(Members[Members.Num() - 1]->IsLead())
	{
		for(int32 i = 0; i < Members.Num() - 1; ++i)
		{
			// the last element on the conga will leave an empty cell
			Members[i]->SetClearPreviousCellOnMove(i == 0);
			Members[i]->MoveNonLeader(Members[i + 1]);
		}
		Members[Members.Num() - 1]->MoveLeader(NewPos);
		
	}

	// update feedback for all the members that moved
	for(int32 i = 0; i < Members.Num(); ++i)
    {
     	Members[i]->MoveFeedback(i);
    }
}
