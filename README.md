# Baby Sound Detector
[![Youtube Link](/picture%20and%20slide/baby-sound-detector.png)](https://youtu.be/kagJ3N3T314)

## ที่มา
ในตอนกลางคืนหรือตอนที่ผู้ปกครองของเด็กอยู่คนละห้องกับตัวของเด็ก แล้วเด็กเกิดร้องขึ้นมา ผู้ปกครองก็ไม่สามารถรู้ได้ว่าเด็กร้องและอาจจะทำให้เกิดอันตรายต่อตัวเด็กได้ ดังนั้นกลุ่มของพวกเราจึงได้มีแนวคิดที่จะทำเครื่องตรวจจับเสียงเด็กร้องนี้ขึ้นมา
## แนวคิดการออกแบบ
ถ้ามีเสียงร้องขึ้นมา อุปกรณ์ของเราก็จะสามารถตรวจจับเสียงร้องของเด็ก พอมีเสียงร้องของเด็กขึ้นไฟก็จะติดและจะส่ง Line Notifications สู่มือถือของผู้ปกครองเพื่อที่จะให้มาดูเด็กได้ทันเวลา

## Requirements
- python3
- usbdrv ไลบรารี V-USB
- ครอสคอมไพเลอร์ (cross compiler) เพื่อพัฒนาโปรแกรมสำหรับชิป AVR บนอุปกรณ์ Raspberry Pi
    ```
    sudo apt update
    sudo apt install gcc-avr avr-libc binutils-avr avrdude
    ```

## Hardware
1. Raspberry pi x1 
2. LED 1 ชุด 
3. ky-038 x1 
4. Breadboard x1 
5. สายไฟ x1 
6. Board NodeMCU - ATmega328p (Practicum Board v3.2 CPE. KU 2020-11) x1 
7. ตัวต้านทาน 330Ω x1 
8. สายแพร์ x1 
9. Practicum Breakout CPE KU x1

## Files and Directories
### env directory
คือ python virsual environment ของโปรเจคนี้

### firmware directory
คือ ที่เก็บโค้ดของตัว microcontroller ประกอบไปด้วย
1. main.c
    >ประกอบไปด้วยโค้ดส่วนที่เมื่อมีการตรวจพบเสียงถึงระดับที่เรากำหนด ก็จะไปเปลี่ยนให้ LED ติดเพื่อแสดงให้เห็นว่าสามารถตรวจจับเจอ และมีฟังก์ชันที่เอาไว้รับ request จากคอมพิวเตอร์ว่าจะเอาสถานะว่าตรวจพบหรือไม่ ส่งคืนค่าไปเป็น 1 ถ้าตรวจจับเสียงได้ ถ้าไม่ก็ 0
2. peri.c
    >เป็นไฟล์ที่เก็บรวบรวมฟังก์ชันทั้งหมดที่ใช้ใน main.c ประกอบไปด้วย
    - init_peri
        > ตั้งขาพินว่าจะให้พินไหนเป็น INPUT/OUTPUT
    - set_led
        > เลือกขาพินที่ LED ตั้งอยู่แล้วเซตได้ว่าจะให้ติดหรือดับ เป็น 1 ไฟจะติด > ถ้าไม่ก็ 0
    - read_adc
        > อ่านค่าเสียงที่ได้จาก sound_sensor
3. usbconfig.h
    >ไฟล์ตั้งค่า usb
4. peri.h
5. Makefile

### python directory
คือ ที่เก็บโค้ดที่ใช้สื่อสารกับ microcontroller ประกอบไปด้วย
1. practicum.py
    >มีคลาส McuBoard ที่มี read/write method ใช้สื่อสารกับ microcontroller และมีคลาส PeriBoard ที่มี method ทำให้ติดต่อสื่อสารกับ microcontroller ได้สะดวกมากขึ้นประกอบไปด้วย
    - get_sound
        > return sound value.
    - get_detect_sound
        > return Sound is detected or not.
2. monitor.py
    >ดูข้อมูลตั้งหมดที่ได้จาก sound_sensor โดยใช้ method จาก practicum.py แสดงผลทุกๆ 0.5 วินาที โดยจะมีโค้ดที่ใช้ส่งข้อความไปใน line notify อยู่ด้วย

### picture and slide
1. schematic.jpg
2. slide.pdf

### requirement.txt
python packepage ที่ใช้
```
pip install -r requirements.txt
```