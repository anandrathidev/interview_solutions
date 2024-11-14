#include <iostream>
#include <map>
#include <string>

class ConfigManager
{
    
    ConfigManager() {}
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    ConfigManager( ConfigManager&&) = delete;
    ConfigManager& operator=( ConfigManager&&) = delete;
        
    // std::unique_ptr<ConfigManager>  mConfigManager  = nullptr;
    public:
    
    std::map<std::string, std::string> mConfig;
    static ConfigManager& getInstance()
    {
        static ConfigManager mObj; // thread safe as per ISO C++ std 
        return mObj;
    }
    
    ~ConfigManager() = default;
};



int main()
{
    
    ConfigManager& conf1 = ConfigManager::getInstance();
    conf1.mConfig["path"] = "/tmp";
    
    ConfigManager& conf2 = ConfigManager::getInstance();

    std::cout<<"Path=" << conf2.mConfig["path"] << std::endl;

    return 0;
}
