#include <solanaceae/plugin/solana_plugin_v1.h>

#include <solanaceae/clamav/clamav_module.hpp>
#include <solanaceae/util/config_model.hpp>

#include <memory>
#include <limits>
#include <iostream>

static std::unique_ptr<ClamAVModule> g_cavm = nullptr;

constexpr const char* plugin_name = "ClamAVModule";

extern "C" {

SOLANA_PLUGIN_EXPORT const char* solana_plugin_get_name(void) {
	return plugin_name;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_get_version(void) {
	return SOLANA_PLUGIN_VERSION;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_start(struct SolanaAPI* solana_api) {
	std::cout << "PLUGIN " << plugin_name << " START()\n";

	if (solana_api == nullptr) {
		return 1;
	}

	try {
		auto* conf = PLUG_RESOLVE_INSTANCE(ConfigModelI);

		// static store, could be anywhere tho
		// construct with fetched dependencies
		g_cavm = std::make_unique<ClamAVModule>(*conf);

		// register types
		PLUG_PROVIDE_INSTANCE(ClamAVModule, plugin_name, g_cavm.get());
	} catch (const ResolveException& e) {
		std::cerr << "PLUGIN " << plugin_name << " " << e.what << "\n";
		return 2;
	}

	return 0;
}

SOLANA_PLUGIN_EXPORT void solana_plugin_stop(void) {
	std::cout << "PLUGIN " << plugin_name << " STOP()\n";

	g_cavm.reset();
}

SOLANA_PLUGIN_EXPORT float solana_plugin_tick(float delta) {
	(void)delta;
	//std::cout << "PLUGIN CAVM TICK()\n";
	//g_cavm->iterate();
	return std::numeric_limits<float>::max();
}

} // extern C

