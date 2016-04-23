
#pragma once
#include "cashgenUE.h"
#include "ZoneBlockCorner.h"


enum EBiome { Wood, Grassland , Cliff, Shore, Underwater };

class ZoneBlock
{
public:
	float Height;
	float Slope;

	FColor Color;
	
	EBiome Biome;

	int MyX;
	int MyY;

	ZoneBlockCorner topLeftCorner;
	ZoneBlockCorner topRightCorner;
	ZoneBlockCorner bottomLeftCorner;
	ZoneBlockCorner bottomRightCorner;

	void ProcessCorners(const float aMaxHeight, const float aUnitSize);

	ZoneBlock(float aHeight, FColor aColor, int aX, int aY);
	ZoneBlock();
	~ZoneBlock();
	
};
