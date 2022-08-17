#include "include/tac.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Please specify input file.\n");
		return 1;
	}

	tac_compile_file(argv[1]);

	return 0;
}

// 29;00 min in parsing part

// echo  "'$USER'"    -n "wqdqwd        " | exit 5 | ls    ccccbffbd          morisse chifrage

//  pour chek segmentatoin fault    valgrind

// main = (argc: int, argv: array<string>):int => {
// 	return 0;
// }