modded class MissionServer
{ 	
	ref FalconAuthenticator auth;
	ref FalconToolsV2 FalconToolsv2;
	ref PlayerMonitorBack MonitorBack;

    void MissionServer()
    {
        auth = new ref FalconAuthenticator();
		FalconToolsv2 = new ref FalconToolsV2();
		MonitorBack = new ref PlayerMonitorBack();
    }
}