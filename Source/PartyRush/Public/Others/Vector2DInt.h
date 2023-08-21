#pragma once
#include "CoreMinimal.h"
#include "Vector2DInt.generated.h"

USTRUCT(BlueprintType)
struct FVector2DInt
{
	GENERATED_BODY()

	FVector2DInt()
	{
		X = MAX_int32;
		Y = MAX_int32;
	}
	
	FVector2DInt(int32 NewX, int32 NewY)
	{
		X = NewX;
		Y = NewY;
	}
	
	UPROPERTY(EditAnywhere)
	int32 X;
	
	UPROPERTY(EditAnywhere)
	int32 Y;
	
	bool operator==(const FVector2DInt& Vector2DInt) const;
	bool operator!=(const FVector2DInt& Vector2DInt) const;
	FVector2DInt operator+(int32 INT32) const;
	FVector2DInt operator*(int32 INT32) const;
	FVector2DInt operator+(const FVector2DInt& Vector2DInt) const;
	FVector2DInt operator*(const FVector2DInt& Vector2DInt) const;
	bool IsValid() const;
};

inline bool FVector2DInt::operator==(const FVector2DInt& Vector2DInt) const
{
	return Vector2DInt.X == X && Vector2DInt.Y == Y;
}

inline bool FVector2DInt::operator!=(const FVector2DInt& Vector2DInt) const
{
	return Vector2DInt.X != X || Vector2DInt.Y != Y;
}

inline FVector2DInt FVector2DInt::operator+(int32 INT32) const
{
	return FVector2DInt(X + INT32, Y + INT32);
}

inline FVector2DInt FVector2DInt::operator*(int32 INT32) const
{
	return FVector2DInt(X * INT32, Y * INT32);
}

inline FVector2DInt FVector2DInt::operator+(const FVector2DInt& Vector2DInt) const
{
	return FVector2DInt(X + Vector2DInt.X, Y + Vector2DInt.Y);
}

inline FVector2DInt FVector2DInt::operator*(const FVector2DInt& Vector2DInt) const
{
	return FVector2DInt(X * Vector2DInt.X, Y * Vector2DInt.Y);
}

inline bool FVector2DInt::IsValid() const
{
	return X != MAX_int32 || Y != MAX_int32;
}
