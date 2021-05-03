class PlayerMonitorBack
{
	const private string playersHummanityPath = "$profile:/FH/";
	
	void PlayerMonitorBack()
	{
		GetRPCManager().AddRPC( "Falcon", "setHummS", this, SingeplayerExecutionType.Server );
	}
	
	private map<string, int> loadPlayerData(string playerID)
	{
		map<string, int> playerData = new map<string, int>();
		string playerJson = playersHummanityPath + playerID + ".json";
		
		if (FileExist(playerJson))
		{
			JsonFileLoader<map<string, int>>.JsonLoadFile(playerJson, playerData);
		}
		
		return playerData;
	}
	
	private void setHummS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		Print("Intit3 set hum");
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			Print(playerID);
			
			map<string, int> playerData = loadPlayerData(playerID);
			
			Print(playerData.Get("Hummanity"));
			
			int hummanity = playerData.Get("Hummanity");
			
			GetRPCManager().SendRPC( "Falcon", "setHummC", new Param1<int>(hummanity) );
       	 }
    }
	
	void setPlayerHummanity() {
		Print("Intit2 set hum");		
		GetRPCManager().SendRPC( "Falcon", "setHummS", new Param1<string>("") );
	}
}