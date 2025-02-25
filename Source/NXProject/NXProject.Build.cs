// NXProject.Build.cs

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class NXProject : ModuleRules
{
	public NXProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			// Initial Dependencies
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			
			//AI
			"AIModule","NavigationSystem", "GameplayTasks",
			//UI
			"UMG"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"NXProject"
		});
	}
}
