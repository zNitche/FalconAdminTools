class FalconPlayerTelemetryLogger
{
	const static string playersListRoot = "$profile:/FTelemetry/";
	
	static void logPlayer(string playerName, string playerID) 
	{
		string playerJson = playersListRoot + playerID + ".json";
		
		map<string, string> playerData = new map<string, string>();
		
		if (FileExist(playerJson))
		{
			JsonFileLoader<map<string, string>>.JsonLoadFile(playerJson, playerData);
			
			playerData.Set("Name", playerName);
			
			JsonFileLoader<map<string, string>>.JsonSaveFile(playerJson, playerData);
		}
		else 
		{
			playerData.Set("Name", playerName);
			
			JsonFileLoader<map<string, string>>.JsonSaveFile(playerJson, playerData);
		}
	}
	
	static void logPlayerLogoutLocation(string playerID, string location)
	{
		string playerJson = playersListRoot + playerID + ".json";
				
		map<string, string> playerData = new map<string, string>();
		
		if (FileExist(playerJson))
		{
			JsonFileLoader<map<string, string>>.JsonLoadFile(playerJson, playerData);
			
			playerData.Set("DisconnectLocation", location);
			
			JsonFileLoader<map<string, string>>.JsonSaveFile(playerJson, playerData);
		}
		else 
		{
			playerData.Set("DisconnectLocation", location);
			
			JsonFileLoader<map<string, string>>.JsonSaveFile(playerJson, playerData);
		}
	}
	
	static void logPlayerLogoutHealth(string playerID, string playerHealth)
	{
		string playerJson = playersListRoot + playerID + ".json";
				
		map<string, string> playerData = new map<string, string>();
		
		if (FileExist(playerJson))
		{
			JsonFileLoader<map<string, string>>.JsonLoadFile(playerJson, playerData);
			
			playerData.Set("DisconnectHealth", playerHealth);
			
			JsonFileLoader<map<string, string>>.JsonSaveFile(playerJson, playerData);
		}
		else 
		{
			playerData.Set("DisconnectHealth", playerHealth);
			
			JsonFileLoader<map<string, string>>.JsonSaveFile(playerJson, playerData);
		}
	}
}