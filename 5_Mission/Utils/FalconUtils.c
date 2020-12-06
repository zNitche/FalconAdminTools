class FalconUtils 
{
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
        map<string, string> adminGuids = new map<string, string>();
		
		if (FileExist("$profile:/FT/admins.json")) {
			
			JsonFileLoader<map<string, string>>.JsonLoadFile("$profile:/FT/admins.json", adminGuids);
					
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