#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

//@brief Configuration class for storing game settings
class Config
{
public:
    int volume;
    int difficulty;
    int resolution;
    int fullscreen;
    int sensitivity;
    std::string FilePath;

    Config(const std::string &directory);
    ~Config();
    void SaveConfig();
    void LoadConfig();
    void LoadDefaultConfig();
    void SetVolume(int volume);
    void SetDifficulty(int difficulty);
    void SetResolution(int resolution);
    void SetFullscreen(int fullscreen);
};

#endif //__CONFIG_HPP__