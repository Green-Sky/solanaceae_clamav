#pragma once

#include <string_view>
#include <string>
#include <future>

// blocking
struct ClamAVModuleInterface {

	struct ScanResult {
		bool virus {false};
		std::string resultText;
	};
	virtual ScanResult scanFilePath(std::string_view path) = 0;

};

// non-blocking
struct ClamAVModuleAsyncInterface {
	using ScanResult = ClamAVModuleInterface::ScanResult;

	virtual std::promise<ScanResult> scanFilePath(std::string_view path) = 0;

};

