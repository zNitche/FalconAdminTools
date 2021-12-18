class ESPHelper
{
	private string mode;
	private int radius;
	private bool isRunning;
	private ref array<Object> objects = new array<Object>();
	private ref array<ref ESPTrack> espTracks = new array<ref ESPTrack>();
	
	
	void ESPHelper(string mode, int range)
	{
		this.mode = mode;
		
		if (range > 0)
		{
			this.radius = range;
		}
	}
	
	bool getIsRunning()
	{
		return isRunning;
	}
	
	int getESPRange()
	{
		return radius;
	}
	
	void setESPRange(int value)
	{
		radius = value;
	}
	
	void disable()
	{
		if (isRunning)
		{
			isRunning = false;
			espTracks.Clear();
		}
	}
	
	void start()
	{
		if (!isRunning)
		{
			isRunning = true;
		}
	}
	
	void getTracks()
	{
		ESPTrack track;
		
		for (int i = 0; i < objects.Count(); i++)
		{
			if (objects[i])
			{
				if (objects[i].IsInherited(ItemBase) && mode == "objects")
				{
					espTracks.Insert(new ESPTrack(objects[i].GetPosition(), objects[i].GetType()));
				}
				
				else if (objects[i].IsInherited(PlayerBase) && mode == "players")
				{
					espTracks.Insert(new ESPTrack(objects[i].GetPosition(), PlayerBase.Cast(objects[i]).GetIdentity().GetName()));
				}
			}
		}
	}
	
	void activateTracks()
	{
		for (int i = 0; i < espTracks.Count(); i++)
		{
			espTracks[i].update();
		}
	}
	
	void update(vector pos)
	{
		if (isRunning)
		{
			objects.Clear();
			espTracks.Clear();
			
			getObjects(pos);
			getTracks();
			activateTracks();
		}
	}
	
	void getObjects(vector pos)
	{
		GetGame().GetObjectsAtPosition(pos, radius, objects, null);
	}
}