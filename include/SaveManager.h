#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

class SaveManager {
public:
    static std::string getSlotPath(int slot);
    static bool slotExists(int slot);
    static void deleteSlot(int slot);
    static std::vector<int> listAvailableSlots();
    static void ensureSaveDirectoryExists();
};
