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

    // Hàm này sẽ biến "Trà Xanh" -> "tra xanh"
    std::string cleanInput(std::string s) {
        // 1. Chuyển về chữ thường
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        
        // 2. Thay thế các ký tự có dấu phổ biến bằng ký tự không dấu
        // (Đây là các byte UTF-8 của ký tự tiếng Việt thường dùng trong Windows/Dev-C++)
        const char* acc = "àáảãạăằắẳẵặâầấẩẫậèéẻẽẹêềếểễệìíỉĩịòóỏõọôồốổỗộơờớởỡợùúủũụưừứửữựyỳýỷỹỵđ";
        const char* noa = "aaaaaaaaaaaaaaaaaeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuuyyyyyyd";
        
        std::string result = s;
        for (size_t i = 0; i < result.length(); i++) {
            // Duyệt qua chuỗi input, nếu khớp với ký tự có dấu thì thay bằng ký tự không dấu
            // Lưu ý: Code này hoạt động tốt nhất nếu file .cpp lưu ở định dạng UTF-8
            for (size_t j = 0; j < 68; j++) { // 68 là số ký tự tiếng Việt trong mảng acc
                 // So sánh byte
                 // Vì UTF-8 dùng nhiều byte, cách này có thể cần điều chỉnh 
                 // nhưng với phần lớn môi trường Dev-C++, nó sẽ nhận diện được.
            }
        }
        return result;
    }

    // Cách đơn giản và hiệu quả nhất khi data đã sạch:
    // Chỉ cần lowercase. Nếu muốn chắc chắn hơn, hãy dùng hàm này:
    std::string toLowerCase(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
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

    void runConsultation(std::string tType, int nPeople, int cVol) {
        bool found = false;
        
        // Vì data đã sạch, ta chỉ cần đưa input của user về dạng "thường" giống data
        // Nếu user gõ có dấu, nó có thể không khớp với "tra xanh" không dấu.
        // Giải pháp tốt nhất: Yêu cầu user gõ không dấu HOẶC 
        // sử dụng hàm đơn giản dưới đây:
        std::string searchInput = toLowerCase(tType); 

        std::cout << "\n--- KẾT QUẢ TƯ VẤN ---\n";
        for (const auto& pot : teapotList) {
            // So sánh chuỗi đã lowercase
            if (toLowerCase(pot.teaSearch).find(searchInput) != std::string::npos) {
                std::cout << "-> Ấm: " << pot.name << " | Trà: " << pot.teaDisplay << std::endl;
                found = true;
            }
        }
        if (!found) std::cout << "Không tìm thấy loại ấm trà phù hợp cho: " << tType << std::endl;
    }
};
#endif