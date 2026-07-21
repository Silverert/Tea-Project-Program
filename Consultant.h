#ifndef CONSULTANT_H
#define CONSULTANT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Teapot.h"

class Consultant {
private:
    // Chuyển chuỗi về chữ thường để so sánh không phân biệt hoa/thường
    std::string toLowerCase(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

public:
    void recommend(const std::string& teaType, int people, int cupVol, const std::vector<Teapot>& inventory) {
        int totalVol = people * cupVol;
        bool found = false;

        // Đưa input của user về chữ thường
        std::string searchInput = toLowerCase(teaType); 

        std::cout << "\n========== KẾT QUẢ TƯ VẤN ==========\n";
        std::cout << "Tổng dung tích cần thiết: " << totalVol << "ml - " << (totalVol + 20) << "ml\n\n";

        // Vòng lặp tìm kiếm trong kho
        for (const auto& pot : inventory) {
            // So sánh với cột teaSearch trong dữ liệu
            if (toLowerCase(pot.teaSearch).find(searchInput) != std::string::npos) {
                std::cout << ">>> GỢI Ý ẤM PHÙ HỢP: " << pot.name << "\n";
                std::cout << "  - Chất đất: " << pot.clayType << "\n";
                std::cout << "  - Dáng ấm : " << pot.shape << "\n";
                std::cout << "  - Dung tích: " << pot.volume << "\n";
                std::cout << "  - Trà hợp : " << pot.teaDisplay << "\n";
                std::cout << "------------------------------------------\n";
                found = true; 
            }
        }

        // CHỈ in thông báo này nếu sau khi duyệt hết kho mà không tìm thấy gì
        if (!found) {
            std::cout << "Tiếc quá, kho hiện tại chưa có ấm phù hợp cho: " << teaType << "\n";
            std::cout << "Vui lòng kiểm tra lại tên trà hoặc dùng chức năng 5 để xem các loại trà.\n";
        }
        
        std::cout << "====================================\n";
    }
};

#endif