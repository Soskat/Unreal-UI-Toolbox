using UnrealBuildTool;

public class UIToolboxPreview : ModuleRules
{
	public UIToolboxPreview(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UMG",
			"InputCore",
			"EnhancedInput",
			"CommonUI",
			"GameplayTags",
			"CoreUIArchitecture",
			"DebuggingUtils"
		});
	}
}
