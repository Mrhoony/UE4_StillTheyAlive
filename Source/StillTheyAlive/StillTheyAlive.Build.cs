using UnrealBuildTool;

public class StillTheyAlive : ModuleRules
{
	public StillTheyAlive(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"AIModule",
			"GameplayTasks"
		});

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
