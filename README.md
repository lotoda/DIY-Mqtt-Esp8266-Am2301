# LOTODA MQTT ESP AM2301

Bạn dễ dàng kết nối đến LOTODA platform bằng Board ESP8266 để tạo một dự án đọc và hiển thị nhiệt độ & độ ẩm trên app Lotoda! Hãy download code tại đây và sử dụng Arduno IDE để nạp code!

Để biết thêm chi tiết xem thêm video tại website: www.lotoda.vn và shop.lotoda.vn

# Sơ đồ đấu nối như sau:

Kết nối từ NodeMCU ESP8266 như sau:

- Chân GND -> GND AM2301 (đen)
- Chân 3V3 -> VCC AM2301 (đỏ)
- Chân D1 (GPIO 05) -> Signal AM2301 (vàng)

# Sơ đồ chân của NodeMCU ESP8266 như sau:
![](https://raw.githubusercontent.com/lotoda/Lotoda-Mqtt-Esp/master/nodemcudevkit_v1-0_io.jpg)

# Cảm biến nhiệt độ & độ ẩm AM2301 (DHT21)
![](https://imgaz.staticbg.com/thumb/large/oaupload/banggood/images/3D/60/0348cf90-f0ce-40c2-a23c-faf1edf2dafb.JPG)

Thông số kỹ thuật:
- Điện áp hoạt động: 3.3-5V.
- Dòng tiêu thụ: 300uA
- Dải đo độ ẩm: 0-99.9%.
- Dải đo nhiệt độ: -40 ~ 80 độ C.
- Sai số độ ẩm: +-3%.
- Sai số nhiệt độ: +-0.5 độ C

IoT LOTODA platform "Your IoT Connected Devices" www.lotoda.vn
