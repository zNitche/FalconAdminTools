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
		
		if (FileExist(adminsJson)) 
		{
			JsonFileLoader<array<string>>.JsonLoadFile(adminsJson, adminGuids);
					
			foreach (string guid : adminGuids) {
				if (guid == userID) {
					return true;
				}
			}
		}
		
		return false;
    }
	
	static vector getCameraPosition()
	{
		vector from = FreeDebugCamera.GetInstance().GetPosition(); 
		vector to = from + ( Vector(0,-1,0) * 10000 );   
		vector contact_pos;   
		vector contact_dir;   
		int contact_component; 
		
		vector outVector;
		
		if ( DayZPhysics.RaycastRV(from, to, contact_pos, contact_dir, contact_component) )   
		{
			outVector = contact_pos;
		}
		else
		{
			outVector = vector.Zero;
		}
		
		return outVector;
	}
	
	static void spawnAdminLoadout(PlayerBase player)
	{
		EntityAI weapon = player.GetHumanInventory().CreateInHands("M4A1");
					
		weapon.GetInventory().CreateAttachment("M4_OEBttstck");
		weapon.GetInventory().CreateAttachment("M4_CarryHandleOptic");
		weapon.GetInventory().CreateAttachment("M4_PlasticHndgrd");
		player.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
	}
	
	static void spawnVehicle(string vehicleName, vector position)
	{
		if (vehicleName == "OffroadHatchback")
		{
			Car carVehicle;

			carVehicle = Car.Cast(GetGame().CreateObject("OffroadHatchback", position));
			
			carVehicle.GetInventory().CreateAttachment("HatchbackTrunk");
			carVehicle.GetInventory().CreateAttachment("HatchbackHood");
			carVehicle.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
			carVehicle.GetInventory().CreateAttachment("HatchbackDoors_Driver");
			carVehicle.GetInventory().CreateAttachment("HatchbackWheel");
			carVehicle.GetInventory().CreateAttachment("HatchbackWheel");
			carVehicle.GetInventory().CreateAttachment("HatchbackWheel");
			carVehicle.GetInventory().CreateAttachment("HatchbackWheel");
			
			carVehicle.GetInventory().CreateAttachment("CarBattery");
			carVehicle.GetInventory().CreateAttachment("SparkPlug");
			carVehicle.GetInventory().CreateAttachment("CarRadiator");
			
			carVehicle.Fill(CarFluid.FUEL, 1000);
			carVehicle.Fill(CarFluid.COOLANT, 1000);
		}
		
		else if (vehicleName == "Truck_01_Covered")
		{
			Truck_01_Base truckVehicle;
			
			truckVehicle = Truck_01_Base.Cast(GetGame().CreateObject("Truck_01_Covered", position));
			
			truckVehicle.GetInventory().CreateAttachment("Truck_01_Wheel");
			truckVehicle.GetInventory().CreateAttachment("Truck_01_Wheel");
			
			truckVehicle.GetInventory().CreateAttachment("Truck_01_WheelDouble");
			truckVehicle.GetInventory().CreateAttachment("Truck_01_WheelDouble");
			truckVehicle.GetInventory().CreateAttachment("Truck_01_WheelDouble");
			truckVehicle.GetInventory().CreateAttachment("Truck_01_WheelDouble");

			truckVehicle.GetInventory().CreateAttachment("TruckBattery");
			truckVehicle.GetInventory().CreateAttachment("GlowPlug");
			truckVehicle.GetInventory().CreateAttachment("CarRadiator");
			
			truckVehicle.GetInventory().CreateAttachment("Truck_01_Door_1_1");
			truckVehicle.GetInventory().CreateAttachment("Truck_01_Door_2_1");
			truckVehicle.GetInventory().CreateAttachment("Truck_01_Hood");

			truckVehicle.GetInventory().CreateAttachment("HeadlightH7");
			truckVehicle.GetInventory().CreateAttachment("HeadlightH7");

			truckVehicle.Fill(CarFluid.FUEL, 120);
			truckVehicle.Fill(CarFluid.OIL, 4.0);
		}
	}
}