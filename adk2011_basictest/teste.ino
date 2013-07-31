#include "Usb.h"
#include "AndroidAccessory.h"
#include <LiquidCrystal.h>
#include <stdlib.h>

AndroidAccessory acc("Orion",
		     "Orionino",
		     "Orionino Smart Charger",
		     "0.1",
		     "http://aoriani.blogspot.com",
		     "0000000012345678");


LiquidCrystal lcd(8, 9, 2, 5, 6, 3);

void setup(){
    Serial.begin(9600);
    Serial.println("Starting Android Charger");
    lcd.begin(16, 2);              // start the library
    lcd.setCursor(0,0);
    lcd.print("Android Charger"); // print a simple message
    acc.powerOn();
}

void loop(){

    if (acc.isConnected()) {
        byte size;        
        acc.read(&size, sizeof(size));
        byte* buffer = (byte*) malloc(sizeof(byte)*(size+1));
        acc.read(buffer, size);
        buffer[size] = '\0';
        lcd.clear();
        lcd.print((char*)buffer);
        free(buffer);
        char text[] = "Olá phone!";
        size = sizeof(text);
        acc.write(&size, sizeof(byte));
        acc.write (text, sizeof(text));
    }

    delay(100);
}
