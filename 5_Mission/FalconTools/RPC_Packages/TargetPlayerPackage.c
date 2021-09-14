class TargetPlayerPackage
{
	string playerName;
	string playerHealth;
	vector playerPos;
	string playerIdentity;
	
	void TargetPlayerPackage(string playerName, string playerHealth, vector playerPos, string playerIdentity)
	{
		this.playerName = playerName;
		this.playerHealth = playerHealth;
		this.playerPos = playerPos;
		this.playerIdentity = playerIdentity;
	}
}