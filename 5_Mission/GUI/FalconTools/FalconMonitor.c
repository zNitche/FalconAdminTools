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
	private ButtonWidget btnTruck;
	private ButtonWidget btnApplyWorld;
	private ButtonWidget btnApplyPosition;
	private ButtonWidget btnSpawn;	
	private ButtonWidget btnMessagePlayers;
	
	///Items Spawner
	private TextListboxWidget spawnerPacksLIST;
	private ButtonWidget btnSpawnPack;
	///
	
	private EditBoxWidget worldTimeBox;
	private EditBoxWidget setPositionBoxX;
	private EditBoxWidget setPositionBoxZ;
	private EditBoxWidget setPositionBoxY;
	private EditBoxWidget messagePlayersInput;
	private EditBoxWidget spawnerBox;
	
	private TextListboxWidget playersWidget;
	private TextWidget playersOnServerTEXT;
	
	///Player View
	private Widget playerWidget;
	
	private TextWidget targetPlayerName;
	private TextWidget targetHealthText;
	private TextWidget playerPosXText;
	private TextWidget playerPosZText;
	private TextWidget playerPosYText;
	private TextWidget playerOrientationText;
	private EditBoxWidget playerIdentityTEXT;
	
	private ButtonWidget BtnTPtoPlayer;
	private ButtonWidget BtnFreeze;
	private ButtonWidget BtnTPtoMe;
	private ButtonWidget BtnHealPlayer;
	private ButtonWidget BtnStripPlayer;
	private ButtonWidget BtnKillPlayer;
	private ButtonWidget BtnCopyID;
	
	private bool isInitialized;
    private bool isMenuOpen;
	
	private string gmValue;
	private string bindsValue;
	
	private Widget mapWidget;
	private MapWidget falconMAP;
	private ButtonWidget switchMapBUTTON;
	
	private Widget espWidget;
	private ButtonWidget disableESPBUTTON;
	private ButtonWidget playersESPBUTTON;
	private ButtonWidget objectsESPBUTTON;
	private ButtonWidget switchESPBUTTON;
	private EditBoxWidget espRangeInput;
	private ButtonWidget setESPRangeBUTTON;
	
	private Widget missionsWidget;
	
	private ButtonWidget spawnHiddenTreasuresBUTTON;
	private ButtonWidget spawnAirDropMissionBUTTON;
	private ButtonWidget spawnCivilianConvoyMissionBUTTON;
	private ButtonWidget spawnMilitaryConvoyMissionBUTTON;
	private ButtonWidget spawnPlaneCrashMissionBUTTON;
	
	private ButtonWidget rougeFarmersBUTTON;
	private ButtonWidget baseKOTHBUTTON;
	
	private ButtonWidget switchMISSIONSBUTTON;
	private ButtonWidget clearMissionsBUTTON;
	private ButtonWidget clearAIMissionsBUTTON;
	private ButtonWidget clearKOTHMissionsBUTTON;
	
	private EditBoxWidget viewDistanceTEXT;
	private ButtonWidget viewBUTTON;
	
	private ButtonWidget invBUTTON;
	
	private Widget currentViewWidget;
	
	ref FalconToolsV2 FalconToolsv2;
	
	private string dotIcon = "FalconTools\\GUI\\textures\\dot.paa";
			
	
	//Constructor
	void FalconMonitor() {		
		FalconToolsv2 = new ref FalconToolsV2();
		
		///Player Viewer Commands
		GetRPCManager().AddRPC( "FalconTools", "getTargetPlayerC", this, SingeplayerExecutionType.Server );
		///
		GetRPCManager().AddRPC( "FalconTools", "setPlayersListC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "setPlayersOnServerC", this, SingeplayerExecutionType.Server );
		
		GetRPCManager().AddRPC( "FalconTools", "setSpawnerPackagesC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "setPlayersPositionsC", this, SingeplayerExecutionType.Server );
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
			btnTruck = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnTRUCK") );
			btnApplyWorld = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnApplyWorld") );
			worldTimeBox = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SetTimeBOX" ));
			btnApplyPosition = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnApplyPosition") );
			setPositionBoxX = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SetPositionBOXX" ));
			setPositionBoxZ = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SetPositionBOXZ" ));
			setPositionBoxY = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SetPositionBOXY" ));
			spawnerBox = EditBoxWidget.Cast( widgetRoot.FindAnyWidget( "SpawnerBOX" ));
			btnSpawn = ButtonWidget.Cast( widgetRoot.FindAnyWidget( "BtnSpawn" ));
			messagePlayersInput = EditBoxWidget.Cast( widgetRoot.FindAnyWidget("MessagePlayersINPUT"));
			btnMessagePlayers = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnMessagePlayers"));
			
			playersWidget = TextListboxWidget.Cast(widgetRoot.FindAnyWidget("PlayersListBOX"));
			playersOnServerTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayersOnServerTEXT"));
			
			///Player Viewer
			playerWidget = Widget.Cast(widgetRoot.FindAnyWidget("SwitchWidgetPlayer"));
			
			targetPlayerName = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerNameTEXT"));
			targetHealthText = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerHealthTEXT"));
			playerPosXText = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerPosXTEXT"));
			playerPosZText = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerPosZTEXT"));
			playerPosYText = TextWidget.Cast(widgetRoot.FindAnyWidget("PlayerPosYTEXT"));
			
			playerOrientationText = TextWidget.Cast(widgetRoot.FindAnyWidget("OrientationTEXT"));
			
			playerIdentityTEXT = EditBoxWidget.Cast(widgetRoot.FindAnyWidget("PlayerIdentityTEXT"));
			
			BtnTPtoPlayer = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnTPtoPlayer")); 
			BtnFreeze = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnFreeze")); 
			BtnTPtoMe = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnTPtoMe")); 
			BtnHealPlayer = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnHealPlayer")); 
			BtnStripPlayer = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnStripPlayer")); 
			BtnKillPlayer = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnKillPlayer"));
			BtnCopyID = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BtnCopyID"));
			///
			
			WidgetEventHandler.GetInstance().RegisterOnClick( btnGM, this, "setGodMode" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnBinds, this, "setBindsMode" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnHeal, this, "healPlayer" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnKYS, this, "kys" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnSafe, this, "takeMeHome" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnAdm, this, "getAdmLoadout" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnCar, this, "getCar" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnTruck, this, "getTruck" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnApplyWorld, this, "applyWorld" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnApplyPosition, this, "applyPosition" );
			WidgetEventHandler.GetInstance().RegisterOnClick( btnSpawn, this, "spawnItem" );
			WidgetEventHandler.GetInstance().RegisterOnClick( playersWidget, this, "selectPlayer" );
			
			WidgetEventHandler.GetInstance().RegisterOnClick( btnMessagePlayers, this, "messagePlayers" );
			
			///Player Viewer Buttons
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnTPtoPlayer, this, "tpToTarget" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnFreeze, this, "freezeTarget" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnTPtoMe, this, "tpToMe" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnHealPlayer, this, "healTarget" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnStripPlayer, this, "stripTarget" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnKillPlayer, this, "killTarget" );
			WidgetEventHandler.GetInstance().RegisterOnClick( BtnCopyID, this, "copyID" );
			///
			
			///Items Spawner
			spawnerPacksLIST = TextListboxWidget.Cast( widgetRoot.FindAnyWidget("SpawnerPacksLIST"));
			btnSpawnPack = ButtonWidget.Cast( widgetRoot.FindAnyWidget("BtnSpawnPack"));
			WidgetEventHandler.GetInstance().RegisterOnClick( btnSpawnPack, this, "spawnPack" );
			///
			mapWidget = Widget.Cast(widgetRoot.FindAnyWidget("MapWIDGET"));
			
			falconMAP = MapWidget.Cast(widgetRoot.FindAnyWidget("FalconMAP"));
			switchMapBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("MapBUTTON"));
			WidgetEventHandler.GetInstance().RegisterOnClick( switchMapBUTTON, this, "showMapWidget" );
			
			viewDistanceTEXT = EditBoxWidget.Cast(widgetRoot.FindAnyWidget("ViewDistanceTEXT"));
			viewBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("ViewBUTTON"));
			WidgetEventHandler.GetInstance().RegisterOnClick( viewBUTTON, this, "setViewDistance" );
			
			invBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("invBUTTON"));
			WidgetEventHandler.GetInstance().RegisterOnClick( invBUTTON, this, "switchInv" );
			
			espWidget = Widget.Cast(widgetRoot.FindAnyWidget("ESPWIDGET"));
			switchESPBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("ESPBUTTON"));
			playersESPBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("PlayersESPBUTTON"));
			objectsESPBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("ObjectsESPBUTTON"));
			disableESPBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("DisableESPBUTTON"));
			espRangeInput = EditBoxWidget.Cast(widgetRoot.FindAnyWidget("ESPRangeInput"));
			setESPRangeBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("SetESPRangeBUTTON"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick(switchESPBUTTON, this, "showESPWidget");
			WidgetEventHandler.GetInstance().RegisterOnClick(playersESPBUTTON, this, "playersESP");
			WidgetEventHandler.GetInstance().RegisterOnClick(objectsESPBUTTON, this, "objectsESP");
			WidgetEventHandler.GetInstance().RegisterOnClick(disableESPBUTTON, this, "disableESP");
			WidgetEventHandler.GetInstance().RegisterOnClick(setESPRangeBUTTON, this, "setESPRange");
			
			missionsWidget = Widget.Cast(widgetRoot.FindAnyWidget("MISSIONSWIDGET"));
			switchMISSIONSBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("MISSIONSBUTTON"));
			
			spawnHiddenTreasuresBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("HiddenTreasuresBUTTON"));
			spawnAirDropMissionBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("AirDropBUTTON"));
			spawnCivilianConvoyMissionBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("CivilianConvoyBUTTON"));
			spawnMilitaryConvoyMissionBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("MilitaryConvoyBUTTON"));
			spawnPlaneCrashMissionBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("PlaneCrashBUTTON"));
			
			rougeFarmersBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("RougeFarmersBUTTON"));
			
			baseKOTHBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BaseKOTHBUTTON"));
			
			clearMissionsBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("ClearMissionsBUTTON"));
			clearAIMissionsBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("ClearAIMissionsBUTTON"));
			clearKOTHMissionsBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("ClearKOTHMissionsBUTTON"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick(switchMISSIONSBUTTON, this, "showMissionsWidget");
			
			WidgetEventHandler.GetInstance().RegisterOnClick(spawnHiddenTreasuresBUTTON, this, "spawnHiddenTreasures");
			WidgetEventHandler.GetInstance().RegisterOnClick(spawnAirDropMissionBUTTON, this, "spawnAirDropMission");
			WidgetEventHandler.GetInstance().RegisterOnClick(spawnCivilianConvoyMissionBUTTON, this, "spawnCivilianConvoyMission");
			WidgetEventHandler.GetInstance().RegisterOnClick(spawnMilitaryConvoyMissionBUTTON, this, "spawnMilitaryConvoyMission");
			WidgetEventHandler.GetInstance().RegisterOnClick(spawnPlaneCrashMissionBUTTON, this, "spawnPlaneCrashMission");
			WidgetEventHandler.GetInstance().RegisterOnClick(rougeFarmersBUTTON, this, "spawnRougeFarmersMission");
			WidgetEventHandler.GetInstance().RegisterOnClick(baseKOTHBUTTON, this, "spawnBaseKOTHMission");
			
			WidgetEventHandler.GetInstance().RegisterOnClick(clearMissionsBUTTON, this, "clearMissions");
			WidgetEventHandler.GetInstance().RegisterOnClick(clearAIMissionsBUTTON, this, "clearAIMissions");
			WidgetEventHandler.GetInstance().RegisterOnClick(clearKOTHMissionsBUTTON, this, "clearKOTHMissions");
			
			isInitialized = true;
		}
		
		initWidget();
		
		return widgetRoot;		
	}
	
	void initWidget() {
		playersWidget.ClearItems();
		spawnerPacksLIST.ClearItems();
		playerWidget.Show(false);
		espWidget.Show(false);
		missionsWidget.Show(false);

		falconMAP.ClearUserMarks();
		mapWidget.Show(true);
		
		setPosition();
		setTime();
		setGM();
		setBinds();
		setOrientation();
		
		setPlayersList();
		setPlayersPositions();
		setPlayersOnServer();
		setSpawnerPackages();
		
		currentViewWidget = mapWidget;
	}

	override void OnHide() {
		super.OnHide();
        PPEffects.SetBlurMenu( 0 );

        unlockControls();
	}
	
	override void OnShow() {
        super.OnShow();
        PPEffects.SetBlurMenu( 0.5 );
		
		lockControls();
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
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player != null)
		{
			vector pos = player.GetPosition();
		
			setPositionBoxX.SetText(pos[0].ToString());
			setPositionBoxY.SetText(pos[1].ToString());
			setPositionBoxZ.SetText(pos[2].ToString());
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
	
	private void setESPRange()
	{
		MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
		
		string espRange = espRangeInput.GetText();
		
		if (espRange)
		{
			mission.setESPRange(espRange.ToInt());
		}
	}
	
	private void initESPRange()
	{
		MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
	
		espRangeInput.SetText(mission.getESPRange().ToString());
	}
	
	private void setOrientation()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		string orientation = player.GetDirection().ToString();
		
		playerOrientationText.SetText(orientation);
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
	
	private void setBindsMode() {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player != null)
		{
			player.setAreBindsOn(!player.getAreBindsOn());
		}
		
		setBinds();
	}
	
	private void setGodMode() {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player != null)
		{
			player.setHasGm(!player.getHasGm());
			FalconToolsv2.turnGM();	
		}
		
		setGM();
	}
	
	private void setViewDistance()
	{
		int distance = viewDistanceTEXT.GetText().ToInt();
		
		GetGame().GetWorld().SetPreferredViewDistance(distance);
		GetGame().GetWorld().SetViewDistance(distance);
		GetGame().GetWorld().SetObjectViewDistance(distance);
	}
	
	private void switchInv()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		player.setIsInv(!player.getIsInv());
	}
	
	private void showMapWidget()
	{
		switchViewWidget(mapWidget);
	}
	
	private void showESPWidget()
	{
		switchViewWidget(espWidget);
		initESPRange();
	}
	
	private void showMissionsWidget()
	{
		switchViewWidget(missionsWidget);
	}
	
	private void showPlayerWidget()
	{
		switchViewWidget(playerWidget);
	}
	
	private void switchViewWidget(Widget widget) 
	{
		currentViewWidget.Show(false);
		currentViewWidget = widget;
		currentViewWidget.Show(true);
	}
	
	private void applyWorld() {
		string time = worldTimeBox.GetText();
		
		FalconToolsv2.changeTime(time);
	}
	
	private void healPlayer() {
		FalconToolsv2.selfHeal();
	}
	
	private void kys() {
		FalconToolsv2.kys();
	}
	private void takeMeHome() {
		FalconToolsv2.safe();
	}
	
	private void getAdmLoadout() {
		FalconToolsv2.adm();
	}
	
	private void getCar() 
	{
		FalconToolsv2.spawnVehicle("OffroadHatchback");
	}
	
	private void getTruck() 
	{
		FalconToolsv2.spawnVehicle("Truck_01_Covered");
	}
	
	private void applyPosition() {
		
		string tpPosX = setPositionBoxX.GetText();
		string tpPosZ = setPositionBoxZ.GetText();
		string tpPosY = setPositionBoxY.GetText();
		
		string vecto = tpPosX + " " + tpPosY + " " + tpPosZ;
		vector vec = vecto.ToVector();
		
		FalconToolsv2.setPos(vec);
	}
	
	private void spawnItem() {
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
				
				array<string> playersNames = new array<string>();
				playersNames = data.param1;
				
				for (int i = 0; i < playersNames.Count(); i++)
				{
					playersWidget.AddItem(playersNames[i], NULL, 0);
				}
			}
		}
	}
	
	private void setPlayersList() {
		FalconToolsv2.setPlayersList();
	}
	
	private void selectPlayer() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		FalconToolsv2.getTargetPlayer(playerName);
		
		showPlayerWidget();
	}
	
	void getTargetPlayerC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<TargetPlayerPackage> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				TargetPlayerPackage dataPackage = data.param1;
				
				targetPlayerName.SetText(dataPackage.playerName);
				playerIdentityTEXT.SetText(dataPackage.playerIdentity);
				targetHealthText.SetText(dataPackage.playerHealth);
				playerPosXText.SetText(dataPackage.playerPos[0].ToString());
				playerPosZText.SetText(dataPackage.playerPos[1].ToString());
				playerPosYText.SetText(dataPackage.playerPos[2].ToString());
			}
		}
	}
	
	private void messagePlayers() {
		string message = messagePlayersInput.GetText();
		
		FalconToolsv2.messagePlayers(message);
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
	
	private void stripTarget() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		
		FalconToolsv2.stripTarget(playerName);
	}
	
	private void killTarget() {
		int ind = playersWidget.GetSelectedRow();
		string playerName;
		
		playersWidget.GetItemText(ind, 0, playerName);
		
		FalconToolsv2.killTarget(playerName);
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
	
	void setSpawnerPackagesC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) 
	{
		Param1<array<string>> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				array<string> packageName = new array<string>();
				packageName = data.param1;
				
				for (int i = 0; i < packageName.Count(); i++) 
				{
					spawnerPacksLIST.AddItem(packageName[i], NULL, 0);
				}
			}
		}
	}
	
	private void setSpawnerPackages() 
	{
		FalconToolsv2.setSpawnerPackages();
	}
	
	void setPlayersPositionsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) 
	{
		Param1<array<ref PlayerPositionPackage>> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				array<ref PlayerPositionPackage> positions = new array<ref PlayerPositionPackage>();
				positions = data.param1;
				
				for (int i = 0; i < positions.Count(); i++) 
				{
					falconMAP.AddUserMark(positions[i].playerPosition, positions[i].playerName, ARGB(255, 230, 20, 20), dotIcon);
				}
			}
		}
	}
	
	private void setPlayersPositions() 
	{
		FalconToolsv2.setPlayersPositions();
	}
	
	private void playersESP() 
	{
		FalconToolsv2.playersESP();
	}
	
	private void objectsESP() 
	{
		FalconToolsv2.objectsESP();
	}
	
	private void disableESP() 
	{
		FalconToolsv2.disableESP();
	}
	
	private void spawnPack()
	{
		int ind = spawnerPacksLIST.GetSelectedRow();
		
		if (ind >= 0)
		{
			string packageName;
		
			spawnerPacksLIST.GetItemText(ind, 0, packageName);
			
			if (packageName)
			{
				FalconToolsv2.spawnPackage(packageName);
			}
		}
	}
	
	private void spawnHiddenTreasures()
	{
		FalconToolsv2.spawnMission("HiddenTreasureMission");
	}
	
	private void spawnAirDropMission()
	{
		FalconToolsv2.spawnMission("AirDropMission");
	}
	
	private void spawnCivilianConvoyMission()
	{
		FalconToolsv2.spawnMission("CivilianConvoy");
	}
	
	private void spawnMilitaryConvoyMission()
	{
		FalconToolsv2.spawnMission("MilitaryConvoy");
	}
	
	private void spawnPlaneCrashMission()
	{
		FalconToolsv2.spawnMission("PlaneCrash");
	}
	
	private void clearMissions()
	{
		FalconToolsv2.clearMissions();
	}
	
	private void clearAIMissions()
	{
		FalconToolsv2.clearAIMissions();
	}
	
	private void clearKOTHMissions()
	{
		FalconToolsv2.clearKOTHMissions();
	}
	
	private void spawnRougeFarmersMission()
	{
		FalconToolsv2.spawnMission("RougeFarmers");
	}
	
	private void spawnBaseKOTHMission()
	{
		FalconToolsv2.spawnMission("BaseKOTH");
	}
	
	private void copyID()
	{
		string id = playerIdentityTEXT.GetText();
		
		if (id)
		{
			GetGame().CopyToClipboard(id);
		}
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) 
	{	
		if (w == falconMAP)
		{	
			vector cursorPosition = falconMAP.ScreenToMap(Vector(x, y, 0));
			
			FalconToolsv2.tpOnClick(Vector(cursorPosition[0], GetGame().SurfaceY(cursorPosition[0], cursorPosition[2]), cursorPosition[2]));
						
			return true;
		}
		
		return true;
	}
		
	private void lockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void unlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
}
	
	
