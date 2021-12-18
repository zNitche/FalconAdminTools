//DeveloperFreeCamera throws NULL pointer to instance

modded class MissionGameplay {
		
	ref FalconToolsV2 FalconToolsv2;
	ref FalconMonitor AdminMonitor;

	private PlayerBase player;
	private bool isFreeCamActive = false;
	
	private ref ESPHelper espHelper;
	
	private float toolsUpdateTick = 0.01;
	private float toolsCurrentTime;
	private float toolsNTime = 0;
	private vector cameraPosition;
	
	private int espRange = 200;
	
	void MissionGameplay() {		
		FalconToolsv2 = new ref FalconToolsV2();
		
		GetRPCManager().AddRPC( "FalconTools", "OpenMenuC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "ToggleFreecamC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "messagePlayersC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "switchESPC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "disableESPC", this, SingeplayerExecutionType.Server );
	}

	override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
		
		if (key == KeyCode.KC_ADD) {
			FalconAuthenticator.verifyFreeCam();
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
					FalconAuthenticator.verifyAdminPanel();	
				}
			}
			else
			{
				if (key == KeyCode.KC_NUMLOCK)
				{
					FalconAuthenticator.verifyAdminPanel();	
				}
			}
			
        }
		
		else if (key == KeyCode.KC_T) {
			FalconAuthenticator.verifyTpToPos();
		}
		
		else if (key == KeyCode.KC_G) {
			FalconAuthenticator.verifyDeleteObject();
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
                	AdminMonitor = FalconMonitor.Cast(GetUIManager().EnterScriptedMenu(2138597, null));
                	AdminMonitor.setMenuOpened(true);
            	}
				
				disableESPHelper();
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
	
	private void switchESPC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				if (espHelper) 
				{
                	espHelper.start();
            	} 
				
				else
				{
                	espHelper = new ref ESPHelper(data.param1, espRange);
					espHelper.start();
            	}
			}
		}
	}
	
	private void disableESPHelper()
	{
		if (espHelper)
		{
			espHelper.disable();
            delete espHelper;
		}
	}
	
	private void disableESPC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				if (espHelper) 
				{
					disableESPHelper();
            	} 
			}
		}
	}
	
	override void TickScheduler(float timeslice)
	{	
		super.TickScheduler(timeslice);
		
		toolsCurrentTime = GetGame().GetTime() * 0.001;
		
		if (toolsCurrentTime >= toolsNTime + toolsUpdateTick)
		{
			if (espHelper)
			{
				if (isFreeCamActive)
				{
					cameraPosition = FalconUtils.getCameraPosition();
				}
				else
				{
					cameraPosition = GetGame().GetPlayer().GetPosition();
				}
				
				if (espHelper.getIsRunning())
				{
					espHelper.update(cameraPosition);
				}
			}
			
			toolsNTime = toolsCurrentTime;
		}
	}
	
	private void messagePlayersC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				GetGame().Chat(data.param1, "colorAction");
			}
		}
	}
	
	private void closeAdminMonitor() 
	{
		AdminMonitor.setMenuOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(AdminMonitor);
	}
	
	private void openAdminMonitor()
	{
		GetGame().GetUIManager().ShowScriptedMenu(AdminMonitor, NULL);
        AdminMonitor.setMenuOpened(true);
	}
	
	int getESPRange()
	{
		return espRange;
	}
	
	void setESPRange(int range)
	{
		espRange = range;
	}
}
