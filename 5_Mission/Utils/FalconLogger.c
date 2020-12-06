class FalconLogger
{
	static void logAdminFileMissing() {
		GetGame().AdminLog("[FalconTools] Can't find admins list. File missing");
	}
	
	static void logAction(string playerID, string info, string type) {
		switch(type) {	
			case "adminMenu": {
				GetGame().AdminLog("[FalconTools] (" + playerID + ") Opened Admin Menu");  	
				break;
			}
			
			case "adminGM": {
				GetGame().AdminLog("[FalconTools] (" + playerID + ") GodMode");  	
				break;
			}
			
			case "adminKillPlayer": {
				GetGame().AdminLog("[FalconTools] (" + playerID + ") Killed + (" + info + ")");  	
				break;
			}
			
			case "adminSpawnedItem": {
				GetGame().AdminLog("[FalconTools] (" + playerID + ") spawned " + info + "");  	
				break;
			}
			
			case "adminTP": {
				GetGame().AdminLog("[FalconTools] (" + playerID + ") TP to " + info + "");  	
				break;
			}
			
			case "debug": {
				GetGame().AdminLog("[DEBUG] "  + info);
				break;
			}
			
			default: {
				GetGame().AdminLog("[FalconTools] (" + type + " ) (" + playerID + ") default log"); 
			}
		}
	}	
}