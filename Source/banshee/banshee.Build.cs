// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class banshee : ModuleRules
{
	public banshee(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
												"HeadMountedDisplay", "EnhancedInput", "GameplayTasks", "NavigationSystem" });
	}
}
