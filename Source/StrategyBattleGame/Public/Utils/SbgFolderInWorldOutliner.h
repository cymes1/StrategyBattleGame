#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SbgFolderInWorldOutliner.generated.h"

UCLASS()
class STRATEGYBATTLEGAME_API USbgFolderInWorldOutliner : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static FFolder ToFolder(const FString& FolderPath);

public:
	UFUNCTION(BlueprintCallable, Category = "SBG|FolderInWorldOutliner")
	static void CreateFolderInWorld(FString FolderPath, bool& bOutSuccess, FString& OutInfoMessage);
	
	UFUNCTION(BlueprintCallable, Category = "SBG|FolderInWorldOutliner")
	static void MoveActorIntoFolder(AActor* Actor, FString FolderPath, bool& bOutSuccess, FString& OutInfoMessage);

	UFUNCTION(BlueprintCallable, Category = "SBG|FolderInWorldOutliner")
	static TArray<FString> GetAllFoldersInFolder(FString FolderPath, bool bRecursive, bool& bOutSuccess,
		FString& OutInfoMessage);

	UFUNCTION(BlueprintCallable, Category = "SBG|FolderInWorldOutliner")
	static TArray<AActor*> GetAllActorsInFolder(FString FolderPath, bool bRecursive, bool& bOutSuccess,
		FString& OutInfoMessage);

	UFUNCTION(BlueprintCallable, Category = "SBG|FolderInWorldOutliner")
	static void DeleteFolderFromWorld(FString FolderPath, bool& bOutSuccess, FString& OutInfoMessage);
};