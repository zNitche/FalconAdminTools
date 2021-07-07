modded class MissionServer
{ 	
	ref FalconAuthenticator auth;
	ref FalconToolsV2 FalconToolsv2;

    void MissionServer()
    {
        auth = new ref FalconAuthenticator();
		FalconToolsv2 = new ref FalconToolsV2();
    }
}