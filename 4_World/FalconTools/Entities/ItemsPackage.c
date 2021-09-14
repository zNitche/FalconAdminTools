class ItemsPackage
{
	private string name;
	private ref array<ref ItemInPackage> items = new array<ref ItemInPackage>();
	
	string getName()
	{
		return name;
	}
	
	array<ref ItemInPackage> getItems()
	{
		return items;
	}
}