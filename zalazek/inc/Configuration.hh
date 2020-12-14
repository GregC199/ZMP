#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include <string>

struct sceneElementConfig
{
  std::string Name;
  std::string Size;
  std::string Color;
};

class Configuration {
public:
	std::vector<std::string> libsConfig{};
	std::vector<sceneElementConfig> sceneConfig{};
};

#endif
