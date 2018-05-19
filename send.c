#include <stdio.h>
#include "connect.h"

int main(int argc, char* argv[])
{
	startClient(2777, "127.0.0.1");
	return 0;
}
