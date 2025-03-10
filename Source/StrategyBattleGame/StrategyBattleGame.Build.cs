// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StrategyBattleGame : ModuleRules
{
	public StrategyBattleGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
		]);

		PrivateDependencyModuleNames.AddRange([]);
		
		if (Target.bBuildEditor)
        {
			PrivateDependencyModuleNames.AddRange([
				"UnrealEd",
			]);
        }

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
		


// [CoreRedirects]
// +FunctionRedirects=(OldName="/Script/StrategyBattleGame.SbgFolderInWorldOutliner.GetAllActorsInWorldFolder",NewName="/Script/StrategyBattleGame.SbgFolderInWorldOutliner.GetAllActorsInFolder")
// +FunctionRedirects=(OldName="/Script/StrategyBattleGame.SbgFolderInWorldOutliner.MoveActorIntoWorldFolder",NewName="/Script/StrategyBattleGame.SbgFolderInWorldOutliner.MoveActorIntoFolder")
// +FunctionRedirects=(OldName="/Script/StrategyBattleGame.SbgFolderInWorldOutliner.GetAllFoldersUnderFolder",NewName="/Script/StrategyBattleGame.SbgFolderInWorldOutliner.GetAllFoldersInFolder")
	}
}
