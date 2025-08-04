#include "../include/SaveManager.h"

std::string SaveManager::getSlotPath(int slot) {
    return "saves/save_slot_" + std::to_string(slot) + ".json";
}

bool SaveManager::slotExists(int slot) {
    std::ifstream f(getSlotPath(slot));
    return f.good();
}

void SaveManager::deleteSlot(int slot) {
    std::remove(getSlotPath(slot).c_str());
}

std::vector<int> SaveManager::listAvailableSlots() {
    std::vector<int> available;
    for (int i = 1; i <= 3; ++i) {
        if (slotExists(i)) available.push_back(i);
    }
    return available;
}

void SaveManager::ensureSaveDirectoryExists() {
    std::filesystem::create_directories("saves");
}
