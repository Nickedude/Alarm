#include "include/camera.h"

uint32_t Record10Sec (void)
{
	uint32_t returncode = system("raspivid -t 10000 -o testvid.h264");
	return returncode;
}
