class ESPTrack
{
	private Widget widgetRoot;
	private TextWidget distanceTEXT;
	private TextWidget nameTEXT;
	private Widget espFramePANEL;
	private vector screenPos;
	private vector targetPos;
	
	private bool isTrackOn = false;
	
	//Constructor
	void ESPTrack(vector targetPos, string targetName) 
	{		
		widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconTools/GUI/Layouts/ESPTrack.layout");
		espFramePANEL = Widget.Cast(widgetRoot.FindAnyWidget("ESPFramePANEL"));
		distanceTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("DistanceTEXT"));
		nameTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("NameTEXT"));
		
		widgetRoot.Show(false);
		
		screenPos = GetGame().GetScreenPos(targetPos);
		this.targetPos = targetPos;
		
		setPosition(screenPos);
		setDistance(this.targetPos);
		setName(targetName);
	}
	
	//Deconstructor
	void ~ESPTrack() 
	{
        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	bool getIsTrackOn()
	{
		return isTrackOn;
	}
	
	void setIsTrackOn(bool value) 
	{
		isTrackOn = value;
	}
	
	void showTrack() 
	{
		if (!isTrackOn)
		{
			widgetRoot.Show(true);
			setIsTrackOn(true);
		}
	}
	
	void hideTrack() 
	{
		if (isTrackOn)
		{
			widgetRoot.Show(false);
			setIsTrackOn(false);
		}
	}
	
	void setPosition(vector targetPos)
	{
		espFramePANEL.SetPos(Math.Ceil(targetPos[0]), Math.Ceil(targetPos[1]));
	}
	
	void setDistance(vector targetPos)
	{
		distanceTEXT.SetText(vector.Distance(GetGame().GetPlayer().GetPosition(), targetPos).ToString());
	}
	
	void setName(string name)
	{
		nameTEXT.SetText(name);
	}
	
	void checkVisibility()
	{
		vector screenPosRelative = GetGame().GetScreenPosRelative(targetPos);
			
        if (screenPosRelative[0] >= 1 || screenPosRelative[0] == 0 || screenPosRelative[1] >= 1 || screenPosRelative[1] == 0) 
		{
            hideTrack();
       	} 
	
		else if (screenPosRelative[2] < 0) 
		{
            hideTrack();
        }
	 
		else 
		{
	        showTrack();
        }
	}
	
	void update()
	{
		checkVisibility();
	}
}
	
	
