#include "main.h"
#include "sys.h"
#include "sfml.h"
#include "argss.h"

int main(int argc, char **argv)
{
    Init_Sys();
    Init_SFML();
    Init_ARGSS();
	return 0;
}
