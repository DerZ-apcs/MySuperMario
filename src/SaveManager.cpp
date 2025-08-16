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

    // Tự động dọn dẹp file rác trước
    cleanupInvalidFiles();

    for (const auto& entry : fs::directory_iterator(SAVE_DIR)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();

            if (filename.rfind(SLOT_PREFIX, 0) == 0 &&
                filename.size() >= slot_extension.size() &&
                filename.compare(filename.size() - slot_extension.size(),
                    slot_extension.size(), slot_extension) == 0)
            {
                std::string numberStr = filename.substr(
                    SLOT_PREFIX.size(),
                    filename.size() - SLOT_PREFIX.size() - slot_extension.size()
                );
                try {
                    int slotNum = std::stoi(numberStr);
                    slots.push_back(slotNum);
                }
                catch (...) {
                    // bỏ qua
                }
            }
        }
    }

    return slots;
}


void SaveManager::cleanupInvalidFiles() {
    ensureSaveDirectoryExists();

    for (const auto& entry : fs::directory_iterator(SAVE_DIR)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();

            // Check xem có đúng format "slotN.json"
            bool valid = false;
            if (filename.rfind(SLOT_PREFIX, 0) == 0 &&
                filename.size() > SLOT_PREFIX.size() + slot_extension.size())
            {
                std::string numberStr = filename.substr(
                    SLOT_PREFIX.size(),
                    filename.size() - SLOT_PREFIX.size() - slot_extension.size()
                );

                try {
                    int slotNum = std::stoi(numberStr);
                    if (slotNum > 0) {
                        valid = true; // Hợp lệ
                    }
                }
                catch (...) {
                    // số không hợp lệ => invalid
                }
            }

            // Nếu không hợp lệ thì xóa
            if (!valid) {
                std::cout << "Deleting invalid save file: " << filename << std::endl;
                fs::remove(entry.path());
            }
        }
    }
}


void SaveManager::ensureSaveDirectoryExists() {
    if (!fs::exists(SAVE_DIR))
        fs::create_directory(SAVE_DIR);
}

int SaveManager::findNextFreeSlot(int maxSlots)
{
    ensureSaveDirectoryExists();
    for (int i = 1; i <= maxSlots; i++) {
        if (!slotExists(i)) {
            return i; // slot này trống
        }
    }
    return -1; // không còn slot trống
}


