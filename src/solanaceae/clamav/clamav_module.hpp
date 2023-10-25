#pragma once

#include "./clamav_module_interface.hpp"

extern "C" {
	struct cl_engine;
}

// blocking
class ClamAVModule : public ClamAVModuleInterface {
	cl_engine* _clamav_engine {nullptr};

	bool startEngine(void);

	public:
		ClamAVModule(void);
		~ClamAVModule(void);

		ScanResult scanFilePath(std::string_view path);

};

