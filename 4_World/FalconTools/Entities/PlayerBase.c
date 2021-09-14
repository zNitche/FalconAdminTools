modded class PlayerBase
{
	private bool hasGM = false;
	private bool isFreezed = false;
	private bool areBindsOn = false;
	private bool isInv = false;
	
	private const int INV_FLAGS = EntityFlags.VISIBLE|EntityFlags.SOLID|EntityFlags.ACTIVE;
	
	bool getHasGm() {
		return hasGM;
	}
	
	void setHasGm(bool state) {
		hasGM = state;
		SetAllowDamage(!state);
	}
	
	bool getIsInv() {
		return isInv;
	}
	
	void setIsInv(bool state) {
		if (isInv)
		{
			SetFlags(INV_FLAGS, true);
			dBodySetInteractionLayer(this, PhxInteractionLayers.CHARACTER);
		}
		else
		{
			ClearFlags(INV_FLAGS, true);
			dBodySetInteractionLayer(this, PhxInteractionLayers.CHARACTER);
		}
		
		isInv = state;
	}
	
	bool getAreBindsOn() {
		return areBindsOn;
	}
	
	void setAreBindsOn(bool state) {
		areBindsOn = state;
	}
	
	bool getIsFreezed() {
		return isFreezed;
	}
	
	void setIsFreezed(bool state) {
		isFreezed = state;
	}
	
	override void OnConnect()
	{
		super.OnConnect();
		
		FalconPlayerTelemetryLogger.logPlayer(GetIdentity().GetName(), GetIdentity().GetId());
	}
	
	override void OnDisconnect() 
	{
		string playerId = GetIdentity().GetId();
		string playerPos = GetPosition().ToString();
		string playerHealth = GetHealth().ToString();
		
		FalconPlayerTelemetryLogger.logPlayerLogoutLocation(playerId, playerPos);
		FalconPlayerTelemetryLogger.logPlayerLogoutHealth(playerId, playerHealth);
		
		super.OnDisconnect();
	}
}