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
        bool found = false;

        // TÍNH TOÁN CÔNG THỨC: Chỉ lấy chênh lệch lớn hơn (từ mức cần thiết đến +80%)
        int variance = totalVol * 0.8; 
        int minVol = totalVol; // Bắt đầu từ đúng dung tích cần thiết (không lấy nhỏ hơn)
        int maxVol = totalVol + variance;

        std::string searchInput = toLowerCase(teaType); 

        std::cout << "\n========== KẾT QUẢ TƯ VẤN ==========\n";
        std::cout << "Dung tích chuẩn cần thiết: " << totalVol << "ml\n";
        std::cout << "(Hệ thống tự động lọc các ấm có dung tích TB trong khoảng: " << minVol << "ml - " << maxVol << "ml)\n\n";

        for (const auto& pot : inventory) {
            // Lọc 1: Kiểm tra loại trà có khớp không
            if (toLowerCase(pot.teaSearch).find(searchInput) != std::string::npos) {
                // Lọc 2: Kiểm tra dung tích trung bình có nằm trong khoảng từ (cần thiết) đến (cần thiết + 80%)
                if (pot.avgVolume >= minVol && pot.avgVolume <= maxVol) {
                    std::cout << ">>> GỢI Ý ẤM PHÙ HỢP: " << pot.name << "\n";
                    std::cout << "  - Mã ấm   : " << pot.id << "\n";
                    std::cout << "  - Chất đất: " << pot.clayType << "\n";
                    std::cout << "  - Dáng ấm : " << pot.shape << "\n";
                    std::cout << "  - Dung tích: " << pot.volume << " (TB: " << pot.avgVolume << "ml)\n";
                    std::cout << "  - Trà hợp : " << pot.teaDisplay << "\n";
                    std::cout << "------------------------------------------\n";
                    found = true; 
                }
            }
        }

        if (!found) {
            std::cout << "Tiếc quá, kho hiện tại chưa có ấm phù hợp thỏa mãn dung tích và loại trà bạn chọn.\n";
            std::cout << "Vui lòng kiểm tra lại tên trà hoặc đổi số lượng người/dung tích chén.\n";
        }
        
        std::cout << "====================================\n";
    }
};

#endif