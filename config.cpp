class CfgPatches
{
	class FalconTools
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"JM_CF_Scripts", "DZ_Data"};
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
	    author = "zNitche";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = {"World", "Mission" };

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