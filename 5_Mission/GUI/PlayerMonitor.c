class PlayerMonitor extends UIScriptedMenu
{
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isMenuOpen;
			
	private TextWidget HummanityCountText;
	private TextWidget HummanityLevelCountText;
	
	ref PlayerMonitorBack MonitorBack;
	
	//Constructor
	void PlayerMonitor() {		
		MonitorBack = new ref PlayerMonitorBack();
		
		GetRPCManager().AddRPC( "Falcon", "setHummanityC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "setHummanityLevelC", this, SingeplayerExecutionType.Server );
	}
	
	//Deconstructor
	void ~PlayerMonitor() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		
		delete MonitorBack;

        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconTools/GUI/Layouts/playerMonitor.layout");
			widgetRoot.Show(false);
			
			HummanityCountText = TextWidget.Cast( widgetRoot.FindAnyWidget("HummanityCountText") );
			HummanityLevelCountText = TextWidget.Cast( widgetRoot.FindAnyWidget("HummanityLevelCountText") );
		
			isInitialized = true;
		}
			
		setHummanity();
		setHummanityLevel();
		
		return widgetRoot;		
	}

	override void OnHide() {
		super.OnHide();
        PPEffects.SetBlurMenu(0);

        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
	}
	
	override void OnShow() {
        super.OnShow();
        PPEffects.SetBlurMenu(0.5);
    }
	
	bool isMenuOpened() {
        return isMenuOpen;
    }
	
	void setMenuOpened(bool state) {
        isMenuOpen = state;
        if (isMenuOpen)
            PPEffects.SetBlurMenu(0.5);
        else
            PPEffects.SetBlurMenu(0);
    }
	
	void setHummanityC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<int> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				int hummanity = data.param1;
				HummanityCountText.SetText(hummanity.ToString());
			}
		}
	}
	
	void setHummanity() {
		MonitorBack.setPlayerHummanity();
	}
	
	void setHummanityLevelC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				string hummanityLevel = data.param1;
				HummanityLevelCountText.SetText(hummanityLevel);
			}
		}
	}
	
	void setHummanityLevel() {
		MonitorBack.setPlayerHummanityLevel();
	}
}
	
	
