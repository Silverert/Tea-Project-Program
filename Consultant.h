#ifndef CONSULTANT_H
#define CONSULTANT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Teapot.h"

class Consultant {
private:
    std::string toLowerCase(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

public:
    void recommend(const std::string& teaType, int people, int cupVol, const std::vector<Teapot>& inventory) {
        int totalVol = people * cupVol;
        
        // TÍNH TOÁN CÔNG THỨC: Chênh lệch từ mức cần thiết đến +80%
        int variance = totalVol * 0.8; 
        int minVol = totalVol; 
        int maxVol = totalVol + variance;

        std::string searchInput = toLowerCase(teaType); 

        std::cout << "\n========== KẾT QUẢ TƯ VẤN ==========\n";
        std::cout << "Dung tích chuẩn cần thiết: " << totalVol << "ml\n";
        std::cout << "(Hệ thống tự động lọc các ấm có dung tích TB trong khoảng: " << minVol << "ml - " << maxVol << "ml)\n\n";

        // Tạo một danh sách tạm để lưu các ấm khớp loại trà
        std::vector<Teapot> matchedTeaTeapots;
        bool foundPerfectMatch = false;

        // BƯỚC 1: Quét kho để tìm TẤT CẢ các ấm khớp loại trà
        for (const auto& pot : inventory) {
            if (toLowerCase(pot.teaSearch).find(searchInput) != std::string::npos) {
                matchedTeaTeapots.push_back(pot); // Lưu vào danh sách tạm
                
                // Nếu ấm này khớp luôn cả dung tích thì đánh dấu là đã tìm thấy mĩ mãn
                if (pot.avgVolume >= minVol && pot.avgVolume <= maxVol) {
                    foundPerfectMatch = true;
                }
            }
        }

        // BƯỚC 2: Xử lý kết quả in ra màn hình
        if (foundPerfectMatch) {
            // Trường hợp 1: Có ấm khớp CẢ trà LẪN dung tích
            for (const auto& pot : matchedTeaTeapots) {
                if (pot.avgVolume >= minVol && pot.avgVolume <= maxVol) {
                    std::cout << ">>> GỢI Ý ẤM HOÀN HẢO: " << pot.name << "\n";
                    std::cout << "  - Mã ấm   : " << pot.id << "\n";
                    std::cout << "  - Chất đất: " << pot.clayType << "\n";
                    std::cout << "  - Dáng ấm : " << pot.shape << "\n";
                    std::cout << "  - Dung tích: " << pot.volume << " (TB: " << pot.avgVolume << "ml)\n";
                    std::cout << "  - Trà hợp : " << pot.teaDisplay << "\n";
                    std::cout << "------------------------------------------\n";
                }
            }
        } else if (!matchedTeaTeapots.empty()) {
            // Trường hợp 2: Có ấm khớp trà, NHƯNG KHÔNG khớp dung tích
            std::cout << "Không tìm được loại ấm phù hợp với dung tích bạn chọn.\n";
            std::cout << "Các loại ấm phù hợp với '" << teaType << "':\n";
            std::cout << "------------------------------------------\n";
            for (const auto& pot : matchedTeaTeapots) {
                std::cout << ">>> Ấm: " << pot.name << "\n";
                std::cout << "  - Mã ấm   : " << pot.id << "\n";
                std::cout << "  - Chất đất: " << pot.clayType << "\n";
                std::cout << "  - Dáng ấm : " << pot.shape << "\n";
                std::cout << "  - Dung tích: " << pot.volume << " (TB: " << pot.avgVolume << "ml)\n";
                std::cout << "------------------------------------------\n";
            }
        } else {
            // Trường hợp 3: Sai tên trà hoặc kho chưa có loại trà này
            std::cout << "Tiếc quá, kho hiện tại chưa có ấm phù hợp cho loại trà '" << teaType << "'.\n";
            std::cout << "Vui lòng kiểm tra lại tên trà hoặc dùng chức năng 5 để xem các loại trà.\n";
        }
        
        std::cout << "====================================\n";
    }
};

#endif