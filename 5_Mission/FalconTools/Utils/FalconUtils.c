class FalconUtils 
{
	const static string adminsJson = "$profile:/FT/admins.json"; 
	
	///Left for compatibility
	static PlayerBase GetPlayer(string id, array<Man> players) {
		
		foreach(Man p : players) {
            if(p.GetIdentity().GetId() == id) {
				return PlayerBase.Cast(p);
			}
		}
		return NULL;
    }
	///
	
	static PlayerBase GetPlayerByName(string name) {
		ref array<Man> players = new array<Man>;
		
		GetGame().GetPlayers(players);
		
		foreach(Man p : players) {
            if(p.GetIdentity().GetName() == name) {
				return PlayerBase.Cast(p);
			}
		}
		return NULL;
    }
	
	static PlayerBase GetPlayerById(string id) {
		ref array<Man> players = new array<Man>;
		
		GetGame().GetPlayers(players);
		
		foreach(Man p : players) {
            if(p.GetIdentity().GetName() == id) {
				return PlayerBase.Cast(p);
			}
		}
		return NULL;
    }
	
	static array<Man> getPlayers() {
		array<Man> players;
		GetGame().GetPlayers(players);

		return players;
	}	
	
	static bool IsPlayerAnAdmin(string userID) {
        array<string> adminGuids = new array<string>();
		
		if (FileExist(adminsJson)) {
			
			JsonFileLoader<array<string>>.JsonLoadFile(adminsJson, adminGuids);
					
			foreach (string guid : adminGuids) {
				if (guid == userID) {
					return true;
				}
			}
			return false;
		}
		else {
			FalconLogger.logAdminFileMissing();
			return false;
		}
    }
}