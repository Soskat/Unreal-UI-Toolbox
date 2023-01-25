using UnrealBuildTool;

public class CoreUIArchitecture : ModuleRules
{
	public CoreUIArchitecture(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"GameplayTags",
			}
		);
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
				"CommonInput",
				"CommonUI",
				"EnhancedInput",
				"DebuggingUtils"
			}
		);
	}
}