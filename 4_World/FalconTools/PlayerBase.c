modded class PlayerBase
{
	private bool hasGM = false;
	private bool isFreezed = false;
	private bool areBindsOn = false;
	
	bool getHasGm() {
		return hasGM;
	}
	
	void setHasGm(bool state) {
		hasGM = state;
		SetAllowDamage(!state);
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
		
		Man thisMan = this;
		
		FalconPlayerTelemetryLogger.logPlayer(thisMan.GetIdentity().GetName(), thisMan.GetIdentity().GetId());
	}
	
	override void OnDisconnect() 
	{
		// Gives NullPointer Exception, IDK why
		Man thisMan = this;
		
		FalconPlayerTelemetryLogger.logPlayerLogoutLocation(thisMan.GetIdentity().GetId(), thisMan.GetPosition().ToString());
		FalconPlayerTelemetryLogger.logPlayerLogoutHealth(thisMan.GetIdentity().GetId(), thisMan.GetHealth().ToString());
		
		super.OnDisconnect();
	}
}