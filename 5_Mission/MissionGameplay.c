//DeveloperFreeCamera throws NULL pointer to instance

modded class MissionGameplay {
		
	ref FalconAuthenticator auth;
	ref FalconToolsV2 FalconToolsv2;
	ref FalconMonitor AdminMonitor;
	ref PlayerMonitor PlayerMonit;
	ref PlayerMonitorBack MonitorBack;

	private PlayerBase player;
	private bool isFreeCamActive = false;
	
	void MissionGameplay() {
		auth = new ref FalconAuthenticator();
		FalconToolsv2 = new ref FalconToolsV2();
		MonitorBack = new ref PlayerMonitorBack();
		
		GetRPCManager().AddRPC( "Falcon", "OpenMenuC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "ToggleFreecamC", this, SingeplayerExecutionType.Server );
	}

	override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
		
		if (key == KeyCode.KC_ADD) {
			auth.verifyFreeCam(PlayerBase.Cast(GetGame().GetPlayer()).GetIdentity().ToString());
		}
		
		else if (key == KeyCode.KC_NUMLOCK) {
			auth.verifyAdminPanel(PlayerBase.Cast(GetGame().GetPlayer()).GetIdentity().ToString());
        }
		
		else if (key == KeyCode.KC_T) {
			vector from = GetGame().GetCurrentCameraPosition();
			vector to = from + (GetGame().GetCurrentCameraDirection() * 9999);
			vector contact_pos;
					
			DayZPhysics.RaycastRV( from, to, contact_pos, NULL, NULL, NULL , NULL, NULL, false, false, ObjIntersectIFire);
			
			FalconToolsv2.tpToPos(contact_pos);
		}
		
		else if (key == KeyCode.KC_M) {
			if ( PlayerMonit ) {
                	if (PlayerMonit.isMenuOpened()) {
                    	PlayerMonit.setMenuOpened(false);
                    	GetGame().GetUIManager().HideScriptedMenu(PlayerMonit);
                    	UnlockControls();
                	} else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    	GetGame().GetUIManager().ShowScriptedMenu(PlayerMonit, NULL);
                    	PlayerMonit.setMenuOpened(true);
					
                    	LockControls();
               	 	}
            } else if (GetGame().GetUIManager().GetMenu() == NULL && PlayerMonit == null) {
                LockControls();
                PlayerMonit = PlayerMonitor.Cast(GetUIManager().EnterScriptedMenu(2138598, null));
                PlayerMonit.setMenuOpened(true);
            }
		}
    }
	
	private void OpenMenuC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<bool> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				if ( AdminMonitor ) {
                	if (AdminMonitor.isMenuOpened()) {
                    	AdminMonitor.setMenuOpened(false);
                    	GetGame().GetUIManager().HideScriptedMenu(AdminMonitor);
                    	UnlockControls();
                	} else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    	GetGame().GetUIManager().ShowScriptedMenu(AdminMonitor, NULL);
                    	AdminMonitor.setMenuOpened(true);
	
						AdminMonitor.setPlayer(PlayerBase.Cast(PlayerBase.Cast(GetGame().GetPlayer())));
					
                    	LockControls();
               	 	}
            	} else if (GetGame().GetUIManager().GetMenu() == NULL && AdminMonitor == null) {
                	LockControls();
                	AdminMonitor = FalconMonitor.Cast(GetUIManager().EnterScriptedMenu(2138597, null));
                	AdminMonitor.setMenuOpened(true);
				
					AdminMonitor.setPlayer(PlayerBase.Cast(GetGame().GetPlayer()));
            	}
			}
		}
	}
	
	private void ToggleFreecamC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<bool> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				player = PlayerBase.Cast(GetGame().GetPlayer());
				
				HumanInputController hic = player.GetInputController();
				
				if (hic) {
					
					if (isFreeCamActive) {
						isFreeCamActive = false;
					}
					else {
						isFreeCamActive = true;
					}
					
					hic.SetDisabled(isFreeCamActive);
				}
				DeveloperFreeCamera.FreeCameraToggle(player, false);
			}
		}
	}
	
	
	//To avoid strange situations when closing menu
	 private void LockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void UnlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
}