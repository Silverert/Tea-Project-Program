#include <iostream>
#include <windows.h>
#include "Manager.h"
#include "Admin.h"
#include "Consultant.h" 

using namespace std;

int main() {
    // Thiết lập tiếng Việt cho console
    SetConsoleCP(65001); 
    SetConsoleOutputCP(65001);
    
    SystemManager app;
    AdminPanel admin;
    Consultant advisor; // Khởi tạo đối tượng tư vấn

    // TỰ ĐỘNG ĐỒNG BỘ NGAY KHI CHƯƠNG TRÌNH KHỞI CHẠY
    app.importTeapotsCSV("Tea_List.csv"); 

    while (true) {
        cout << "\n================ HỆ THỐNG QUẢN LÝ TRÀ ================\n";
        cout << "1. Kho ấm trà\n";
        cout << "2. Tư vấn chọn ấm\n";
        cout << "3. Danh sách các loại trà khả dụng\n";
        cout << "4. ĐỒNG BỘ DỮ LIỆU\n";
        cout << "5. [ADMIN] Nhập dữ liệu tay\n";
        cout << "0. Thoát\n";
        cout << "Chọn chức năng (0-5): ";

        int choice;
        // Kiểm tra lỗi nhập liệu
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Lựa chọn không hợp lệ!\n";
            continue;
        }

        if (choice == 0) break; // Thoát chương trình

        // Xử lý các chức năng
        switch (choice) {
            case 1: 
                app.showInventory(); 
                break;
            case 2: {
                string tType;
                int nPeople, cVol;
                cout << "\n--- NHẬP THÔNG TIN TƯ VẤN ---\n";
                cout << "Nhập loại trà (vui lòng nhập không dấu VD: Tra Xanh/tra xanh): ";
 
                cin.ignore();
                getline(cin, tType);
                
                // --- VÒNG LẶP KIỂM TRA LỖI CHỐNG NHẬP CHỮ & SỐ ÂM ---
                do {
                    cout << "Số người uống: ";
                    if (!(cin >> nPeople)) { 
                        cin.clear(); cin.ignore(1000, '\n'); nPeople = -1; 
                    }
                    
                    cout << "Dung tích chén (ml): ";
                    if (!(cin >> cVol)) { 
                        cin.clear(); cin.ignore(1000, '\n'); cVol = -1; 
                    }
                    
                    if (nPeople <= 0 || cVol <= 0) {
                        cout << "=> [LỖI] Dữ liệu không hợp lệ! Vui lòng chỉ nhập số dương.\n\n";
                    }
                } while (nPeople <= 0 || cVol <= 0);
                
                // Sử dụng Consultant để tư vấn
                advisor.recommend(tType, nPeople, cVol, app.getInventory());
                break;
            }
            case 5: 
                admin.showMenu(app); 
                break;
            case 4: 
                app.importTeapotsCSV("Tea_List.csv"); 
                break;
            case 3: 
                app.showAvailableTeas();
                break;
            default: 
                cout << "Lựa chọn không hợp lệ!\n";
        }
    }
    return 0;
}