// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FalloutGuys_Clone_UE : ModuleRules
{
	public FalloutGuys_Clone_UE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"FalloutGuys_Clone_UE",
			"FalloutGuys_Clone_UE/Variant_Platforming",
			"FalloutGuys_Clone_UE/Variant_Combat",
			"FalloutGuys_Clone_UE/Variant_Combat/AI",
			"FalloutGuys_Clone_UE/Variant_SideScrolling",
			"FalloutGuys_Clone_UE/Variant_SideScrolling/Gameplay",
			"FalloutGuys_Clone_UE/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
