===================================================================
ĐỒ ÁN MÔN HỌC: CƠ SỞ LẬP TRÌNH (PRF)
TÊN ĐỀ TÀI: HỆ THỐNG QUẢN LÝ VÀ TƯ VẤN CHỌN ẤM TRÀ
===================================================================

I. THÔNG TIN SINH VIÊN
- Sinh viên thực hiện: 
	Trần Huy Hoàng - HE211112 - Coder chính
	Nguyễn Xuân Giang - HE210701 - Coder phụ
	Lương Trọng Nghĩa - HE211150 - Nhập cơ sở dữ liệu
	Nguyễn Thành Long - HE211669 - Thiết kế Power Point
- Lớp: IC2110
- Giảng viên hướng dẫn: Bùi Ngọc Anh


II. GIỚI THIỆU DỰ ÁN
Chương trình là một ứng dụng Console C++ được xây dựng dựa trên tư duy 'Lập trình Hướng đối tượng' (OOP). Hệ thống giúp quản lý danh sách các loại ấm trà (với các thuộc tính chi tiết như chất đất, kiểu dáng, dung tích...) và cung cấp thuật toán tư vấn chọn ấm phù hợp dựa trên nhu cầu của người dùng (loại trà, số lượng người uống, thể tích chén).


III. CÁC TÍNH NĂNG NỔI BẬT
1. Quản lý kho: Lưu trữ và nạp dữ liệu động từ file định dạng CSV.

2. Tư vấn thông minh:
	- Tự động tính toán dung tích cần thiết dựa trên số người và thể tích chén.
	- Đưa ra những loại chén phù hợp với loại trà và dung tích cần thiết
	- Thuật toán tìm kiếm mở rộng (+80% dung tích) để đưa ra các gợi ý tối ưu nhất.
	- Đưa ra các lựa chọn thay thế nếu không tìm được ấm khớp dung tích 100%.

3. Quản trị viên (Admin): Cho phép nhập liệu trực tiếp từ Console và ghi thẳng xuống (Append) ổ cứng (file CSV) để lưu trữ vĩnh viễn dữ liệu mới.

4. Xử lý ngoại lệ (Input Validation): Ngăn chặn lỗi khi người dùng nhập số âm, nhập sai định dạng tại các menu.

5. So sánh chuỗi linh hoạt: Hỗ trợ tìm kiếm trà không phân biệt chữ hoa, chữ thường.


IV. CẤU TRÚC MÃ NGUỒN (SEPARATION OF CONCERNS)

Dự án được chia thành các module độc lập để dễ dàng bảo trì:
	-Teapot.h    : Khai báo cấu trúc dữ liệu cơ bản của một Ấm trà.
	-Manager.h   : Xử lý logic Đọc/Ghi file File I/O và quản lý danh sách.
	-Consultant.h: Đảm nhiệm riêng phần thuật toán tính toán và tư vấn.
	-Admin.h     : Giao diện và logic nhập liệu dành cho quản trị.
	-main.cpp    : Điểm neo của chương trình, chứa Menu điều hướng.
	-Tea_List.csv: Cơ sở dữ liệu của hệ thống.

V. HƯỚNG DẪN CÀI ĐẶT VÀ CHẠY CHƯƠNG TRÌNH

1. Môi trường: Dev-C++ (hoặc các IDE hỗ trợ chuẩn C++11 trở lên).
2. Yêu cầu: Đảm bảo file `Tea_List.csv` nằm cùng thư mục với file `main.cpp` (hoặc file `.exe` nếu chạy trực tiếp).
3. Hiển thị: Mở mã nguồn bằng Dev-C++, ấn F11 (Compile & Run). Chương trình đã được thiết lập `SetConsoleOutputCP(65001)` để hiển thị tiếng Việt có dấu hoàn chỉnh.


VI. LƯU Ý QUAN TRỌNG KHI SỬ DỤNG
- Khi sử dụng tính năng [3. Nhập dữ liệu tay] của Admin, vui lòng ĐÓNG file `Tea_List.csv` nếu đang mở bằng Excel. Nếu Excel đang chiếm quyền file, C++ sẽ không thể ghi dữ liệu mới xuống ổ cứng.
- Chương trình nhận diện tốt nhất với bảng mã UTF-8.

===================================================================