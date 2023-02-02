// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StillTheyAlive : ModuleRules
{
	public StillTheyAlive(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PublicIncludePaths.Add(ModuleDirectory); //포함디렉토리
	}
}
