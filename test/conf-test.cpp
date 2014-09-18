#include <iostream>
#include <libconfig.h++>

int main()
{
	libconfig::Config cfg;
	try {
		cfg.readFile("../assets/entities/player.conf");
	} catch (const libconfig::FileIOException& ioe) {
		std::cerr << "Unable to read file." << std::endl;
		return -1;
	} catch (const libconfig::ParseException& pe) {
		std::cerr << "Parse error at " << pe.getFile() << ":" << pe.getLine() << " - " << pe.getError() << std::endl;
		return -2;
	}

	try {
		const libconfig::Setting& dir_ani = cfg.lookup("animation.direction");
		std::cout << static_cast<int>(dir_ani["south"][0][0]) << std::endl;
	} catch (const libconfig::SettingNotFoundException& snfe) {
		std::cerr << "Setting not found: " << snfe.getPath() << std::endl;
	}
	return 0;
}
