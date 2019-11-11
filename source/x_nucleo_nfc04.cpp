#include "x_nucleo_nfc04.h"

extern sCCFileInfo CCFileStruct;

// This is a constructor

X_Nucleo_NFC04::X_Nucleo_NFC04(I2C* i2cChannel, DigitalOut* led_1, DigitalOut* led_2, DigitalOut* led_3, DigitalOut* LPD, DigitalIn* MISO){
	mi2cChannel = i2cChannel;
	mled_1 = led_1;
    mled_2 = led_2;
    mled_3 = led_3;
    mLPD = LPD;
    mMISO = MISO;
}

/**
  * @brief  This function initialize the device
  * @param  mi2cChannel : I2C Channel
  * @param  mLPD : A digital PIN
  * @retval status(int) : Return if the write operation is succesful
  */

int X_Nucleo_NFC04::begin(I2C* mi2cChannel, DigitalOut *mLPD) {
	int ret = 0;
	
	// Light some leds
	ledOn(mled_1);
	wait_ms( 300 );
	ledOn(mled_2);

	/* NFCTAG Init */
	ret = BSP_NFCTAG_Init(mi2cChannel, mLPD);
	if(ret != NDEF_OK)
		return ret;

	/* Reset MBEN Dynamic and initializes the CCFile struct */
	BSP_NFCTAG_GetExtended_Drv()->ResetMBEN_Dyn( mi2cChannel );
	if( NfcType5_NDEFDetection( mi2cChannel) != NDEF_OK )
	{
		CCFileStruct.MagicNumber = NFCT5_MAGICNUMBER_E1_CCFILE;
		CCFileStruct.Version = NFCT5_VERSION_V1_0;
		CCFileStruct.MemorySize = ( ST25DV_MAX_SIZE / 8 ) & 0xFF;
		CCFileStruct.TT5Tag = 0x05;
		/* Init of the Type Tag 5 component (M24LR) */
		ret = NfcType5_TT5Init( mi2cChannel );
		if (ret != NDEF_OK)
			return ret;
	}
	
	ledOff( mled_1 );
	wait_ms( 300 );
	ledOff( mled_2 );
	wait_ms( 300 );
	ledOff( mled_3 );
	wait_ms( 300 );
	return NDEF_OK;
}


/**
  * @brief  This function light on selected Led
  * @param  led : Led to be lit on
  * @retval None
  */
void X_Nucleo_NFC04::ledOn(DigitalOut* led) {
	led -> write(1);
}

/**
  * @brief  This function light off selected Led
  * @param  led : Led to be lit off
  * @retval None
  */

void X_Nucleo_NFC04::ledOff(DigitalOut* led) {
	*led = 0;
}


/**
  * @brief  This function write an URI into the NFC Tag
  * @param  protocol : Protocol of the uri to write
  * @param  uri : String containing the uri to write in the NFC Tag
  * @param  info : Additional info
  * @param  mi2cChannel : Object of the I2C channel
  * @retval status(int) : Return if the write operation is succesful
  */
int X_Nucleo_NFC04::writeURI(string protocol, string uri, string info, I2C* mi2cChannel) {
	sURI_Info _URI;
    strcpy( _URI.protocol,protocol.c_str() );
    strcpy( _URI.URI_Message,uri.c_str() );
    strcpy( _URI.Information,info.c_str() );


	return NDEF_WriteURI( &_URI, mi2cChannel );
}

/**
  * @brief  This function read an URI from the NFC Tag
  * @param  mi2cChannel : Object of the I2C channel
  * @retval string : Return the string that has been read from the NFC Tag
  */

string X_Nucleo_NFC04::readURI( I2C* mi2cChannel) {
    sURI_Info uri = {"","",""};
    sRecordInfo_t recordInfo;
    // increase buffer size for bigger messages
    if(NDEF_ReadNDEF(NDEF_Buffer, mi2cChannel))
        return (string)NULL;
    
    if(NDEF_IdentifyBuffer(&recordInfo, NDEF_Buffer))
        return (string)NULL;
    if(NDEF_ReadURI(&recordInfo,&uri))
        return (string)NULL;
    return string(uri.protocol) + string(uri.URI_Message);
}


/**
  * @brief  This function write WiFi Credentials into the NFC Tag
  * @param  NetworkSSID : SSID of the WiFi Network
  * @param  AuthenticationType :
  * @param  EncryptionType :
  * @param  NetworkKey : Password of the WiFi
  * @param  mi2cChannel : Object of the I2C channel
  * @retval status(int) : Return if the write operation is succesful
  */
uint16_t X_Nucleo_NFC04::writeWiFi(string NetworkSSID, Ndef_Wifi_Authentication_t AuthenticationType, Ndef_Wifi_Encryption_t EncryptionType, string NetworkKey, I2C* mi2cChannel ){

	sWifiTokenInfo _wifi;

	strcpy( _wifi.NetworkSSID,NetworkSSID.c_str() );
	_wifi.AuthenticationType = AuthenticationType;
	_wifi.EncryptionType = EncryptionType;
	strcpy( _wifi.NetworkKey,NetworkKey.c_str() );



	 return NDEF_WriteWifiToken(&_wifi, mi2cChannel );
}





