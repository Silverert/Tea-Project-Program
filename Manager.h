#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include "Teapot.h"

class SystemManager {
private:
    std::vector<Teapot> teapotList;

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (std::string::npos == first) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

public:
    void addTeapot(std::string id, std::string name, std::string clay, std::string shape, std::string volRange, std::string teaDisplay, std::string teaSearch, int avgVolume) {
        teapotList.emplace_back(id, name, clay, shape, volRange, teaDisplay, teaSearch, avgVolume);
    }
    
    void saveNewTeapotToCSV(std::string filename, std::string id, std::string name, std::string clay, std::string shape, std::string volRange, std::string teaDisplay, std::string teaSearch, int avgVolume) {
        std::ofstream file(filename, std::ios::app); 
        if (file.is_open()) {
            // Đã bọc ngoặc kép cho các chuỗi để chống lỗi dấu phẩy
            file << "\n" << id << ",\"" << name << "\",\"" << clay << "\",\"" << shape << "\",\"" << volRange << "\",\"" << teaDisplay << "\",\"" << teaSearch << "\"," << avgVolume;
            file.close();
        } else {
            std::cout << "[LỖI] Không thể mở file " << filename << " để lưu!\n";
        }
    }

    void importTeapotsCSV(std::string filename) {
        teapotList.clear();
        std::ifstream file(filename);
        
        // --- BẢN VÁ LỖI: Báo cảnh báo nếu mất file ---
        if (!file.is_open()) {
            std::cout << "[CẢNH BÁO] Không tìm thấy file '" << filename << "'!\n";
            std::cout << "=> Hệ thống hiện đang chạy với kho dữ liệu trống.\n";
            return;
        }
        // ---------------------------------------------

        std::string line;
        std::getline(file, line); 

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::vector<std::string> row;
            std::string cell;
            bool inQuotes = false;
            for (size_t i = 0; i < line.size(); ++i) {
                char c = line[i];
                if (c == '\"') inQuotes = !inQuotes;
                else if (c == ',' && !inQuotes) {
                    cell = trim(cell);
                    row.push_back(cell);
                    cell = "";
                } else cell += c;
            }
            cell = trim(cell);
            row.push_back(cell);

            // Kiểm tra xem đã có đủ 8 cột chưa (bao gồm cả cột avgVolume mới)
            if (row.size() >= 8) {
                int avgVol = 0;
                try {
                    avgVol = std::stoi(row[7]); // Ép kiểu string sang int
                } catch (...) {
                    avgVol = 0; // Nếu ô trống hoặc lỗi thì gán bằng 0
                }
                addTeapot(row[0], row[1], row[2], row[3], row[4], row[5], row[6], avgVol);
            }
        }
        file.close();
        std::cout << "-Data synchronized successfully-" << std::endl;
    }
		
    void showInventory() {
        std::cout << "\n--- DANH SÁCH ẤM TRÀ ---\n";
        for (const auto& pot : teapotList) pot.displayCard();
    }

    void showAvailableTeas() {
        std::set<std::string> uniqueTeas;
        for (const auto& pot : teapotList) {
            std::stringstream ss(pot.teaDisplay);
            std::string segment;
            while (std::getline(ss, segment, ';')) {
                std::string cleanedTea = trim(segment);
                if (!cleanedTea.empty()) uniqueTeas.insert(cleanedTea);
            }
        }
        std::cout << "\n--- CÁC LOẠI TRÀ KHẢ DỤNG ---\n";
        int count = 1;
        for (const auto& tea : uniqueTeas) std::cout << count++ << ". " << tea << "\n";
    }

    const std::vector<Teapot>& getInventory() const {
        return teapotList;
    }
};
#endif