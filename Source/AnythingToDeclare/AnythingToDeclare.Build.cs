// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnythingToDeclare : ModuleRules
{
	public AnythingToDeclare(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Core
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			//"GameplayAbilities",
			"GameplayTags",
			//"GameplayTasks",
			"GlobalLoader",
			"InputCore",
		});

	}
}
