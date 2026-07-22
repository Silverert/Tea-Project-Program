#ifndef TEAPOT_H
#define TEAPOT_H

#include <string>
#include <iostream>

struct Teapot {
    std::string id, name, clayType, shape, volume, teaDisplay, teaSearch;
    int avgVolume; // Thêm biến lưu dung tích trung bình

    // HÀM KHỞI TẠO (Constructor)
    Teapot(std::string _id, std::string _name, std::string _clay, std::string _shape, 
           std::string _vol, std::string _teaDisplay, std::string _teaSearch, int _avgVolume) 
        : id(_id), name(_name), clayType(_clay), shape(_shape), 
          volume(_vol), teaDisplay(_teaDisplay), teaSearch(_teaSearch), avgVolume(_avgVolume) {}

    void displayCard() const { 
        std::cout << "---------------------------------------------------------\n";
        std::cout << " [Mã ấm: " << id << "] - " << name << "\n";
        std::cout << "---------------------------------------------------------\n";
        std::cout << " + Chất đất  : " << clayType << "\n";
        std::cout << " + Kiểu dáng : " << shape << "\n";
        std::cout << " + Dung tích : " << volume << " (TB: " << avgVolume << "ml)\n";
        
        // Hiển thị trà
        std::string displayTea = teaDisplay;
        size_t pos = displayTea.find(';'); 
        while(pos != std::string::npos) {
            displayTea.replace(pos, 1, ", ");
            pos = displayTea.find(';', pos + 1);
        }
        std::cout << " + Trà gợi ý : " << displayTea << "\n";
        std::cout << "---------------------------------------------------------\n\n";
    }
};

#endif