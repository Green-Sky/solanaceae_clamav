#include <clamav.h>

#include <iostream>

int main(void) {
	if (cl_init(CL_INIT_DEFAULT) != CL_SUCCESS) {
		return 1;
	}

	auto* clamav_engine = cl_engine_new();
	if (clamav_engine == nullptr) {
		return 2;
	}

	std::string db_dir;
	// TODO: load from config

	unsigned int signo = 0;

	if (db_dir.empty()) {
		std::cout << "default db dir: " << cl_retdbdir() << "\n";
		if (cl_load(cl_retdbdir(), clamav_engine, &signo, CL_DB_STDOPT) != CL_SUCCESS) {
			std::cerr << "default db dir load failed, falling back to '/var/lib/clamav'\n";
			if (cl_load("/var/lib/clamav", clamav_engine, &signo, CL_DB_STDOPT) != CL_SUCCESS) {
				std::cerr << "db dir load failed, exiting\n";
				return 3;
			} else {
				db_dir = "/var/lib/clamav";
			}
		} else {
			db_dir = cl_retdbdir();
		}
		// if db_dir changed, save to config?
	} else {
		if (cl_load(db_dir.c_str(), clamav_engine, &signo, CL_DB_STDOPT) != CL_SUCCESS) {
			std::cerr << "config db dir load failed, exiting (" << db_dir << ")\n";
			return 3;
		}
	}

	std::cout << "signatures loaded: " << signo << "\n";

	if (cl_engine_compile(clamav_engine) != CL_SUCCESS) {
		cl_engine_free(clamav_engine);
		return 4;
	}

	// TODO: database update watcher

	const char* filename = "~/Downloads/cubic-paper.pdf";
	const char* virname = nullptr;
	unsigned long int scanned = 0;

	struct cl_scan_options scan_opts {
		/*CL_SCAN_GENERAL_ALLMATCHES |*/ CL_SCAN_GENERAL_HEURISTICS | CL_SCAN_GENERAL_HEURISTIC_PRECEDENCE,
		~0u,
		~0u,
		0u,
		0u
	};

	if (auto ret = cl_scanfile(
		filename,
		&virname,
		&scanned,
		clamav_engine,
		&scan_opts
	); ret != CL_CLEAN && ret != CL_VIRUS) {
		// error
	} else if (ret == CL_VIRUS) {
		std::cout << "file virus\n";
	} else { // clean
		std::cout << "file clean\n";
	}

	cl_engine_free(clamav_engine);
	return 0;
}

