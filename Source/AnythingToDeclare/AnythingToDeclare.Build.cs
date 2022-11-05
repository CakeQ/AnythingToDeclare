// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

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
