#include "config.hpp"
#include "MacroConst.hpp"

using namespace Constants;

Config::Config(const std::string &directory)
{
    // Ensure the directory exists
    std::filesystem::create_directories(directory);

    // Construct the full file path
    FilePath = directory + ConfigMacro::Paths::CONFIG_FILE_PATH;

    LoadConfig();
}

Config::~Config()
{
}

void Config::LoadConfig()
{
    std::ifstream configFile(FilePath);
    if (configFile.is_open())
    {
        std::string line;
        bool isEmpty = true;
        while (std::getline(configFile, line))
        {
            isEmpty = false;
            size_t delimiterPos = line.find("=");
            std::string name = line.substr(0, delimiterPos);
            int value = std::stoi(line.substr(delimiterPos + 1));

            if (name == "volume")
                volume = value;
            else if (name == "difficulty")
                difficulty = value;
            else if (name == "resolution")
                resolution = value;
            else if (name == "fullscreen")
                fullscreen = value;
            else if (name == "sensitivity")
                sensitivity = value;
        }
        configFile.close();

        if (isEmpty)
        {
            std::cerr << "Config file is empty. Creating default config file." << std::endl;
            LoadDefaultConfig();
            SaveConfig();
        }
    }
    else
    {
        std::cerr << "Config file not found. Creating default config file." << std::endl;
        LoadDefaultConfig();
        SaveConfig();
    }
}

void Config::LoadDefaultConfig()
{
    volume = 50;
    difficulty = 1;
    resolution = 1;
    fullscreen = 100;
    sensitivity = 50;
}

void Config::SaveConfig()
{
    std::ofstream configFile(FilePath);
    if (configFile.is_open())
    {
        configFile << "volume=" << volume << std::endl;
        configFile << "difficulty=" << difficulty << std::endl;
        configFile << "resolution=" << resolution << std::endl;
        configFile << "fullscreen=" << fullscreen << std::endl;
        configFile << "sensitivity=" << sensitivity << std::endl;
        configFile.close();
    }
    else
    {
        std::cerr << "Unable to open config file for writing." << std::endl;
    }
}