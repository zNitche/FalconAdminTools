//TODO: Yeah some functions (almost all of them) take PlayerBase as arg. Decide what to do with it.
class FalconToolsV2
{
	private PlayerBase player;
	private ref array<Man> players = new array<Man>;
	
	void FalconToolsV2()
    {
        GetRPCManager().AddRPC( "Falcon", "healS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "turnGMS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "kysS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "safeS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "admS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "carS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "changeTimeS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "tpToPosS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "setPosS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "spawnItemS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "getTargetPlayerS", this, SingeplayerExecutionType.Server );
		
		///Player Viewer Commands
		GetRPCManager().AddRPC( "Falcon", "tpToTargetS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "freezeTargetS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "tpToMeS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "healTargetS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "killTargetS", this, SingeplayerExecutionType.Server );
		///
		
		GetRPCManager().AddRPC( "Falcon", "setPlayersListS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "setPlayersOnServerS", this, SingeplayerExecutionType.Server );
    }
	
	private PlayerBase getPlayer(PlayerIdentity sender) {
		GetGame().GetPlayers(players);
		player = FalconUtils.GetPlayer(sender.GetId(), players);
		
		return player;
	}
	
	private void turnGMS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				
				FalconLogger.logAction(sender.GetId(), "", "adminGM");
				
				player = getPlayer(sender);
				
				player.setHasGm(!player.getHasGm());
			}
        }
    }
	
	void turnGM() {
		GetRPCManager().SendRPC( "Falcon", "turnGMS", new Param1<string>("") );
	}
	
	private void healS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				player = getPlayer(sender);
				
				heal(player);
			}
        }
    }
	
	void selfHeal() {
		GetRPCManager().SendRPC( "Falcon", "healS", new Param1<string>("") );
	}
	
	private void kysS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				player = getPlayer(sender);
				
				player.SetHealth(0);
			}
        }
    }
	
	void kys() {
		GetRPCManager().SendRPC( "Falcon", "kysS", new Param1<string>("") );
	}
	
	private void safeS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				player = getPlayer(sender);
				
				string vecto = "2500" + " " + "200" + " " + "2500";
				vector vec = vecto.ToVector();
				
				player.SetPosition(vec);
			}
        }
    }
	
	void safe() {
		GetRPCManager().SendRPC( "Falcon", "safeS", new Param1<string>("") );
	}
	
	private void admS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				player = getPlayer(sender);
				
				EntityAI weapon = player.GetHumanInventory().CreateInHands("M4A1");
					
				weapon.GetInventory().CreateAttachment("M4_OEBttstck");
				weapon.GetInventory().CreateAttachment("M4_CarryHandleOptic");
				weapon.GetInventory().CreateAttachment("M4_PlasticHndgrd");
				player.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			}
        }
    }
	
	void adm() {
		GetRPCManager().SendRPC( "Falcon", "admS", new Param1<string>("") );
	}
	
	private void carS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				Car vehicle;
				player = getPlayer(sender);
				
				vehicle = Car.Cast(GetGame().CreateObject("OffroadHatchback", player.GetPosition()));
				vehicle.Fill(CarFluid.FUEL, 1000);
				vehicle.GetInventory().CreateAttachment("HatchbackTrunk");
				vehicle.GetInventory().CreateAttachment("HatchbackHood");
				vehicle.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
				vehicle.GetInventory().CreateAttachment("HatchbackDoors_Driver");
				vehicle.GetInventory().CreateAttachment("HatchbackWheel");
				vehicle.GetInventory().CreateAttachment("HatchbackWheel");
				vehicle.GetInventory().CreateAttachment("HatchbackWheel");
				vehicle.GetInventory().CreateAttachment("HatchbackWheel");
				vehicle.GetInventory().CreateAttachment("CarBattery");
				vehicle.GetInventory().CreateAttachment("SparkPlug");
				vehicle.GetInventory().CreateAttachment("CarRadiator");
				vehicle.Fill(CarFluid.COOLANT, 1000);
			}
        }
    }
	
	void car() {
		GetRPCManager().SendRPC( "Falcon", "carS", new Param1<string>("") );
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
		GetRPCManager().SendRPC( "Falcon", "changeTimeS", new Param1<string>(time) );
	}
	
	private void tpToPosS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< vector > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				FalconLogger.logAction(sender.GetId(), data.param1.ToString(), "adminTP");
				player = getPlayer(sender);
				player.SetPosition(data.param1);
			}
        }
    }
	
	void tpToPos(vector pos) {
		GetRPCManager().SendRPC( "Falcon", "tpToPosS", new Param1<vector>(pos) );
	}
	
	private void setPosS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< vector > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Server ) {
			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				FalconLogger.logAction(sender.GetId(), data.param1.ToString(), "adminTP");
				player = getPlayer(sender);
				player.SetPosition(data.param1);
			}
        }
    }
	
	void setPos(vector pos) {
		GetRPCManager().SendRPC( "Falcon", "setPosS", new Param1<vector>(pos) );
	}
	
	private void spawnItemS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {

			if (FalconUtils.IsPlayerAnAdmin(sender.GetId())) {
				player = getPlayer(sender);
				
				GetGame().CreateObject(data.param1, player.GetPosition(), false, true );
				
				FalconLogger.logAction(sender.GetId(), data.param1, "adminSpawnedItem");
			}
        }
    }
	
	void spawnItem(string item) {
		GetRPCManager().SendRPC( "Falcon", "spawnItemS", new Param1<string>(item) );
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
					
					string targetPName = targetP.GetIdentity().GetName();
					
					GetRPCManager().SendRPC("Falcon", "getTargetPlayerC", new Param1<string>(targetPName));
					GetRPCManager().SendRPC("Falcon", "getTargetPlayerHealthC", new Param1<string>(targetP.GetHealth().ToString()));
					GetRPCManager().SendRPC("Falcon", "getTargetPlayerPosC", new Param1<vector>(targetP.GetPosition()));
				}
			}
       	 }
    }
	
	void getTargetPlayer(string targetPlayer) {	
		GetRPCManager().SendRPC( "Falcon", "getTargetPlayerS", new Param1<string>(targetPlayer) );
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
		GetRPCManager().SendRPC( "Falcon", "tpToMeS", new Param1<string>(targetPlayer) );
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
		GetRPCManager().SendRPC( "Falcon", "freezeTargetS", new Param1<string>(targetPlayer) );
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
					
					FalconLogger.logAction(sender.GetId(), targetP.GetPosition().ToString(), "adminTP");
				}
			}
       	 }
    }
	
	void tpToTarget(string targetPlayer) {	
		GetRPCManager().SendRPC( "Falcon", "tpToTargetS", new Param1<string>(targetPlayer) );
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
		GetRPCManager().SendRPC( "Falcon", "healTargetS", new Param1<string>(targetPlayer) );
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
					
					FalconLogger.logAction(sender.GetId(), targetP.GetIdentity().GetName(), "adminKillPlayer");
				}
			}
       	 }
    }
	
	void killTarget(string targetPlayer) {	
		GetRPCManager().SendRPC( "Falcon", "killTargetS", new Param1<string>(targetPlayer) );
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
				
				foreach (Man player: players) {
					playersNames.Insert(player.GetIdentity().GetName());
				}	
				GetRPCManager().SendRPC( "Falcon", "setPlayersListC", new Param1<array<string>>(playersNames) );
			}
       	 }
    }
	
	void setPlayersList() {	
		GetRPCManager().SendRPC( "Falcon", "setPlayersListS", new Param1<string>("") );
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
				
				GetRPCManager().SendRPC( "Falcon", "setPlayersOnServerC", new Param1<int>(playersCount) );
			}
       	 }
    }
	
	void setPlayersOnServer() {	
		GetRPCManager().SendRPC( "Falcon", "setPlayersOnServerS", new Param1<string>("") );
	}
	
	///TODO: Move utils to another file ?
	private void heal(PlayerBase player) {
		player.SetHealth(player.GetMaxHealth("", ""));
		player.SetHealth("", "Blood", player.GetMaxHealth("", "Blood"));
		player.GetStatStamina().Set(1000);
		player.GetStatEnergy().Set(player.GetStatWater().GetMax());
		player.GetStatWater().Set(player.GetStatWater().GetMax());
	}
	///
}