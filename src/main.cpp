#include "main.h"
#include "sys.h"
#include "argss_sdl.h"
#include "argss.h"

int main(int argc, char **argv)
{
    Init_Sys();
    Init_SDL();
    Init_ARGSS();
	
	return 0;
}
