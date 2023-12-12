// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Study : ModuleRules
{
	public Study(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // 추가한 목록 : "UMG", "NavigationSystem","AIModule","GameplayTasks"
        // UMG 를 추가해야 UI를 사용 가능
        // NavigationSystem, AIModule 를 추가하면 내비와 AI 사용 가능
        // GameplayTasks 를 추가하면 비헤이비어 트리를 사용 가능
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "NavigationSystem","AIModule","GameplayTasks"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
