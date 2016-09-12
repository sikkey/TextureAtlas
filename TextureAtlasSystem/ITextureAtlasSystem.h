//Copyright 2013 - 2016 Truing Co.,Ltd All Rights Reserved.
//Author:7Mersenne@ghmail.com

#pragma once

#include "ModuleManager.h"


/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules 
 * within this plugin.
 */
class ITextureAtlasSystem : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline ITextureAtlasSystem& Get()
	{
		return FModuleManager::LoadModuleChecked< ITextureAtlasSystem >("TextureAtlasSystem");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "TextureAtlasSystem" );
	}
};
