#include "Utils/SbgFolderInWorldOutliner.h"

#include "EditorActorFolders.h"
#include "Editor/EditorEngine.h"

FFolder USbgFolderInWorldOutliner::ToFolder(const FString& FolderPath)
{
	#if WITH_EDITOR
	if (GEditor == nullptr)
		return FFolder();

	UWorld* World = GEditor->GetEditorWorldContext().World();
	FFolder::FRootObject FolderRoot = FFolder::GetWorldRootFolder(World).GetRootObject();
	return FFolder(FolderRoot, *FolderPath);
	#else
	return FFolder();
	#endif
}

void USbgFolderInWorldOutliner::CreateFolderInWorld(FString FolderPath, bool& bOutSuccess, FString& OutInfoMessage)
{
	#if WITH_EDITOR
	if (GEditor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Create folder in world failed - GEditor is not valid '%s'"), *FolderPath);
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	FFolder FolderToCreate = ToFolder(FolderPath);
	FActorFolders::Get().CreateFolder(*World, FolderToCreate);
	World->MarkPackageDirty();
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Create folder in world succeeded - '%s'"), *FolderPath);
	#endif
}

void USbgFolderInWorldOutliner::MoveActorIntoFolder(AActor* Actor, FString FolderPath, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	#if WITH_EDITOR
	CreateFolderInWorld(FolderPath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Move actor into a folder failed - cannot create folder '%s'"), *FolderPath);
		return;
	}
	
	if (Actor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Move actor into a folder failed - actor is not valid '%s'"), *FolderPath);
		return;
	}

	Actor->SetFolderPath_Recursively(*FolderPath);
	Actor->GetWorld()->MarkPackageDirty();
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Move actor into a folder succeeded - `%s`"), *FolderPath);
	#endif
}

TArray<FString> USbgFolderInWorldOutliner::GetAllFoldersInFolder(FString FolderPath, bool bRecursive, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	#if WITH_EDITOR
	if (GEditor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Get all folders under folder failed - GEditor is not valid '%s'"), *FolderPath);
		return TArray<FString>();
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	FolderPath = ToFolder(FolderPath).ToString();
	TArray<FString> Folders;

	FActorFolders::Get().ForEachFolder(*World, [&Folders, &FolderPath, &bRecursive] (const FFolder& Folder)
	{
		if (Folder.ToString() != FolderPath
			&& Folder.ToString().Contains(FolderPath)
			&& (bRecursive || Folder.GetParent().ToString() == FolderPath))
		{
			Folders.Add(Folder.ToString());
		}
		
		return true;
	});

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Get all folders under folder succeeded - `%s`"), *FolderPath);
	return Folders;
	#else
	return TArray<FString>();
	#endif
}

TArray<AActor*> USbgFolderInWorldOutliner::GetAllActorsInFolder(FString FolderPath, bool bRecursive, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	#if WITH_EDITOR
	if (GEditor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Get all actors in folder failed - GEditor is not valid '%s'"), *FolderPath);
		return TArray<AActor*>();
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	TArray<FName> Folders = TArray<FName>({ *FolderPath });
	if (bRecursive)
	{
		Folders.Append(GetAllFoldersInFolder(FolderPath, true, bOutSuccess, OutInfoMessage));
	}

	TArray<AActor*> Actors;
	FActorFolders::Get().GetActorsFromFolders(*World, Folders, Actors);
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Get all actors in folder succeeded - '%s'"), *FolderPath);
	return Actors;
	#else
	return TArray<AActor*>();
	#endif
}

void USbgFolderInWorldOutliner::DeleteFolderFromWorld(FString FolderPath, bool& bOutSuccess, FString& OutInfoMessage)
{
	#if WITH_EDITOR
	if (GEditor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Delete folder from world failed - GEditor is not valid '%s'"), *FolderPath);
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	FFolder FolderToDelete = ToFolder(FolderPath);

	TArray<AActor*> Actors = GetAllActorsInFolder(FolderPath, true, bOutSuccess, OutInfoMessage);
	for (AActor* Actor : Actors)
	{
		FFolder OldFolder = ToFolder(Actor->GetFolderPath().ToString());
		FFolder NewFolder = ToFolder(OldFolder.ToString().Replace(
			*FolderToDelete.ToString(), *FolderToDelete.GetParent().ToString()));
		MoveActorIntoFolder(Actor, NewFolder.ToString(), bOutSuccess, OutInfoMessage);
	}

	TArray<FString> Paths = GetAllFoldersInFolder(FolderPath, true, bOutSuccess, OutInfoMessage);
	for (FString Path : Paths)
	{
		FFolder OldFolder = ToFolder(Path);
		FFolder NewFolder = ToFolder(OldFolder.ToString().Replace(
			*FolderToDelete.ToString(), *FolderToDelete.GetParent().ToString()));
		FActorFolders::Get().RenameFolderInWorld(*World, OldFolder, NewFolder);
	}

	FActorFolders::Get().DeleteFolder(*World, FolderToDelete);
	World->MarkPackageDirty();
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Delete folder from world succeeded - '%s'"), *FolderPath);
	#endif
}