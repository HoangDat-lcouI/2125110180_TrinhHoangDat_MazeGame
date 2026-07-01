
**Maze Game (Trò Chơi Mê Cung C++)**
Một ứng dụng console tương tác được viết bằng C++ cho phép người dùng tạo các mê cung ngẫu nhiên, tự trải nghiệm giải mê cung hoặc quan sát máy tính tự động tìm đường ra thông qua các thuật toán duyệt đồ thị kinh điển. 

## Cấu trúc dữ liệu sử dụng
- **Stack (Ngăn xếp):** - *Dùng để:* Hỗ trợ thuật toán tạo mê cung ngẫu nhiên (Recursive Backtracker) và thuật toán tìm đường DFS (Depth First Search).
  - *Vì:* Đặc tính LIFO (Vào sau ra trước) của Stack rất phù hợp để lưu lại lịch sử các bước di chuyển, giúp hệ thống có thể "quay lui" (backtrack) dễ dàng khi gặp ngõ cụt trong quá trình tạo hoặc giải mê cung.
- **Queue (Hàng đợi):** - *Dùng để:* Hỗ trợ thuật toán giải mê cung BFS (Breadth First Search).
  - *Vì:* Đặc tính FIFO (Vào trước ra trước) giúp thuật toán duyệt qua các ô theo từng lớp từ gần đến xa, qua đó đảm bảo luôn tìm được con đường ngắn nhất từ điểm bắt đầu đến đích.
- **Vector (Mảng động):** - *Dùng để:* Lưu trữ bản đồ mê cung (mảng 2 chiều `vector<vector<Cell>>`), danh sách các ô kề cạnh (neighbors) và danh sách tọa độ tạo nên đường đi (path).
  - *Vì:* Vector cấp phát bộ nhớ động, cho phép thay đổi kích thước dễ dàng (hỗ trợ các độ khó/kích thước mê cung khác nhau như 10x10, 20x20, 30x30) và truy xuất phần tử nhanh chóng.
- **Struct (Cấu trúc):**
  - *Dùng để:* Định nghĩa `Cell` (lưu trạng thái 4 bức tường và trạng thái đã duyệt) và `Position` (lưu tọa độ hàng, cột).
  - *Vì:* Giúp nhóm các thuộc tính có liên quan lại với nhau, làm cho code hướng đối tượng, gọn gàng và dễ hiểu hơn.

Chức năng
1.Tạo mê cung ngẫu nhiên: Sử dụng thuật toán Recursive Backtracker để sinh ra các mê cung hoàn hảo (không có chu trình và luôn có đường đi) theo thời gian thực.

2.Hiển thị trực quan (ASCII Art): In và render mê cung ra màn hình console bằng các ký tự ASCII, hiển thị rõ ràng tường, vị trí người chơi (P), đích đến (E) và đường đi (o).

3.Chơi thủ công: Cho phép người dùng tự di chuyển và giải mê cung thông qua các phím điều hướng W (Lên), A (Trái), S (Xuống), D (Phải).

4.Giải tự động bằng BFS: Tìm và hiển thị con đường ngắn nhất từ điểm xuất phát tới đích.

5.Giải tự động bằng DFS (Visualized): Mô phỏng trực quan từng bước đi của máy tính khi dùng thuật toán tìm kiếm theo chiều sâu (có hiệu ứng delay để dễ quan sát quá trình backtrack).

6.So sánh thuật toán: Chạy song song BFS và DFS để so sánh độ dài đường đi và số lượng ô phải duyệt của từng thuật toán.

7.Tùy chỉnh độ khó: Hỗ trợ thay đổi kích thước mê cung theo 3 cấp độ: Dễ (10x10), Trung bình (20x20) và Khó (30x30).