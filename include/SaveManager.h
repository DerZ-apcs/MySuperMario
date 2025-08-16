#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "json.hpp"
using json = nlohmann::json;

class SaveManager {
public:
    static std::string getSlotPath(int slot);
    static bool slotExists(int slot);
    static void deleteSlot(int slot);
    static std::vector<int> listAvailableSlots();
    static void ensureSaveDirectoryExists();
    static int findNextFreeSlot(int maxSlots = 5);
private:
    static void cleanupInvalidFiles();
};

