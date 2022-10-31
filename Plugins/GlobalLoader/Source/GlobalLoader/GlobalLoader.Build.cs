// Copyright Tom Shinton 2022 - GlobalLoader

using UnrealBuildTool;

public class GlobalLoader : ModuleRules
{
	public GlobalLoader(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
		});
	}
}
