# SS004_Git_Snake

Trò chơi rắn săn mồi (Snake) chạy trên console Windows, viết bằng C++.
Dự án dùng để thực hành làm việc nhóm với Git trong môn SS004.

## Yêu cầu

- Windows (code dùng `windows.h` và `conio.h`)
- Trình biên dịch C++: MinGW `g++`, Dev-C++ hoặc Visual Studio

## Biên dịch và chạy

```bash
g++ snake.cpp -o snake.exe
```

```bash
snake.exe
```

## Cách chơi

| Phím | Hướng   |
|------|---------|
| `w`  | Lên     |
| `x`  | Xuống   |
| `a`  | Trái    |
| `d`  | Phải    |

Rắn không thể quay đầu ngược 180° (ví dụ đang đi phải thì bấm `a` sẽ bị bỏ qua).

## Cấu trúc code

- `CONRAN` — lớp con rắn: mảng toạ độ `A` (`A[0]` là đầu), độ dài `DoDai`
  - `Ve()` — vẽ rắn lên console
  - `DiChuyen(Huong)` — di chuyển rắn 1 ô theo hướng
- `gotoxy(x, y)` — đặt con trỏ console tới vị trí cần vẽ

## Quy trình đóng góp

1. Tạo nhánh mới cho mỗi tính năng/sửa lỗi: `git switch -c ten-nhanh`
2. Commit nhỏ, mô tả rõ thay đổi
3. Tạo Pull Request vào `main` để nhóm review trước khi merge
