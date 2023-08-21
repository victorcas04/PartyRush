#pragma once
#include "CoreMinimal.h"

#define CELL_SIZE 100

UENUM(BlueprintType)
enum class EPRMovementType : uint8
{
	None, 
	Up,
	Down,
	Right,
	Left,
	MAX
};

UENUM(BlueprintType)
enum class EPRCellType : uint8
{
	None, 
	Floor,
	Wall,
	Exit,
	MAX
};
