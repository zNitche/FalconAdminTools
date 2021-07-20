class FalconAuthenticator
{
    void FalconAuthenticator()
    {
        GetRPCManager().AddRPC( "Falcon", "OpenMenuS", this, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "Falcon", "ToggleFreecamS", this, SingeplayerExecutionType.Client );
    }

	private void OpenMenuS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				GetRPCManager().SendRPC( "Falcon", "OpenMenuC", new Param1<bool>(true), true, sender);
			}
        }
    }
	
	private void ToggleFreecamS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {				
				GetRPCManager().SendRPC( "Falcon", "ToggleFreecamC", new Param1<bool>(true), true, sender);
			}
        }
    }

    void verifyAdminPanel(string guid) {
		GetRPCManager().SendRPC( "Falcon", "OpenMenuS", new Param1< string >( guid ) );
	}
	
	void verifyFreeCam(string guid) {
		GetRPCManager().SendRPC( "Falcon", "ToggleFreecamS", new Param1< string >( guid ) );
	}
	
	void verifyTpToPos(string guid) {
		vector from = GetGame().GetCurrentCameraPosition();
		vector to = from + (GetGame().GetCurrentCameraDirection() * 9999);
		vector contact_pos;
				
		DayZPhysics.RaycastRV( from, to, contact_pos, NULL, NULL, NULL , NULL, NULL, false, false, ObjIntersectIFire);
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player.getAreBindsOn())
		{
			GetRPCManager().SendRPC( "Falcon", "tpToPosS", new Param1<vector>(contact_pos) );
		}
	}
}