#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include "Manager.h"

class AdminPanel {
public:
    void showMenu(SystemManager& app) {
        int choice;
        while (true) {
            std::cout << "\n--- [MENU QUẢN TRỊ VIÊN] ---\n1. Thêm ấm trà\n0. Quay lại\nChọn: ";
            
            // Bắt lỗi nhập chữ ở Menu Admin
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Lựa chọn không hợp lệ!\n";
                continue;
            }
            if (choice == 0) break;
            std::cin.ignore();
            
            if (choice == 1) {
                std::string id, name, clay, shape, vol, teas, displayTeas;
                int avgVol;
                
                std::cout << "Mã: "; std::cin >> id; std::cin.ignore();
                std::cout << "Tên ấm: "; std::getline(std::cin, name);
                std::cout << "Chất đất: "; std::getline(std::cin, clay);
                std::cout << "Dáng ấm: "; std::getline(std::cin, shape);
                std::cout << "Dung tích (VD: 40ml - 60ml): "; std::getline(std::cin, vol);
                std::cout << "Loại trà phù hợp (display - có dấu có viết hoa): "; std::getline(std::cin, teas);
                std::cout << "Loại trà phù hợp (search - không dấu không viết hoa): "; std::getline(std::cin, displayTeas);
                
                // Bắt lỗi nhập chữ ở Dung tích trung bình
                std::cout << "Dung tích trung bình (chỉ nhập số - VD: 150): "; 
                while (!(std::cin >> avgVol) || avgVol <= 0) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "[LỖI] Vui lòng chỉ nhập số dương: ";
                }
                std::cin.ignore();
                
                app.addTeapot(id, name, clay, shape, vol, teas, displayTeas, avgVol);
                app.saveNewTeapotToCSV("Tea_List.csv", id, name, clay, shape, vol, teas, displayTeas, avgVol);
                
                std::cout << "=> Thêm và lưu vào file CSV thành công!\n";
            }
        }
    }
};
#endif	