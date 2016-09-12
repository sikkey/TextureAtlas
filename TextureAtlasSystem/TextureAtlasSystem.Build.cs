// Copyright 2013-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TextureAtlasSystem : ModuleRules
{
	public TextureAtlasSystem(TargetInfo Target)
	{
                PublicIncludePaths.AddRange(
                        new string[] {
                                //"VoxelEngine/NMath/Public",
				// ... add public include paths required here ...
			}
                        );


                PrivateIncludePaths.AddRange(
                        new string[] {
                               // "VoxelEngine/NMath/Private",
				// ... add other private include paths required here ...
			}
                        );

                PublicDependencyModuleNames.AddRange(new string[] {
                        "Core",
                        "CoreUObject",
                        "Engine",
                        "Json",
                        "JsonUtilities"
                });

                MinFilesUsingPrecompiledHeaderOverride = 1;
                bFasterWithoutUnity = true;
        }
}
