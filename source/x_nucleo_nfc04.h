#ifndef _X_NUCLEO_NFC04_H_
#define _X_NUCLEO_NFC04_H_
#include "BSP/x_nucleo_nfc04a1_nfctag.h"
#include "libNDEF/NDEFcommon.h"
#include "libNDEF/tagtype5_wrapper.h"
#include "libNDEF/lib_NDEF_URI.h"
#include "libNDEF/lib_NDEF_AAR.h"
#include "libNDEF/lib_NDEF_Bluetooth.h"
#include "libNDEF/lib_NDEF_Email.h"
#include "libNDEF/lib_NDEF_Handover.h"
#include "libNDEF/lib_NDEF_Geo.h"
#include "libNDEF/lib_NDEF_MyApp.h"
#include "libNDEF/lib_NDEF_SMS.h"
#include "libNDEF/lib_NDEF_Text.h"
#include "libNDEF/lib_NDEF_Vcard.h"
#include "libNDEF/lib_NDEF_Wifi.h"

//#include "ST25DV/st25dv.h"
//#include "x_nucleo_nfc04a1.h"
#include "mbed.h"
#include "PinNames.h"
#include "st25dv.h"

#include <string>

using namespace std;



/* Class of the NFC04A1
 *
 * begin: It initializes the device in order to start the communication with it
 * writeURI: Method that implements the write of an URI through I2C communication
 * readURI: Reading of an URI coming from an NFC tag
 * writeWiFi: Write the WiFi in the NFC tag
 * readWiFi: Read the WiFi coming from another device that writes on the NFC tag
 * ledON: It lights one of the three LED based on input PIN
 * ledOFF: It lights off one of the three LED based on input PIN
 *
 */
class X_Nucleo_NFC04 {
    public:
    X_Nucleo_NFC04(I2C* i2cChannel, DigitalOut* led_1, DigitalOut* led_2, DigitalOut* led_3, DigitalOut* LPD, DigitalIn* MISO);
    int begin(I2C* mi2cChannel, DigitalOut * mLPD);
    void ledOn(DigitalOut* led);
    void ledOff(DigitalOut* led);
    int writeURI(string protocol, string uri, string info, I2C* mi2cChannel);
    uint16_t writeWiFi(string NetworkSSID, Ndef_Wifi_Authentication_t AuthenticationType, Ndef_Wifi_Encryption_t EncryptionType, string NetworkKey, I2C* mi2cChannel );
    string readURI( I2C* mi2cChannel);
    private:
    DigitalOut *mled_1;
    DigitalOut *mled_2;
    DigitalOut *mled_3;
    DigitalOut *mLPD;
    DigitalIn *mMISO;
    I2C *mi2cChannel;

};

extern X_Nucleo_NFC04 X_Nucleo_Nfc04;

#endif
