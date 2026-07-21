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
    void addTeapot(std::string id, std::string name, std::string clay, std::string shape, std::string volRange, std::string teaDisplay, std::string teaSearch) {
        teapotList.emplace_back(id, name, clay, shape, volRange, teaDisplay, teaSearch);
    }

    void importTeapotsCSV(std::string filename) {
        teapotList.clear();
        std::ifstream file(filename);
        if (!file.is_open()) return;

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

            if (row.size() >= 7) {
                addTeapot(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
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

    // Cung cấp danh sách ấm trà cho class Consultant đọc
    const std::vector<Teapot>& getInventory() const {
        return teapotList;
    }
};
#endif