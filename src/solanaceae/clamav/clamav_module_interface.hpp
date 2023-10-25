#pragma once

#include <string_view>
#include <string>

// blocking
struct ClamAVModuleInterface {

	struct ScanResult {
		bool virus {false};
		std::string resultText;
	};
	virtual ScanResult scanFilePath(std::string_view path) = 0;

};

