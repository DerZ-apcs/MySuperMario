#include "../include/SaveManager.h"
#include <iostream>
namespace fs = std::filesystem;

const std::string SAVE_DIR = "resources/maps/saves";
const std::string SLOT_PREFIX = "slot";
const std::string slot_extension = ".json";

std::string SaveManager::getSlotPath(int slot) {
    return SAVE_DIR + "/" + SLOT_PREFIX + std::to_string(slot) + slot_extension;
}

bool SaveManager::slotExists(int slot) {
    return fs::exists(getSlotPath(slot));
}

void SaveManager::deleteSlot(int slot) {
    std::string path = getSlotPath(slot);
    if (fs::exists(path))
        fs::remove(path);
}

std::vector<int> SaveManager::listAvailableSlots() {
    std::vector<int> slots;
    ensureSaveDirectoryExists();

    for (const auto& entry : fs::directory_iterator(SAVE_DIR)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();

            // Expect filenames like "slot3.json"
            if (filename.rfind(SLOT_PREFIX, 0) == 0 && filename.size() >= slot_extension.size() &&
                filename.compare(filename.size() - slot_extension.size(), slot_extension.size(), slot_extension) == 0
                ) {
                std::string numberStr = filename.substr(SLOT_PREFIX.size(), filename.size() - SLOT_PREFIX.size() - slot_extension.size());
                try {
                    int slotNum = std::stoi(numberStr);
                    slots.push_back(slotNum);
                }
                catch (...) {
                    // Ignore malformed filenames
                }
            }
        }
    }

    return slots;
}

void SaveManager::ensureSaveDirectoryExists() {
    if (!fs::exists(SAVE_DIR))
        fs::create_directory(SAVE_DIR);
}
