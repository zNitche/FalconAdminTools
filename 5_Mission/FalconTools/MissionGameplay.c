//DeveloperFreeCamera throws NULL pointer to instance

modded class MissionGameplay {
		
	ref FalconAuthenticator auth;
	ref FalconToolsV2 FalconToolsv2;
	ref FalconMonitor AdminMonitor;

	private PlayerBase player;
	private bool isFreeCamActive = false;
	
	void MissionGameplay() {
		auth = new ref FalconAuthenticator();
		FalconToolsv2 = new ref FalconToolsV2();
		
		GetRPCManager().AddRPC( "FalconTools", "OpenMenuC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "ToggleFreecamC", this, SingeplayerExecutionType.Server );
	}

	override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
		
		if (key == KeyCode.KC_ADD) {
			auth.verifyFreeCam(PlayerBase.Cast(GetGame().GetPlayer()).GetIdentity().ToString());
		}
		
		else if (key == KeyCode.KC_NUMLOCK || key == KeyCode.KC_ESCAPE) {
			if (AdminMonitor)
			{
				if (AdminMonitor.isMenuOpened())
				{
					closeAdminMonitor();
				}
				else if (key == KeyCode.KC_NUMLOCK && !AdminMonitor.isMenuOpened())
				{
					auth.verifyAdminPanel(PlayerBase.Cast(GetGame().GetPlayer()).GetIdentity().ToString());	
				}
			}
			else
			{
				if (key == KeyCode.KC_NUMLOCK)
				{
					auth.verifyAdminPanel(PlayerBase.Cast(GetGame().GetPlayer()).GetIdentity().ToString());	
				}
			}
			
        }
		
		else if (key == KeyCode.KC_T) {
			auth.verifyTpToPos(PlayerBase.Cast(GetGame().GetPlayer()).GetIdentity().ToString());
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
                    	closeAdminMonitor();
                	} else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    	openAdminMonitor();
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
				
				if (player.getAreBindsOn())
				{
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
	}
	
	private void closeAdminMonitor() 
	{
		AdminMonitor.setMenuOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(AdminMonitor);
        UnlockControls();
	}
	
	private void openAdminMonitor()
	{
		GetGame().GetUIManager().ShowScriptedMenu(AdminMonitor, NULL);
        AdminMonitor.setMenuOpened(true);
		AdminMonitor.setPlayer(PlayerBase.Cast(PlayerBase.Cast(GetGame().GetPlayer())));

        LockControls();
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