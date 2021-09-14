class FalconAuthenticator
{
    static void verifyAdminPanel() {
		GetRPCManager().SendRPC( "FalconTools", "OpenMenuS", new Param1< string >("") );
	}
	
	static void verifyFreeCam() {
		GetRPCManager().SendRPC( "FalconTools", "ToggleFreecamS", new Param1< string >("") );
	}
	
	static void verifyTpToPos() {
		vector from = GetGame().GetCurrentCameraPosition();
		vector to = from + (GetGame().GetCurrentCameraDirection() * 9999);
		vector contact_pos;
				
		//Works with 3rd person view
		//DayZPhysics.RaycastRV( from, to, contact_pos, NULL, NULL, NULL , NULL, NULL, false, false, ObjIntersectIFire);
		
		//Works with 1st person view
		 DayZPhysics.RaycastRV( from, to, contact_pos, NULL, NULL, NULL, NULL, GetGame().GetPlayer(), false, false, ObjIntersectView, 0.0 );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player.getAreBindsOn())
		{
			GetRPCManager().SendRPC( "FalconTools", "tpToPosS", new Param1<vector>(contact_pos) );
		}
	}
	
	static void verifyDeleteObject() {
		vector from = GetGame().GetCurrentCameraPosition();
		vector to = from + (GetGame().GetCurrentCameraDirection() * 9999);
		vector contact_pos;
		set<Object> results = new set<Object>;
			
		//Works with 3rd person view	
		//DayZPhysics.RaycastRV( from, to, contact_pos, NULL, NULL, results, NULL, NULL, false, false, ObjIntersectIFire);
		
		//Works with 1st person view
		DayZPhysics.RaycastRV( from, to, contact_pos, NULL, NULL, results, NULL, GetGame().GetPlayer(), false, false, ObjIntersectView, 0.0 );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player.getAreBindsOn())
		{
			if (!results[0].IsInherited(SurvivorBase))
			{
				GetRPCManager().SendRPC("FalconTools", "deleteObjectS", new Param1<Object>(results[0]));
			}
		}
	}
}