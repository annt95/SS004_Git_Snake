# SS004_Git_Snake

Trò chơi rắn săn mồi (Snake) chạy trên console, viết bằng C++.
Dự án dùng để thực hành làm việc nhóm với Git trong môn SS004.

## Thành viên nhóm

| Họ và tên          | MSSV     | GitHub                                         |
|--------------------|----------|------------------------------------------------|
| Ngô Thành An       | 26730083 | [annt95](https://github.com/annt95)            |
| Nguyễn Hữu Trương  | 26730143 | [26730143](https://github.com/26730143)        |
| Nguyễn Minh Tiến   | 26730137 | [UIT26730137](https://github.com/UIT26730137)  |

## Yêu cầu

- Windows, macOS hoặc Linux
  - Windows dùng `windows.h` / `conio.h`
  - macOS/Linux dùng `termios` và mã ANSI, cần chạy trong terminal thật
- Trình biên dịch C++11 trở lên: `g++`, `clang++`, MinGW hoặc Visual Studio

## Biên dịch và chạy

Windows:

```bash
g++ -std=c++11 snake.cpp -o snake.exe
```

```bash
snake.exe
```

macOS / Linux:

```bash
g++ -std=c++11 snake.cpp -o snake
```

```bash
./snake
```

## Cách chơi

| Phím | Hướng   |
|------|---------|
| `w`  | Lên     |
| `x`  | Xuống   |
| `a`  | Trái    |
| `d`  | Phải    |
| `q`  | Thoát   |

Rắn không thể quay đầu ngược 180° (ví dụ đang đi phải thì bấm `a` sẽ bị bỏ qua).

## Cấu trúc code

- `CONRAN` — lớp con rắn: mảng toạ độ `A` (`A[0]` là đầu), độ dài `DoDai`
  - `Ve()` — vẽ rắn lên console
  - `DiChuyen(Huong)` — di chuyển rắn 1 ô theo hướng
- `gotoxy(x, y)` — đặt con trỏ console tới vị trí cần vẽ
- `readKeyIfAvailable()` — đọc phím không chặn (trả về `-1` nếu chưa bấm)
- `clearScreen()` — xoá màn hình
- `TerminalMode` (macOS/Linux) — bật chế độ raw cho terminal, khôi phục khi thoát

## Quy trình đóng góp

1. Tạo nhánh mới cho mỗi tính năng/sửa lỗi: `git switch -c ten-nhanh`
2. Commit nhỏ, mô tả rõ thay đổi
3. Tạo Pull Request vào `main` để nhóm review trước khi merge
