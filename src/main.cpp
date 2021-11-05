#include "Arduino.h"
#include <SPI.h>
#include "Ucglib.h"
#include "qrcode.h"

#define  pin_backlight      27
#define SCREEN_OFFSET_X     6
#define SCREEN_OFFSET_Y     -9
#define QRCODE_BLOCK        3
#define QRCODE_VERSION      5

// Ucglib_ST7735_18x128x160_SWSPI ucg(/*sclk=*/18, /*data=*/23, /*cd=*/17, /*cs=*/5, /*reset=*/16);  //SW SPI
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/17, /*cs=*/5, /*reset=*/16);      //HW SPI, sclk=18, mosi=23
// Create the QR code
QRCode qrcode;

void generateQRCode(String message)
{
    uint8_t qrcodeData[qrcode_getBufferSize(QRCODE_VERSION)];
    // Start time
    uint32_t dt = millis();
   
    qrcode_initText(&qrcode, qrcodeData, QRCODE_VERSION, 0, message.c_str());

    // Delta time
    dt = millis() - dt;

    Serial.print("QR Code Generation Time: ");
    Serial.print(dt);
    Serial.print("\n");
  
    ucg.setColor(0, 0, 0);

    int offsetX = 10;
    int offsetY = 45;

    for (uint8_t y = 0; y < qrcode.size; y++)
    {
        offsetX = 0;
        for (uint8_t x = 0; x < qrcode.size; x++)
        {
            if (qrcode_getModule(&qrcode, x, y))
            {
                ucg.setColor(255, 255, 255);
                ucg.drawBox(SCREEN_OFFSET_X + x + offsetX, SCREEN_OFFSET_Y + y + offsetY, QRCODE_BLOCK, QRCODE_BLOCK);
                // ucg.drawFrame(SCREEN_OFFSET_X + x + offsetX, SCREEN_OFFSET_Y + y + offsetY, QRCODE_BLOCK, QRCODE_BLOCK);
            }
            // 바탕이 검은색이어서 필요없음
            // else
            // {
            //     ucg.setColor(0, 0, 0);                
            //     ucg.drawBox(SCREEN_OFFSET_X + x + offsetX, SCREEN_OFFSET_Y + y + offsetY, QRCODE_BLOCK, QRCODE_BLOCK);
            //     ucg.drawFrame(SCREEN_OFFSET_X + x + offsetX, SCREEN_OFFSET_Y + y + offsetY, QRCODE_BLOCK, QRCODE_BLOCK);
            // }
            offsetX += QRCODE_BLOCK - 1;
        }
        offsetY += QRCODE_BLOCK - 1;
    }
    // Bottom quiet zone
}

void lcd_on_off(bool on_off){
    if(on_off)
        digitalWrite(pin_backlight, 1);
    else
        digitalWrite(pin_backlight, 0);
}


String boxMsg = "https://yongseung.pythonanywhere.com/mail/reg/?b=A002-001B&p=0001&m=123456&n=홍길동";

void setup(void)
{
    Serial.begin(115200);

    pinMode(pin_backlight, OUTPUT);
    lcd_on_off(0);  

    ucg.begin(UCG_FONT_MODE_TRANSPARENT);
    ucg.clearScreen();
    ucg.setRotate180();

    ucg.setFont(ucg_font_ncenR12_tr);
    ucg.setColor(1, 255, 0,0);
    ucg.setPrintPos(10,25);
    ucg.print("@A002 - 002B ");
}

void loop(void)
{   

    // 문이 열리거나 키가 눌러지면 deep sleep mode 에서 깨어난다.

    // 물체 센서를 읽어 드린다. 

    // 배터리 상태를 읽어드린다.

    // 바코드 리더기에 데이터가 들어오면 등기번호를 저장한다.
            

    // 센서에 물건이 인식식되면(키가 눌러지면) QR 코드를 작성 후 표시
    //
    // 작성 후 LCD ON
    generateQRCode(boxMsg);           //draw qrcode    
    lcd_on_off(1);

    //추가 누른 버튼이 없으면 30초 후 LCD OFF and deep sleep mode
    //
    for (;;)
        ;
}