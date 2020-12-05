class CfgPatches
{
	class FalconTools
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"DZ_Data", "JM_CF_Scripts"};
	};
};

class CfgMods
{
	class FalconTools
	{
	    dir = "FalconTools";
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = "FalconTools";
	    credits = "";
	    author = "";
	    authorID = "0";
	    version = "0.3";
	    extra = 0;
	    type = "mod";

	    dependencies[] = { "Game", "World", "Mission" };

		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {"FalconTools/5_Mission"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"FalconTools/4_World"};
			};
		};
	};
};