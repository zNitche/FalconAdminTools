class PlayerMonitorBack
{
	const private string playersHummanityPath = "$profile:/FH/";
	const static string hummanityValues = "$profile:/FValues/FHvalues.json";
	
	void PlayerMonitorBack()
	{
		GetRPCManager().AddRPC( "Falcon", "setHummanityS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "setHummanityLevelS", this, SingeplayerExecutionType.Server );
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
	
	private string getHummanityLevel(string playerID)
	{
		
		string playerJson = playersHummanityPath + playerID + ".json";
		
		if (FileExist(playerJson))
		{
			PlayerHummanityValues playerHummanityData = new PlayerHummanityValues();
			HummanityValues hummanityValuesData = new HummanityValues();
			
			JsonFileLoader<PlayerHummanityValues>.JsonLoadFile(playerJson, playerHummanityData);
			JsonFileLoader<HummanityValues>.JsonLoadFile(hummanityValues, hummanityValuesData);
			
			foreach (HummanityLevel level : hummanityValuesData.getHummanityLevels()) {
				Print(level.getName());
			}
			return "Survivor";
		}
		else
		{
			return "Survivor";
		}
	}
	
	private void setHummanityS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			
			map<string, int> playerData = loadPlayerData(playerID);
			
			int hummanity = playerData.Get("hummanity");
			
			GetRPCManager().SendRPC( "Falcon", "setHummanityC", new Param1<int>(hummanity) );
       	 }
    }
	
	void setPlayerHummanity() {		
		GetRPCManager().SendRPC( "Falcon", "setHummanityS", new Param1<string>("") );
	}
	
	private void setHummanityLevelS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			string playerID = sender.GetId();
			
			string hummanityLevel = getHummanityLevel(playerID);
			
			GetRPCManager().SendRPC( "Falcon", "setHummanityLevelC", new Param1<string>(hummanityLevel) );
       	 }
    }
	
	void setPlayerHummanityLevel() {		
		GetRPCManager().SendRPC( "Falcon", "setHummanityLevelS", new Param1<string>("") );
	}
}