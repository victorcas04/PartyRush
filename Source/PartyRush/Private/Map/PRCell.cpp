#include "PRCell.h"

void APRCell::SetLocationByCoord(FVector2DInt NewCoord)
{
	const FVector2DInt Loc2D = NewCoord * Cell_GetSize();
	const float LocX = Loc2D.X - Cell_GetSize() - (Loc2D.X * 2);
	const FVector Loc3D {LocX, (float)Loc2D.Y, .0f};
	SetActorLocation(Loc3D);
	Coord = NewCoord;
}

void APRCell::SetCellVisuals()
{
	SetCellSize();
	if(GetType() == EPRCellType::Floor)
	{
		SetCellColor((Coord.X + Coord.Y) % 2 ? MainColor : SecondaryColor);
	}
	else
	{
		SetCellColor(MainColor);
	}
}
