```markdown
# Điều Khiển Robot Di Động với Cảm Biến Đường Dẫn

**Tên Chương Trình:** xe_do_line_5_mat_BAOTT569.ino

**Tác Giả:** BAOTT569

**Ngày Sửa Đổi Cuối Cùng:** 19/12/2023

## Mô Tả

Chương trình xe_do_line_5_mat_BAOTT569.ino điều khiển robot di động thông qua cảm biến đường dẫn. Cung cấp khả năng thực hiện các hành động như tiến, lùi, quẹo trái và quẹo phải dựa trên thông tin cảm biến.

## Hướng Dẫn Sử Dụng

1. Cài đặt chương trình lên bo mạch Arduino.
2. Kết nối cảm biến và động cơ với robot.
3. Khởi động robot để theo dõi hành vi di chuyển.

## Hàm Chính

- `readSensors()`: Đọc giá trị từ cảm biến và giới hạn chúng trong khoảng 0-1000.
- `processSensorValues()`: Chuyển đổi giá trị cảm biến thành số nhị phân.
- `handleDirection()`: Xử lý hướng di chuyển dựa trên giá trị số nhị phân.
- `notLine()`: Xử lý trường hợp không có đường dẫn.

## Cấu Trúc

- **MotorPins:** Chứa thông tin chân điều khiển động cơ.
- **motorData:** Lưu trữ thông tin về động cơ, bao gồm chân điều khiển và tốc độ.

## Báo Lỗi và Đóng Góp

Đề xuất cải tiến hoặc báo lỗi tại [GitHub Issues](https://www.facebook.com/profile.php?id=100021561485210).

## Giấy Phép

Phần mềm được phát hành free.

## Cảm ơn các bạn đã xem có thể nó không hoàng hảo nhưng rất vui vì bạn đã xem qua 😋
---

© BAOTT569 | 19/12/2023
```
