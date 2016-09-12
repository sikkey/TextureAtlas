# TextureAtlas

a project for Unreal4 & TexturePacker User

## Features

1. Load TexturePacker text|json file
2. use the uv data at runtime. You can dynamic draw them in 3D Procedural Mesh. Or other feature~

## How to use

insert the file to your ue4
rename the include filename which marked "YourProject"

## TEST
test on 4.11, all fine

## TODO

maybe I will release a version as Unreal Plugin.

## update 2016.9
make it as an unreal module.
You can setup in *.uproject :
"Modules": [
		{
			"Name": "YourProjectName",
			"Type": "Runtime",
			"LoadingPhase": "Default",
		},
		{
			"Name": "TextureAtlasSystem",
			"Type": "Runtime",
			"LoadingPhase": "Default",
			"AdditionalDependencies": [
				"CoreUObject",
				"Engine"
			]
		}
	]
}

## License

GPL