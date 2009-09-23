#include "sfml.h"
#include "sys.h"

void Init_SFML() {
    sf::WindowSettings Settings;
    Settings.DepthBits = 24;
    Settings.StencilBits = 8;
    Settings.AntialiasingLevel = 0;
	SFML_Window.Create(sf::VideoMode(Sys_Res[0], Sys_Res[1], Sys_Res[2]),
        Sys_Title, sf::Style::Close, Settings);
    SFML_Window.PreserveOpenGLStates(false);
	SFML_Window.Clear();
	SFML_Window.SetFramerateLimit(0);
	SFML_Window.UseVerticalSync(false);
	SFML_Window.Display();
	SFML_Clock.Reset();
	//SFML_Input = SFML_Window.GetInput();
}
