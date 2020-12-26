#include "lib/nix/nix.h"
#include "lib/xhui/xhui.h"
#include <stdio.h>

#include <unistd.h>

int main() {

	hui::init();

	auto w = new hui::Window("test", 1024, 768);
	hui::run();

	delete w;


	return 0;
}

