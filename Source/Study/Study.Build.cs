// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Study : ModuleRules
{
	public Study(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // �߰��� ��� : "UMG", "NavigationSystem","AIModule","GameplayTasks"
        // UMG �� �߰��ؾ� UI�� ��� ����
        // NavigationSystem, AIModule �� �߰��ϸ� ����� AI ��� ����
        // GameplayTasks �� �߰��ϸ� �����̺�� Ʈ���� ��� ����
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "NavigationSystem","AIModule","GameplayTasks"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
