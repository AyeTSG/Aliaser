// Aliaser - /Aliaser/Source/Aliaser.Build.cs
// Copyright AyeTSG 2022-2024.

using UnrealBuildTool;

public class Aliaser : ModuleRules
{
	public Aliaser(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UnrealEd", "ContentBrowserData", "ContentBrowserAliasDataSource" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}