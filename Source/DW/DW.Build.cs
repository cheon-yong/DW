// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DW : ModuleRules
{
	public DW(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {
			"DW"
		});

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"UMG", 
			"NavigationSystem", 
			"AIModule",

			// GAS
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags"
		});
	}
}
