class FalconMonitor extends UIScriptedMenu
{
	private Widget widgetRoot;
	
	private TextWidget gmContent;
	private TextWidget bindsContent;
	
	private ButtonWidget btnGM;
	private ButtonWidget btnHeal;
	private ButtonWidget btnKYS;
	private ButtonWidget btnSafe;
	private ButtonWidget btnBinds;
	private ButtonWidget btnAdm;
	private ButtonWidget btnCar;
	private ButtonWidget btnApplyWorld;
	private ButtonWidget btnApplyPosition;
	private ButtonWidget btnSpawn;
	
	private EditBoxWidget worldTimeBox;
	private EditBoxWidget setPositionBoxX;
	private EditBoxWidget setPositionBoxZ;
	private EditBoxWidget setPositionBoxY;
	private EditBoxWidget spawnerBox;
	
	private TextListboxWidget playersWidget;
	private TextWidget playersOnServerTEXT;
	
	///Player View
	private Widget switchWidgetPlayer;
	
	private TextWidget targetPlayerName;
	private TextWidget targetHealthText;
	private TextWidget playerPosXText;
	private TextWidget playerPosZText;
	private TextWidget playerPosYText;
	
	private ButtonWidget btnPlayerView;
	
	private ButtonWidget BtnTPtoPlayer;
	private ButtonWidget BtnFreeze;
	private ButtonWidget BtnTPtoMe;
	private ButtonWidget BtnHealPlayer;
	private ButtonWidget BtnKillPlayer;
	///
	
	///Map View
	private Widget switchWidgetMap;
	private MapWidget mapWidget;
	private ButtonWidget btnMapView;
	///
	
	private bool isInitialized;
    private bool isMenuOpen;
	private bool isPlayerViewerOpened = false;
	private bool isMapViewerOpened = false;
	
	private PlayerBase player;
	
	private string gmValue;
	private string bindsValue;
	
	ref FalconToolsV2 FalconToolsv2;
			
	
	//Constructor
	void FalconMonitor() {		
		FalconToolsv2 = new ref FalconToolsV2();
		
		///Player Viewer Commands
		GetRPCManager().AddRPC( "FalconTools", "getTargetPlayerC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "getTargetPlayerHealthC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "getTargetPlayerPosC", this, SingeplayerExecutionType.Server );
		///
		GetRPCManager().AddRPC( "FalconTools", "setPlayersListC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "setPlayersOnServerC", this, SingeplayerExecutionType.Server );
	}
	
	//Deconstructor
	void ~FalconMonitor() {
        PPEffects.SetBlurMenu( 0 );
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		
		delete FalconToolsv2;

        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconTools/GUI/Layouts/FalconMonitor.layout");
			widgetRoot.Show(false);
		
			gmContent = TextWidget.Cast( widgetRoot.FindAnyWidget("GmCONTENT") );
			bindsContent = TextWidget.Cast( widgetRoot.FindAnyWidget("BindsCONTENT") );
			
			btnGM = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnGM") );
			btnBinds = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnBinds") );
			btnHeal = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnHEAL") );
			btnKYS = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnKYS") );
			btnSafe = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnSAFE") );
			btnAdm = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnLOADOUT") );
			btnCar = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnCAR") );
			btnApplyWorld = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnApplyWorld") );
			worldTimeBox = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SetTimeBOX" ));
			btnApplyPosition = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnApplyPosition") );
			setPositionBoxX = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SetPositionBOXX" ));
			setPositionBoxZ = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SetPositionBOXZ" ));
			setPositionBoxY = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SetPositionBOXY" ));
			spawnerBox = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SpawnerBOX" ));
			btnSpawn = ButtonWidget.Cast( widgetRoot.FindAnyWidget( "BtnSpawn" ));
			
			playersWidget = TextListboxWidget.Cast(widgetRoot.FindAnyWidget("PlayersListBOX"));
			playersOnServerTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayersOnServerTEXT"));
			
			///Player Viewer
			switchWidgetPlayer = Widget.Cast(widgetRoot.FindAnyWidget("SwitchWidgetPlayer"));
			
			targetPlayerName = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerNameTEXT"));
			targetHealthText = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerHealthTEXT"));
			playerPosXText = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerPosXTEXT"));
			playerPosZText = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerPosZTEXT"));
			playerPosYText = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerPosYTEXT"));
			
			btnPlayerView = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnPlayerView"));
			
			BtnTPtoPlayer = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnTPtoPlayer")); 
			BtnFreeze = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnFreeze")); 
			BtnTPtoMe = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnTPtoMe")); 
			BtnHealPlayer = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnHealPlayer")); 
			BtnKillPlayer = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnKillPlayer"));
			///
			
			///Map View
			switchWidgetMap = Widget.Cast(widgetRoot.FindAnyWidget("SwitchWidgetMap"));
			mapWidget = MapWidget.Cast(widgetRoot.FindAnyWidget("MapWidget"));
			btnMapView = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnMapView"));
			///
			
			WidgetEventHandler.GetInstance().RegisterOnClick( btnGM, this, "setGodMode" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnBinds, this, "setBindsMode" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnHeal, this, "healPlayer" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnKYS, this, "kys" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnSafe, this, "takeMeHome" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnAdm, this, "getAdmLoadout" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnCar, this, "getCar" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnApplyWorld, this, "applyWorld" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnApplyPosition, this, "applyPosition" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnSpawn, this, "spawnItem" );
			WidgetEventHandler.GetInstance().RegisterOnClick( playersWidget, this, "selectPlayer" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnPlayerView, this, "switchPlayerViewer" );
			
			///Player Viewer Buttons
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnTPtoPlayer, this, "tpToTarget" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnFreeze, this, "freezeTarget" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnTPtoMe, this, "tpToMe" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnHealPlayer, this, "healTarget" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnKillPlayer, this, "killTarget" );
			///
						
			///Map Viewer Buttons
			WidgetEventHandler.GetInstance().RegisterOnClick(btnMapView, this, "switchMapViewer");
			///
			
			isInitialized = true;
		}
		
		setPosition();
		setTime();
		setGM();
		setBinds();
		
		playersWidget.ClearItems();
		setPlayersList();
		setPlayersOnServer();
		
		hidePlayerViewer();
		hideMapViewer();
		
		
		return widgetRoot;		
	}

	override void OnHide() {
		super.OnHide();
        PPEffects.SetBlurMenu( 0 );

        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
	}
	
	override void OnShow() {
        super.OnShow();
        PPEffects.SetBlurMenu( 0.5 );
    }
	
	override void Update(float timeslice) {
        super.Update(timeslice);
    }
	
	bool isMenuOpened() {
        return isMenuOpen;
    }

    void setMenuOpened(bool state) {
        isMenuOpen = state;
        if (isMenuOpen)
            PPEffects.SetBlurMenu( 0.5 );
        else
            PPEffects.SetBlurMenu( 0 );
    }
	
	private void setPosition() {
		if (player != null)
		{
			vector pos = player.GetPosition();
		
			setPositionBoxX.SetText(pos[0].ToString());
			setPositionBoxZ.SetText(pos[1].ToString());
			setPositionBoxY.SetText(pos[2].ToString());
		}
	}
	
	private void setTime() {
		int year, month, day, hour, minute;
		GetGame().GetWorld().GetDate(year, month, day, hour, minute);
		
		string time = hour.ToString() + ":" + minute.ToString();
		
		worldTimeBox.SetText(time);
	}
	
	private void setGM() {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player != null)
		{
			if (player.getHasGm()) {
				gmValue = "GM ON";
			}
			else {
				gmValue = "GM OFF";
			}
			
			gmContent.SetText(gmValue);
		}
	}
	
	private void setBinds() {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player != null)
		{
			if (player.getAreBindsOn()) {
				bindsValue = "Binds ON";
			}
			else {
				bindsValue = "Binds OFF";
			}
			
			bindsContent.SetText(bindsValue);
		}
	}
	
	void setPlayer(PlayerBase player) {
		this.player = player;
	}
	
	void setBindsMode() {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player != null)
		{
			player.setAreBindsOn(!player.getAreBindsOn());
		}
	}
	
	void setGodMode() {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player != null)
		{
			player.setHasGm(!player.getHasGm());
			FalconToolsv2.turnGM();	
		}
	}
	
	void applyWorld() {
		string time = worldTimeBox.GetText();
		
		FalconToolsv2.changeTime(time);
	}
	
	void healPlayer() {
		FalconToolsv2.selfHeal();
	}
	
	void kys() {
		FalconToolsv2.kys();
	}
	void takeMeHome() {
		FalconToolsv2.safe();
	}
	
	void getAdmLoadout() {
		FalconToolsv2.adm();
	}
	
	void getCar() {
		FalconToolsv2.car();
	}
	
	void applyPosition() {
		
		string tpPosX = setPositionBoxX.GetText();
		string tpPosZ = setPositionBoxZ.GetText();
		string tpPosY = setPositionBoxY.GetText();
		
		string vecto = tpPosX + " " + tpPosZ + " " + tpPosY;
		vector vec = vecto.ToVector();
		
		FalconToolsv2.setPos(vec);
	}
	
	void spawnItem() {
		FalconToolsv2.spawnItem(spawnerBox.GetText());
	}
	
	void setPlayersListC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<array<string>> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				playersWidget.ClearItems();
				array<string> playersNames = data.param1;
				
				foreach (string playerName : playersNames) {
					playersWidget.AddItem(playerName, NULL, 0);
				}
			}
		}
	}
	
	void setPlayersList() {
		FalconToolsv2.setPlayersList();
	}
	
	void selectPlayer() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		FalconToolsv2.getTargetPlayer(playerName);
		
		switchPlayerViewer();
	}
	
	void getTargetPlayerC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				string targetPName = data.param1;
				targetPlayerName.SetText(targetPName);
			}
		}
	}
	
	void getTargetPlayerHealthC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				targetHealthText.SetText(data.param1);
			}
		}
	}
	
	void getTargetPlayerPosC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<vector> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				vector targetPos = data.param1;
				
				playerPosXText.SetText(targetPos[0].ToString());
				playerPosZText.SetText(targetPos[1].ToString());
				playerPosYText.SetText(targetPos[2].ToString());
			}
		}
	}
	
	private void tpToTarget() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		
		FalconToolsv2.tpToTarget(playerName);
	}
	
	private void freezeTarget() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		
		FalconToolsv2.freezeTarget(playerName);
	}
	
	private void tpToMe() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		
		FalconToolsv2.tpToMe(playerName);
	}
	
	private void healTarget() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		
		FalconToolsv2.healTarget(playerName);
	}
	
	private void killTarget() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		
		FalconToolsv2.killTarget(playerName);
	}
	
	private void switchPlayerViewer() {
		if (isPlayerViewerOpened) {
			hidePlayerViewer();
			isPlayerViewerOpened = false;	
		}
		else {
			showPlayerViewer();
			isPlayerViewerOpened = true;
		}
	}
	
	private void switchMapViewer() {
		if (isMapViewerOpened) {
			hideMapViewer();
			isMapViewerOpened = false;	
		}
		else {
			hideMapViewer();
			isMapViewerOpened = true;
		}
	}
	
	void setPlayersOnServerC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<int> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				int playersCount = data.param1;
				
				playersOnServerTEXT.SetText("Players: " + playersCount.ToString());
			}
		}
	}
	
	private void setPlayersOnServer() {
		FalconToolsv2.setPlayersOnServer();
	}
	
	private void hidePlayerViewer() {	
		switchWidgetPlayer.Show(false);
		
		isPlayerViewerOpened = false;
	}
	
	private void showPlayerViewer() {
		switchWidgetPlayer.Show(true);
		
		isPlayerViewerOpened = true;
	}
	
	private void hideMapViewer() {
		switchWidgetMap.Show(false);
		
		isMapViewerOpened = false;
	}
	
	private void showMapViewer() {
		switchWidgetMap.Show(true);
		
		isMapViewerOpened = true;
	}
}
	
	
