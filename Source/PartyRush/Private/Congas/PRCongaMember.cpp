#include "PRCongaMember.h"
#include "PRConga.h"

void APRCongaMember::SetIsPlayer(bool bNewIsPlayer)
{
	bIsPlayer = bNewIsPlayer;
}

void APRCongaMember::SetLocationByCoord(FVector2DInt NewCoord)
{
	const FVector2DInt OldCoord = CurrCoord;
	
	const FVector2DInt Loc2D = NewCoord * CongaMember_GetSize();
	const float LocX = Loc2D.X - CongaMember_GetSize() - (Loc2D.X * 2);
	const FVector Loc3D {LocX, (float)Loc2D.Y, ZPos};
	SetActorLocation(Loc3D);
	AdjustZPos();
	
	CurrCoord = NewCoord;
	CongaMemberUpdateLocation_Delegate.Broadcast(this, NewCoord, OldCoord, bClearPreviousCellOnMove);
}

void APRCongaMember::SetSelected(bool bSelected, bool bNewIsLead/* = false*/)
{
	bIsLead = bSelected && bNewIsLead;
	BP_SetCongaMemberSelected(bSelected, bNewIsLead);
}

bool APRCongaMember::IsHeadOrTail() const
{
	return CongaOwner->IsCongaMemberHeadOrTail(this);
}

void APRCongaMember::SetCongaOwner(APRConga* Conga)
{
	CongaOwner = Conga;
}

void APRCongaMember::MoveLeader(FVector2DInt NewPos)
{
	SetLocationByCoord(NewPos);
}

void APRCongaMember::MoveNonLeader(const APRCongaMember* PreviousMember)
{
	SetLocationByCoord(PreviousMember->GetCurrentCoord());
}

FLinearColor APRCongaMember::GetColorByDirection()
{
	if(IsPlayer()) return MainColor;
	switch (GetCongaOwner()->GetMovementTypeAllowed())
	{
	case EPRCongaMovementType::Horizontal:
		return ColorHorizontal;
	case EPRCongaMovementType::Vertical:
		return ColorVertical;
	case EPRCongaMovementType::HorizontalAndVertical:
		return ColorHorizontalAndVertical;
	case EPRCongaMovementType::None:
		return ColorNone;
	default:
		return MainColor;
	}
}
