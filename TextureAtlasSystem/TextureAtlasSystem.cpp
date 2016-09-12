//Copyright 2013 - 2016 Truing Co.,Ltd All Rights Reserved.
#pragma once

#include "TextureAtlasSystemPrivatePCH.h"


class FTextureAtlasSystem : public ITextureAtlasSystem
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FTextureAtlasSystem, TextureAtlasSystem)



void FTextureAtlasSystem::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FTextureAtlasSystem::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

