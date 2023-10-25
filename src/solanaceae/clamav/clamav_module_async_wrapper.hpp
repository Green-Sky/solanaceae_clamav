#pragma once

#include "./clamav_module_async_interface.hpp"

#include <mutex>

class ClamAVModuleAsyncWrapper : public ClamAVModuleAsyncInterface {
	ClamAVModuleInterface& _cavmi;
	std::mutex _cavmi_mutex;

	public:

		ClamAVModuleAsyncWrapper(ClamAVModuleInterface& cavmi);

		std::future<ScanResult> scanFilePath(std::string_view path) override;

};

