#include "PRCongasManager.h"
#include "PRGrid.h"
#include "PRConga.h"
#include "PRCongaMember.h"

bool APRCongasManager::MergeCongas(APRGrid* GridRef, APRCongaMember* CurrentMember, APRCongaMember* OtherMember)
{
	APRConga* NewMergedConga = CurrentMember->GetCongaOwner();
	APRConga* OldConga = OtherMember->GetCongaOwner();
	if(NewMergedConga == OldConga) return false;
	if(!CurrentMember->IsHeadOrTail() || !OtherMember->IsHeadOrTail()) return false;
	GridRef->SelectCurrentMemberOnCell();

	// unbind conga delegates (all of them are rebinded again later)
	OldConga->UnbindMembers();
	NewMergedConga->UnbindMembers();
	// add members from old conga to new conga
	NewMergedConga->AddNewMembers(OldConga->GetAllMembers(), CurrentMember, OtherMember);
	// set result available direction
	NewMergedConga->SetMovementTypeAllowed(GetMergeMovementType(NewMergedConga->GetMovementTypeAllowed(), OldConga->GetMovementTypeAllowed()));
	// destroy old conga
	OldConga->Destroy();
	// play feedback on new conga
	NewMergedConga->SetMerged();
	
	return true;
}

EPRCongaMovementType APRCongasManager::GetMergeMovementType(EPRCongaMovementType NewCongaMovement, EPRCongaMovementType OldCongaMovement)
{
	switch (NewCongaMovement)
	{
	case EPRCongaMovementType::HorizontalAndVertical:
		return EPRCongaMovementType::HorizontalAndVertical;
	case EPRCongaMovementType::Horizontal:
		switch (OldCongaMovement)
		{
		case EPRCongaMovementType::HorizontalAndVertical:
			return EPRCongaMovementType::HorizontalAndVertical;
		case EPRCongaMovementType::Vertical:
			return EPRCongaMovementType::HorizontalAndVertical;
		default: ;
		}
		return EPRCongaMovementType::Horizontal;
	case EPRCongaMovementType::Vertical:
		switch (OldCongaMovement)
		{
		case EPRCongaMovementType::HorizontalAndVertical:
			return EPRCongaMovementType::HorizontalAndVertical;
		case EPRCongaMovementType::Horizontal:
			return EPRCongaMovementType::HorizontalAndVertical;
		default: ;
		}
		return EPRCongaMovementType::Vertical;
	case EPRCongaMovementType::None:
		return OldCongaMovement;
	default: ;
	}
	return EPRCongaMovementType::None;
}
