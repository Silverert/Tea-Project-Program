#ifndef CONSULTANT_H
#define CONSULTANT_H

#include <iostream>
#include <string>
#include <vector>
#include "Teapot.h"

// Đảm bảo struct Teapot đã được định nghĩa ở đâu đó trong dự án của bạn (thường là trong Manager.h)
// Nếu chưa có, bạn có thể cần include header chứa định nghĩa Teapot vào đây.

class Consultant {
public:
    void recommend(const std::string& teaType, int people, int cupVol, const std::vector<Teapot>& inventory) {
        int totalVol = people * cupVol;
        bool found = false;

        std::cout << "\n========== KẾT QUẢ TƯ VẤN ==========\n";
        std::cout << "Tổng dung tích cần thiết: " << totalVol << "ml - " << (totalVol + 20) << "ml\n\n";

        // Vòng lặp tìm kiếm trong kho
        for (const auto& pot : inventory) {
            // Kiểm tra nếu loại trà tìm thấy trong chuỗi teaDisplay
            if (pot.teaDisplay.find(teaType) != std::string::npos) {
                std::cout << ">>> GỢI Ý ẤM PHÙ HỢP: " << pot.name << "\n";
                std::cout << "  - Chất đất: " << pot.clayType << "\n";
                std::cout << "  - Kiểu dáng: " << pot.shape << "\n";
                std::cout << "  - Dung tích: " << pot.volume << "\n";
                std::cout << "------------------------------------------\n";
                found = true; 
            }
        }

        // CHỈ in thông báo này nếu sau khi duyệt hết kho mà không tìm thấy gì
        if (!found) {
            std::cout << "Tiếc quá, kho hiện tại chưa có ấm phù hợp cho: " << teaType << "\n";
            std::cout << "Vui lòng kiểm tra lại tên trà hoặc nạp dữ liệu mới.\n";
        }
        
        std::cout << "====================================\n";
    }
};

#endif