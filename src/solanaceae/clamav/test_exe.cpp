#include "./clamav_module.hpp"

#include <iostream>

int main(void) {

	ClamAVModule clamav;

	auto [is_virus, virus_string] = clamav.scanFilePath("/home/green/Downloads/mal/f8c08d00ff6e8c6adb1a93cd133b19302d0b651afd73ccb54e3b6ac6c60d99c6");
	if (is_virus) {
		std::cout << "is virus: " << virus_string << "\n";
	} else {
		std::cout << "not virus: " << virus_string << "\n";
	}

	return 0;
}

