modded class PlayerBase
{
	private bool hasGM;
	private bool isFreezed;
	
	bool getHasGm() {
		return hasGM;
	}
	
	void setHasGm(bool state) {
		hasGM = state;
		SetAllowDamage(!state);
	}
	
	bool getIsFreezed() {
		return isFreezed;
	}
	
	void setIsFreezed(bool state) {
		isFreezed = state;
	}
}