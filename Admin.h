#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include "Manager.h"


//Chức năng của Admin: Cho phép nhập thêm Ấm trà, Chất đất, Dáng ấm, Dung tích, Loại trà phù hợp với ấm.

class AdminPanel {
public:
    void showMenu(SystemManager& app) {
        int choice;
        while (true) {
            std::cout << "\n--- [MENU QUẢN TRỊ VIÊN] ---\n1. Thêm ấm trà\n0. Quay lại\nChọn: ";
            std::cin >> choice;
            if (choice == 0) break;
            std::cin.ignore();
            
            if (choice == 1) {
                std::string id, name, clay, shape, vol, teas, displayTeas;
                std::cout << "Mã: "; std::cin >> id; std::cin.ignore();
                std::cout << "Tên ấm: "; std::getline(std::cin, name);
                std::cout << "Chất đất: "; std::getline(std::cin, clay);
                std::cout << "Dáng ấm: "; std::getline(std::cin, shape);
                std::cout << "Dung tích (VD: 100ml - 150ml): "; std::getline(std::cin, vol);
                std::cout << "Loại trà phù hợp (display - có dấu có viết hoa): "; std::getline(std::cin, teas);		// Tên loại trà sẽ được hiển thị (VD: Trà Xanh)
                std::cout << "Loại trà phù hợp (search - không dấu không viết hoa): "; std::getline(std::cin, displayTeas);		//Tên loại trà dùng cho việc tìm kiếm (VD:tra xanh)
                
                app.addTeapot(id, name, clay, shape, vol, teas, displayTeas);
                std::cout << "=> Thêm thành công!\n";
            }
        }
    }
};
#endif