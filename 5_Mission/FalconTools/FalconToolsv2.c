class FalconToolsV2
{
	void FalconToolsV2()
    {
        GetRPCManager().AddRPC( "FalconTools", "healS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "turnGMS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "kysS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "safeS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "admS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "spawnVehicleS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "changeTimeS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "tpToPosS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "deleteObjectS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "setPosS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "spawnItemS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "getTargetPlayerS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "OpenMenuS", this, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "FalconTools", "ToggleFreecamS", this, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "FalconTools", "messagePlayersS", this, SingeplayerExecutionType.Server );
		
		///Player Viewer Commands
		GetRPCManager().AddRPC( "FalconTools", "tpToTargetS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "freezeTargetS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "tpToMeS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "healTargetS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "stripTargetS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "killTargetS", this, SingeplayerExecutionType.Server );
		///
		
		GetRPCManager().AddRPC( "FalconTools", "setPlayersListS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "setPlayersOnServerS", this, SingeplayerExecutionType.Server );
		
		GetRPCManager().AddRPC( "FalconTools", "setSpawnerPackagesS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "spawnPackageS", this, SingeplayerExecutionType.Server );
		
		GetRPCManager().AddRPC( "FalconTools", "setPlayersPositionsS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "tpOnClickS", this, SingeplayerExecutionType.Server );
		
		GetRPCManager().AddRPC( "FalconTools", "switchESPS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "disableESPS", this, SingeplayerExecutionType.Server );
		
		GetRPCManager().AddRPC( "FalconTools", "spawnMissionS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "clearMissionsS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "clearAIMissionsS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTools", "clearKOTHMissionsS", this, SingeplayerExecutionType.Server );
    }
	
	private PlayerBase getPlayer(PlayerIdentity sender) {
		array<Man> players = new array<Man>;
		
		GetGame().GetPlayers(players);
		PlayerBase player = FalconUtils.GetPlayer(sender.GetId(), players);
		
		return player;
	}

	private void OpenMenuS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				#ifdef FALCON_LOGS
					FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_ACTIVATED_PANEL);
				#endif
				
				GetRPCManager().SendRPC( "FalconTools", "OpenMenuC", new Param1<bool>(true), true, sender);
			}
        }
    }
	
	private void ToggleFreecamS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{				
				#ifdef FALCON_LOGS
					FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_ACTIVATED_FREECAM);
				#endif
				
				GetRPCManager().SendRPC( "FalconTools", "ToggleFreecamC", new Param1<bool>(true), true, sender);
			}
        }
    }
	
	private void turnGMS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				#ifdef FALCON_LOGS
					FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_SWITCHED_GM);
				#endif
				
				PlayerBase player = getPlayer(sender);
				
				player.setHasGm(!player.getHasGm());
			}
        }
    }
	
	void turnGM() {
		GetRPCManager().SendRPC( "FalconTools", "turnGMS", new Param1<string>("") );
	}
	
	private void healS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				PlayerBase player = getPlayer(sender);
				
				heal(player);
			}
        }
    }
	
	void selfHeal() {
		GetRPCManager().SendRPC( "FalconTools", "healS", new Param1<string>("") );
	}
	
	private void kysS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				PlayerBase player = getPlayer(sender);
				
				player.SetHealth(0);
			}
        }
    }
	
	void kys() {
		GetRPCManager().SendRPC( "FalconTools", "kysS", new Param1<string>("") );
	}
	
	private void safeS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				PlayerBase player = getPlayer(sender);
				
				string vecto = "2500" + " " + "200" + " " + "2500";
				vector vec = vecto.ToVector();
				
				player.SetPosition(vec);
			}
        }
    }
	
	void safe() {
		GetRPCManager().SendRPC( "FalconTools", "safeS", new Param1<string>("") );
	}
	
	private void admS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if ( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				FalconUtils.spawnAdminLoadout(getPlayer(sender));
			}
        }
    }
	
	void adm() {
		GetRPCManager().SendRPC( "FalconTools", "admS", new Param1<string>("") );
	}
	
	private void spawnVehicleS(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        Param1<string> data;
        if (!ctx.Read(data)) return;
        
        if (type == CallType.Server) 
		{
			if (data.param1)
			{
				if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
				{
					FalconUtils.spawnVehicle(data.param1, getPlayer(sender).GetPosition());
				}
			}
        }
    }
	
	void spawnVehicle(string vehicleName) {
		GetRPCManager().SendRPC( "FalconTools", "spawnVehicleS", new Param1<string>(vehicleName) );
	}
	
	private void changeTimeS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				string time = data.param1;
				
				int year, month, day, hour, minute;
				GetGame().GetWorld().GetDate(year, month, day, hour, minute);
		
				TStringArray timeTab = new TStringArray;
				time.Split(":", timeTab);
				
				GetGame().GetWorld().SetDate( year, month, day, timeTab[0].ToInt(), timeTab[1].ToInt());
			}
        }
    }
	
	void changeTime(string time) {
		GetRPCManager().SendRPC( "FalconTools", "changeTimeS", new Param1<string>(time) );
	}
	
	private void tpToPosS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< vector > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				#ifdef FALCON_LOGS
					FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_TELEPORTED + data.param1.ToString());
				#endif
				
				PlayerBase player = getPlayer(sender);
				player.SetPosition(data.param1);
			}
        }
    }
	
	private void deleteObjectS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<Object> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				if (data.param1)
				{
					#ifdef FALCON_LOGS
						FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_DELETED_OBJECT + data.param1.GetName());
					#endif
					
					GetGame().ObjectDelete(data.param1);
				}
			}
        }
    }
	
	private void setPosS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< vector > data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				#ifdef FALCON_LOGS
					FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_TELEPORTED + data.param1.ToString());
				#endif
				
				PlayerBase player = getPlayer(sender);
				player.SetPosition(data.param1);
			}
        }
    }
	
	void setPos(vector pos) {
		GetRPCManager().SendRPC( "FalconTools", "setPosS", new Param1<vector>(pos) );
	}
	
	private void spawnItemS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				#ifdef FALCON_LOGS
						FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_SPAWNED_ITEM + data.param1);
				#endif
				
				PlayerBase player = getPlayer(sender);
				
				GetGame().CreateObject(data.param1, player.GetPosition(), false, false, false );
			}
        }
    }
	
	void spawnItem(string item) {
		GetRPCManager().SendRPC( "FalconTools", "spawnItemS", new Param1<string>(item) );
	}

	private void getTargetPlayerS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
						
				if (data.param1 == "") {
					return;
				} 
				else {
					PlayerBase targetP = FalconUtils.GetPlayerByName(data.param1);
					
					TargetPlayerPackage playerDataPackage = new TargetPlayerPackage(targetP.GetIdentity().GetName(), targetP.GetHealth().ToString(),
					targetP.GetPosition(), targetP.GetIdentity().GetId());
					
					GetRPCManager().SendRPC("FalconTools", "getTargetPlayerC", new Param1<TargetPlayerPackage>(playerDataPackage), true, sender);
				}
			}
       	 }
    }
	
	void getTargetPlayer(string targetPlayer) {	
		GetRPCManager().SendRPC( "FalconTools", "getTargetPlayerS", new Param1<string>(targetPlayer) );
	}
	
	///Player Viewer
	private void tpToMeS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
						
				if (data.param1 == "") {
					return;
				} 
				else {
					PlayerBase targetP = FalconUtils.GetPlayerByName(data.param1);
					PlayerBase player = getPlayer(sender);
					
					targetP.SetPosition(player.GetPosition());
				}
			}
       	 }
    }
	
	void tpToMe(string targetPlayer) {	
		GetRPCManager().SendRPC( "FalconTools", "tpToMeS", new Param1<string>(targetPlayer) );
	}
	
	private void freezeTargetS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
						
				if (data.param1 == "") {
					return;
				} 
				else {
					PlayerBase targetP = FalconUtils.GetPlayerByName(data.param1);
					
					#ifdef FALCON_LOGS
						FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_FREEZED_PLAYER + data.param1);
					#endif
					
					HumanInputController hic = targetP.GetInputController();
					
					if (targetP.getIsFreezed()) {
						hic.SetDisabled(false);
						targetP.setIsFreezed(false);
					}
					else {
						hic.SetDisabled(true);
						targetP.setIsFreezed(true);
					}
				}
			}
       	 }
    }
	
	void freezeTarget(string targetPlayer) {	
		GetRPCManager().SendRPC( "FalconTools", "freezeTargetS", new Param1<string>(targetPlayer) );
	}
	
	private void tpToTargetS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
						
				if (data.param1 == "") {
					return;
				} 
				else {
					PlayerBase targetP = FalconUtils.GetPlayerByName(data.param1);
					PlayerBase player = getPlayer(sender);

					player.SetPosition(targetP.GetPosition());
				}
			}
       	 }
    }
	
	void tpToTarget(string targetPlayer) {	
		GetRPCManager().SendRPC( "FalconTools", "tpToTargetS", new Param1<string>(targetPlayer) );
	}
	
	private void healTargetS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
						
				if (data.param1 == "") {
					return;
				} 
				else {
					PlayerBase targetP = FalconUtils.GetPlayerByName(data.param1);
					heal(targetP);
				}
			}
       	 }
    }
	
	void healTarget(string targetPlayer) {	
		GetRPCManager().SendRPC( "FalconTools", "healTargetS", new Param1<string>(targetPlayer) );
	}
	
	private void stripTargetS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
						
				if (data.param1 == "") {
					return;
				} 
				else {
					PlayerBase targetP = FalconUtils.GetPlayerByName(data.param1);
					
					targetP.RemoveAllItems();
					
					#ifdef FALCON_LOGS
						FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_STRIPED_PLAYER + data.param1);
					#endif
				}
			}
       	 }
    }
	
	void stripTarget(string targetPlayer) {	
		GetRPCManager().SendRPC( "FalconTools", "stripTargetS", new Param1<string>(targetPlayer) );
	}
	
	private void killTargetS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
						
				if (data.param1 == "") {
					return;
				} 
				else {
					PlayerBase targetP = FalconUtils.GetPlayerByName(data.param1);
					
					targetP.SetHealth(0);
					
					#ifdef FALCON_LOGS
						FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_KILLED_PLAYER + data.param1);
					#endif
				}
			}
       	 }
    }
	
	void killTarget(string targetPlayer) {	
		GetRPCManager().SendRPC( "FalconTools", "killTargetS", new Param1<string>(targetPlayer) );
	}
	
	private void messagePlayersS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				GetRPCManager().SendRPC( "FalconTools", "messagePlayersC", new Param1<string>(data.param1) );
			}
       	 }
    }
	
	void messagePlayers(string message) {	
		GetRPCManager().SendRPC("FalconTools", "messagePlayersS", new Param1<string>("[Admin]: " + message));
	}
	
	private void setPlayersListS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				array<Man> players = new array<Man>;
				
				GetGame().GetPlayers(players);
				
				array<string> playersNames = new array<string>;
				
				for (int i = 0; i < players.Count(); i++) 
				{
					playersNames.Insert(players[i].GetIdentity().GetName());
				}	
				
				GetRPCManager().SendRPC( "FalconTools", "setPlayersListC", new Param1<array<string>>(playersNames), true, sender );
			}
       	 }
    }
	
	void setPlayersList() {	
		GetRPCManager().SendRPC( "FalconTools", "setPlayersListS", new Param1<string>("") );
	}
	///Player Viewer
	
	private void setPlayersOnServerS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				array<Man> players = new array<Man>;
				
				GetGame().GetPlayers(players);
				
				int playersCount = players.Count();
				
				GetRPCManager().SendRPC( "FalconTools", "setPlayersOnServerC", new Param1<int>(playersCount), true, sender );
			}
       	 }
    }
	
	void setPlayersOnServer() {	
		GetRPCManager().SendRPC( "FalconTools", "setPlayersOnServerS", new Param1<string>("") );
	}
	
	private void setSpawnerPackagesS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				array<string> spawnerPackagesNames = new array<string>();

				spawnerPackagesNames = loadItemsPackagesNames();
				
				GetRPCManager().SendRPC("FalconTools", "setSpawnerPackagesC", new Param1<array<string>>(spawnerPackagesNames), true, sender);
			}
       	 }
    }
	
	void setSpawnerPackages() {	
		GetRPCManager().SendRPC( "FalconTools", "setSpawnerPackagesS", new Param1<string>("") );
	}
	
	private void spawnPackageS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				if (data.param1)
				{
					string packageName = data.param1;
					PlayerBase player = getPlayer(sender);
					ref array<ref ItemInPackage> packageItems = new array<ref ItemInPackage>();
					
					#ifdef FALCON_LOGS
						FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_SPAWNED_ITEM + packageName);
					#endif
					
					packageItems = getItemsPackageByName(packageName);

					for (int i = 0; i < packageItems.Count(); i++)
					{
						for (int j = 0; j < packageItems[i].getAmmount(); j++)
						{
							GetGame().CreateObject(packageItems[i].getName(), player.GetPosition(), false, false, true);
						}
					}
				}
			}
       	 }
    }
	
	void spawnPackage(string packageName) {	
		GetRPCManager().SendRPC("FalconTools", "spawnPackageS", new Param1<string>(packageName));
	}
	
	private void setPlayersPositionsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				array<Man> players = new array<Man>();
				array<ref PlayerPositionPackage> positions = new array<ref PlayerPositionPackage>();
				
				GetGame().GetPlayers(players);
				
				for (int i = 0; i < players.Count(); i++)
				{
					positions.Insert(new PlayerPositionPackage(players[i].GetIdentity().GetName(), players[i].GetPosition()));
				}
				
				GetRPCManager().SendRPC("FalconTools", "setPlayersPositionsC", new Param1<array<ref PlayerPositionPackage>>(positions), true, sender);
			}
       	 }
    }
	
	void setPlayersPositions() {	
		GetRPCManager().SendRPC("FalconTools", "setPlayersPositionsS", new Param1<string>(""));
	}
	
	private void tpOnClickS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<vector> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				if (data.param1)
				{
					#ifdef FALCON_LOGS
						FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_TELEPORTED + data.param1.ToString());
					#endif
					
					PlayerBase player = getPlayer(sender);
					
					player.SetPosition(data.param1);
				}
			}
       	 }
    }
	
	void tpOnClick(vector pos) {	
		GetRPCManager().SendRPC("FalconTools", "tpOnClickS", new Param1<vector>(pos));
	}
	
	private void switchESPS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				if (data.param1)
				{
					#ifdef FALCON_LOGS
						FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_SWITCHED_ESP);
					#endif
					
					GetRPCManager().SendRPC("FalconTools", "switchESPC", new Param1<string>(data.param1), true, sender);
				}
			}
       	 }
    }
	
	void playersESP() 
	{
		GetRPCManager().SendRPC("FalconTools", "switchESPS", new Param1<string>("players"));
	}
	
	void objectsESP() 
	{
		GetRPCManager().SendRPC("FalconTools", "switchESPS", new Param1<string>("objects"));
	}
	
	private void disableESPS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<vector> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				if (data.param1)
				{
					#ifdef FALCON_LOGS
						//FalconLogsUtils.logAdminAction(sender, FalconLogsMessagesConsts.ADMIN_TELEPORTED + data.param1.ToString());
					#endif
					
					GetRPCManager().SendRPC("FalconTools", "disableESPC", new Param1<string>(""), true, sender);
				}
			}
       	 }
    }
	
	void disableESP() 
	{
		GetRPCManager().SendRPC("FalconTools", "disableESPS", new Param1<string>(""));
	}
	
	private void spawnMissionS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;

        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				if (data.param1)
				{
					string missionName = data.param1;
					
					#ifdef FALCON_MISSIONS
					MissionServer mission = MissionServer.Cast(GetGame().GetMission());
					
					if (missionName == "HiddenTreasureMission")
					{
						mission.getMissionManager().spawnHiddenTreasuresMissionDebug();
					}
					else if (missionName == "AirDropMission")
					{
						mission.getMissionManager().spawnAirDropMissionDebug();
					}
					else if (missionName == "CivilianConvoy")
					{
						mission.getMissionManager().spawnCivilianConvoyMissionsDebug();
					}
					else if (missionName == "MilitaryConvoy")
					{
						mission.getMissionManager().spawnMilitaryConvoyMissionsDebug();
					}
					else if (missionName == "PlaneCrash")
					{
						mission.getMissionManager().spawnPlaneCrashMissionDebug();
					}
					else if (missionName == "RougeFarmers")
					{
						mission.getAIMissionManager().spawnRogueFarmersMissionsDebug();
					}
					else if (missionName == "BaseKOTH")
					{
						mission.getKOTHMissionsManager().spawnBaseKOTHMissionDebug();
					}
					#endif 
				}
			}
       	 }
    }
	
	void spawnMission(string missionName)
	{
		GetRPCManager().SendRPC("FalconTools", "spawnMissionS", new Param1<string>(missionName));
	}
	
	private void clearMissionsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;

        if( type == CallType.Server ) 
		{
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				#ifdef FALCON_MISSIONS
					MissionServer mission = MissionServer.Cast(GetGame().GetMission());
				
					mission.getMissionManager().clearMissionsDebug();
				#endif
			}
       	 }
    }
	
	void clearMissions()
	{
		GetRPCManager().SendRPC("FalconTools", "clearMissionsS", new Param1<string>(""));
	}
	
	private void clearAIMissionsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;

        if( type == CallType.Server ) 
		{
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				#ifdef FALCON_MISSIONS
					MissionServer mission = MissionServer.Cast(GetGame().GetMission());
				
					mission.getAIMissionManager().clearMissionsDebug();
				#endif
			}
       	 }
    }
	
	void clearAIMissions()
	{
		GetRPCManager().SendRPC("FalconTools", "clearAIMissionsS", new Param1<string>(""));
	}
	
	private void clearKOTHMissionsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;

        if( type == CallType.Server ) 
		{
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) 
			{
				#ifdef FALCON_MISSIONS
					MissionServer mission = MissionServer.Cast(GetGame().GetMission());
				
					mission.getKOTHMissionsManager().clearMissionsDebug();
				#endif
			}
       	 }
    }
	
	void clearKOTHMissions()
	{
		GetRPCManager().SendRPC("FalconTools", "clearKOTHMissionsS", new Param1<string>(""));
	}
	
	///TODO: Move utils to another file ? 
	private void heal(PlayerBase player) {
		player.SetHealth(player.GetMaxHealth("", ""));
		player.SetHealth("", "Blood", player.GetMaxHealth("", "Blood"));
		player.GetStatStamina().Set(1000);
		player.GetStatEnergy().Set(player.GetStatEnergy().GetMax());
		player.GetStatWater().Set(player.GetStatWater().GetMax());
		player.SetHealth("GlobalHealth", "Shock", player.GetMaxHealth("GlobalHealth", "Shock"));
		player.GetBleedingManagerServer().RemoveAllSources();
		
		//Heal Broken Limbs
		if (player.m_BrokenLegState == eBrokenLegs.BROKEN_LEGS || player.m_BrokenLegState == eBrokenLegs.BROKEN_LEGS_SPLINT)
		{
			player.AddHealth("LeftLeg", "Health", (player.GetMaxHealth("LeftLeg", "Health")));
			player.AddHealth("RightLeg", "Health", (player.GetMaxHealth("RightLeg", "Health")));
			player.AddHealth("RightFoot", "Health", (player.GetMaxHealth("RightFoot", "Health")));
			player.AddHealth("LeftFoot", "Health",	(player.GetMaxHealth("LeftFoot", "Health")));
			
			player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BROKEN_LEGS);
			player.UpdateBrokenLegs(eBrokenLegs.NO_BROKEN_LEGS);
			
			player.m_NotifiersManager.DeactivateByType(eNotifiers.NTF_FRACTURE);
			
			EntityAI attachment;
			
			Class.CastTo(attachment, player.GetItemOnSlot("Splint_Right"));
			
			if (attachment && attachment.GetType() == "Splint_Applied")
			{
				attachment.Delete();
			}
		}
		
		//Heal Diseases
		player.RemoveAllAgents();
	}
	///
	
	private array<ref ItemsPackage> loadItemsPackages()
	{
		const static string itemsPackagesPath = "$profile:/FT/items_packages.json";
		array<ref ItemsPackage> itemsPackages = new array<ref ItemsPackage>();
		
		if (FileExist(itemsPackagesPath))
		{
			JsonFileLoader<array<ref ItemsPackage>>.JsonLoadFile(itemsPackagesPath, itemsPackages);
		}
		
		return itemsPackages;
	}
	
	private array<string> loadItemsPackagesNames()
	{
		array<string> itemsPackagesNames = new array<string>();
		array<ref ItemsPackage> itemsPackages = new array<ref ItemsPackage>();
		
		itemsPackages = loadItemsPackages();
		
		for (int i = 0; i < itemsPackages.Count(); i++)
		{
			itemsPackagesNames.Insert(itemsPackages[i].getName());
		}
		
		return itemsPackagesNames;
	}
	
	private array<ref ItemInPackage> getItemsPackageByName(string itemsPackageName)
	{
		ref array<ref ItemInPackage> items = new array<ref ItemInPackage>();
		array<ref ItemsPackage> itemsPackages = new array<ref ItemsPackage>();
		
		itemsPackages = loadItemsPackages();
		
		for (int i = 0; i < itemsPackages.Count(); i++)
		{
			if (itemsPackages[i].getName() == itemsPackageName)
			{
				items = itemsPackages[i].getItems();
			}
		}
		
		return items;
	}
}