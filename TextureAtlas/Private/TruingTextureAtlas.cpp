// Copyright @7Mersenne All Rights Reserved.
// Email: 7Mersenne@gmail.com

//#include "YourProjectPrivatePCH.h"
#include "YourProject.h"
#include "TruingTextureAtlas.h"
#include "Json.h"
#include "FileManagerGeneric.h"

int16 TextureAtlas::GetAtlasId(const FName& name)
{
	int16* id= idConvert.Find(name);
	if (id != nullptr)
	{
		return *id;
	}

	// 0 means 0 or error
	return 0;
}

TSharedPtr<AtlasUV> TextureAtlas::GetAtlas(const FName& name)
{
	TSharedPtr<AtlasUV>* ptr = nameFinder.Find(name);
	if (ptr != nullptr)
		return *ptr;

	return nullptr;
}

TSharedPtr<AtlasUV> TextureAtlas::GetAtlas(const int16& id)
{
	if (id < idFinder.Num()){
		return idFinder[id];
	}

	return nullptr;
}

bool TextureAtlas::InitFromTxtFile(FString filename, bool isFullPath)
{
	// reset index
	nameFinder.Reset();
	nameConvert.Reset();
	idFinder.Reset();
	idConvert.Reset();

	// read json
	IFileManager& fileManager = FFileManagerGeneric::Get();
	FString filelocation(DefaultJsonDir + filename);
	if (isFullPath)
		filelocation = filename;

	checkf(fileManager.FileExists(*filelocation), TEXT("%texturepacker%.json file is not exist"));

	FString content;

	checkf(FFileHelper::LoadFileToString(content, *filelocation), TEXT(" load file %texturepacker%.json failed"));

	//UE_LOG(LogStats, Log, TEXT("[TextureAtlas] content = \n %s"), *content);

	// read json from string

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(content);
	// Deserialize the JSON data
	TSharedPtr<FJsonObject> JsonData;
	bool isDeserialized = FJsonSerializer::Deserialize(JsonReader, JsonData);

	checkf(isDeserialized && JsonData.IsValid(), TEXT(" JSON data is invalid! Input:\n'%s'"), *content);
	
	// json load success

	//TSharedPtr<FJsonObject, ESPMode::ThreadSafe> frames = JsonData->GetObjectField("frames");
	TSharedPtr<FJsonObject> frames = JsonData->GetObjectField("frames");
	TSharedPtr<FJsonObject> meta = JsonData->GetObjectField("meta");
	TSharedPtr<FJsonObject> size = meta->GetObjectField("size");

	float width = size->GetNumberField("w");
	float height = size->GetNumberField("h");

	// Iterate over Json Values
	for (auto currJsonValue = frames->Values.CreateConstIterator(); currJsonValue; ++currJsonValue)
	{
		// Get the key name
		const FString Name = (*currJsonValue).Key;

		// Get the value as a FJsonValue object
		TSharedPtr< FJsonValue > Value = (*currJsonValue).Value;

		// set uv
		const TSharedPtr<FJsonObject>& textureInfo = Value->AsObject();
		TSharedPtr<FJsonObject> frame = textureInfo->GetObjectField("frame");
		TSharedPtr<AtlasUV> uv(new AtlasUV());
		uv->x = frame->GetNumberField("x") / width;
		uv->y = frame->GetNumberField("y") / height;
		uv->w = frame->GetNumberField("w") / width;
		uv->h = frame->GetNumberField("h") / height;

		// set uv index
		FName name = FName(*Name);
		int16 id = nameConvert.Num();
		nameConvert.Add(name);
		idFinder.Add(uv);

		idConvert.Add(name, id);
		nameFinder.Add(name, uv);
	}

	return true;
}

bool TextureAtlas::InitFromJsonFile(FString filename, bool isFullPath /*= false*/)
{
	// reset index
	nameFinder.Reset();
	nameConvert.Reset();
	idFinder.Reset();
	idConvert.Reset();

	// read json
	IFileManager& fileManager = FFileManagerGeneric::Get();
	FString filelocation(DefaultJsonDir + filename);
	if (isFullPath)
		filelocation = filename;

	checkf(fileManager.FileExists(*filelocation), TEXT("%texturepacker%.json file is not exist"));

	FString content;

	checkf(FFileHelper::LoadFileToString(content, *filelocation), TEXT(" load file %texturepacker%.json failed"));

	//UE_LOG(LogStats, Log, TEXT("[TextureAtlas] content = \n %s"), *content);

	// read json from string

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(content);
	// Deserialize the JSON data
	TSharedPtr<FJsonObject> JsonData;
	bool isDeserialized = FJsonSerializer::Deserialize(JsonReader, JsonData);

	checkf(isDeserialized && JsonData.IsValid(), TEXT(" JSON data is invalid! Input:\n'%s'"), *content);

	// json load success
	const TArray<TSharedPtr<FJsonValue> >& frames = JsonData->GetArrayField("frames");
	const TSharedPtr<FJsonObject>& meta = JsonData->GetObjectField("meta");
	const TSharedPtr<FJsonObject>& size = meta->GetObjectField("size");

	float width = size->GetNumberField("w");
	float height = size->GetNumberField("h");

	// Iterate over Json Values
	for (int32 i = 0, count = frames.Num(); i < count;++i)
	{
		// set uv
		const TSharedPtr<FJsonObject>& textureInfo = frames[i]->AsObject();

		// Get the key name
		const FString Name = textureInfo->GetStringField(TEXT("filename"));

		TSharedPtr<FJsonObject> frame = textureInfo->GetObjectField("frame");
		TSharedPtr<AtlasUV> uv(new AtlasUV());
		uv->x = frame->GetNumberField("x") / width;
		uv->y = frame->GetNumberField("y") / height;
		uv->w = frame->GetNumberField("w") / width;
		uv->h = frame->GetNumberField("h") / height;

		// set uv index
		FName name = FName(*Name);
		int16 id = nameConvert.Num();
		nameConvert.Add(name);
		idFinder.Add(uv);

		idConvert.Add(name, id);
		nameFinder.Add(name, uv);
	}

	return true;
}

FString TextureAtlas::DefaultJsonDir = FPaths::GameDir() + TEXT("Common/");
