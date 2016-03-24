// Copyright @7Mersenne All Rights Reserved.
// Email: 7Mersenne@gmail.com

#pragma once

#include "Core.h"

// import NMath Module

class VOXELPLUGIN_API AtlasUV
{
public:
	float x;
	float y;
	float w;
	float h;

	AtlasUV()
	{
		x = y = w = h = 0;
	}

	AtlasUV(float X, float Y, float W, float H)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
	}

	FVector2D TopLeft()
	{
		return FVector2D(x, y);
	}

	FVector2D TopRight()
	{
		return FVector2D(x + w, y);
	}

	FVector2D ButtomLeft()
	{
		return FVector2D(x, y + h);
	}

	FVector2D ButtomRight()
	{
		return FVector2D(x + w, y+h);
	}

	// buttom left
	static FVector2D GetTL(AtlasUV& uv)
	{
		return FVector2D(uv.x, uv.y);
	}

	static FVector2D GetTR(AtlasUV& uv)
	{
		return FVector2D(uv.x + uv.w, uv.y);
	}


	// top left
	static FVector2D GetBL(AtlasUV& uv)
	{
		return FVector2D(uv.x, uv.y + uv.h);
	}

	static FVector2D GetBR(AtlasUV& uv)
	{
		return FVector2D(uv.x + uv.w, uv.y+uv.h);
	}
};

struct MetaInfo
{
public:
	float width;
	float height;

	FVector2D size;
};

struct AtlasInfo
{
public:
	AtlasUV frame;
	MetaInfo meta;
};

class VOXELPLUGIN_API TextureAtlas
{
public:
	// finder
	TMap<FName, TSharedPtr<AtlasUV> > nameFinder;
	TArray<TSharedPtr<AtlasUV> > idFinder;

	// convert
	TMap<FName, int16> idConvert;
	TArray<FName> nameConvert;

	//TextureAtlas();
	int16 GetAtlasId(const FName& name);
	TSharedPtr<AtlasUV> GetAtlas(const FName& name);
	TSharedPtr<AtlasUV> GetAtlas(const int16& id);
	bool InitFromTxtFile(FString filename, bool isFullPath = false);
	bool InitFromJsonFile(FString filename, bool isFullPath = false);

	static FString DefaultJsonDir;
};