/**
 ******************************************************************************
 * @file    main.cpp
 * @author  STMicroelectronics
 * @version V1.0.0
 * @date    05 April 2019
 * @brief    test application for the STMicrolectronics
 *          X-NUCLEO-NFC04A1. NFC tag based on ST25DV device.
 *          This application makes use of C++ classes obtained from the C
 *          components' drivers.
 ******************************************************************************
*/
#include "mbed.h"
#include "x_nucleo_nfc04.h"
#include "stdio.h"
#include "string.h"

using namespace std;

DigitalOut led_1(D5);
DigitalOut led_2(D4);
DigitalOut led_3(D2);
DigitalOut LPD(D7);
DigitalIn MISO(D12);
I2C i2cChannel(I2C_SDA, I2C_SCL);
DigitalIn uButton(BUTTON1);
X_Nucleo_NFC04 X_Nucleo_Nfc04(&i2cChannel, &led_1, &led_2, &led_3, &LPD, &MISO);

int main()							
{

  const char uri_write_message[] = "polito.it";   // Uri message to write in the tag
  const char uri_write_protocol[] = URI_ID_0x01_STRING; // Uri protocol to write in the tag
  string uri_write = string(uri_write_protocol) + string(uri_write_message);



  const char SSID[] = "CLAB1"; // WiFi SSID to write in the tag
  Ndef_Wifi_Authentication_t Auth = NDEF_WIFI_AUTHENTICATION_WPA2;
  Ndef_Wifi_Encryption_t Encrypt = NDEF_WIFI_ENCRYPTION_AES;
  const char NetKey[] = "STM32ODE"; // WiFi password to write in the tag


  if(X_Nucleo_Nfc04.begin(&i2cChannel, &LPD) == 0) {
    printf("System Init done!");
    X_Nucleo_Nfc04.ledOn(&led_3);
  } else {
    printf("System Init failed!");
    while(1);
  }


	int ButtonPressed = 1;

	/* BY pressing the button the option to write the WiFi on the tag, or to write a link( or read from it ) is enabled */
	while(1)
	{
		/* Toggle ButtonPressed variable everytime button is pressed */
		if(uButton.read() == 0)
		{
			ButtonPressed++;
			if(ButtonPressed == 4)
				ButtonPressed = 1;
			while( uButton.read() == 0 ); //Debouncing
		}


		if(ButtonPressed == 1)
		{

			X_Nucleo_Nfc04.ledOn(&led_1);
			X_Nucleo_Nfc04.ledOff(&led_2);
			   X_Nucleo_Nfc04.ledOff(&led_3);
			wait_ms(100);
			if(X_Nucleo_Nfc04.writeWiFi(SSID, Auth, Encrypt, NetKey, &i2cChannel)) {
				/* Write failed! */
			}
		}
		if(ButtonPressed == 2)
		{

			X_Nucleo_Nfc04.ledOn(&led_2);
			X_Nucleo_Nfc04.ledOff(&led_1);
			   X_Nucleo_Nfc04.ledOff(&led_3);
			wait_ms(100);
			if(X_Nucleo_Nfc04.writeURI(uri_write_protocol, uri_write_message, "", &i2cChannel)) {
				/* Write failed! */
			}
		}
		if(ButtonPressed == 3)
		{
			   X_Nucleo_Nfc04.ledOn(&led_3);
			   X_Nucleo_Nfc04.ledOff(&led_1);
			   X_Nucleo_Nfc04.ledOff(&led_2);
			// Prepare device to readURI from NFC device
			string uri_read = X_Nucleo_Nfc04.readURI( &i2cChannel );

		  if(uri_read == "\0") {
			  /* Read failed! */
		  }


		  if(strcmp( uri_read.c_str(), uri_write.c_str() ) == 0) {
			  /* Successfully written and read! */
			  ButtonPressed = 0;

		  } else {
			  /* Read bad string! */
			   X_Nucleo_Nfc04.ledOff(&led_3);
			   X_Nucleo_Nfc04.ledOff(&led_1);
			   X_Nucleo_Nfc04.ledOff(&led_2);
		  }

		}
	}





}//end of main
