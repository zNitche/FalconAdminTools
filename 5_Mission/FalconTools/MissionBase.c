modded class MissionBase {
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            switch (id) {
            	case 2138597: {
                	menu = new FalconMonitor;
                	break;
				}
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}