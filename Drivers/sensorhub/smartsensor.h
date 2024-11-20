//#define SS_ALGORITHM_CONFIGURATION 	0x50
//
//#define SS_WEARABLE_ALGORITHM		0x07
//
//#define SS_ALGOMODE					0x0A
//#define SS_AECENABLE				0x0B
//#define SS_AUTOPDCURRENTENABLE		0x12
//#define SS_TARGETPDPERIOD			0x0D
//#define SS_MOTIONTHRESHOLD			0x0E
//#define SS_MINPDCURRENT				0x0F
//#define SS_INITPDCURRENT			0x10
//#define SS_INITTINTOPTION			0x1A
//#define SS_MINTINTOPTION			0x13
//#define SS_MAXTINTOPTION			0x15
//#define SS_INITFSMPOPTION			0x1B
//#define SS_MINFSMPOPTION			0x14
//#define SS_MAXFSMPOPTION			0x16
//
//// 갑자기 왠 플레시 메모리???
////	dsInterface.parse_command_str("set_cfg ppg hr_conf_level 0");
////	dsInterface.parse_command_str("set_cfg ppg hr_expiration 5");
////#define SS_ a
////#define SS_ a
//
//#define SS_SCDENABLE				0x0C
//
//#define SS_SET_OUTPUT_MODE			0x10
//#define SS_REPORT_PERIOD 			0x02
//
////	dsInterface.parse_command_str("read ppg 9");
////#define SS_ a
//
//
//
////struct SmartSensor {
////	int ssbegin(void);
////
////	// ssWriteCommand();
////	int set_cfg_wearablesuite_algomode(int mode);
////	int set_cfg_wearablesuite_aecenable(int enable);
////	int set_cfg_wearablesuite_autopdcurrentenable(int enable);
////	int set_cfg_wearablesuite_targetpdperiod(int period);
////	int set_cfg_wearablesuite_motionthreshold(int threshold);
////	int set_cfg_wearablesuite_minpdcurrent(int current);
////	int set_cfg_wearablesuite_initpdcurrent(int current);
////	int set_cfg_wearablesuite_inittintoption(int option);
////	int set_cfg_wearablesuite_mintintoption(int option);
////	int set_cfg_wearablesuite_maxtintoption(int option);
////	int set_cfg_wearablesuite_initfsmpoption(int option);
////	int set_cfg_wearablesuite_minfsmpoption(int option);
////	int set_cfg_wearablesuite_maxfsmpoption(int option);
////
////	// ssReadCommand();
////
////	int ssWrite(void);
////	int ssRead(void);
////};
////
////int ssbegin(void){
////
////}
//
//
////dsInterface.parse_command_str("set_cfg wearablesuite algomode 0");
////dsInterface.parse_command_str("set_cfg wearablesuite aecenable 1");			  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite autopdcurrentenable 1"); // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite targetpdperiod 708");	  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite motionthreshold 32");	  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite minpdcurrent 32");		  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite initpdcurrent 32");	  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite inittintoption 3");	  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite mintintoption 0");		  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite maxtintoption 3");		  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite initfsmpoption 0");	  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite minfsmpoption 0");		  // dtriple
////dsInterface.parse_command_str("set_cfg wearablesuite maxfsmpoption 0");		  // dtriple
//
////dsInterface.parse_command_str("set_cfg ppg hr_conf_level 0");				  // dtriple
////dsInterface.parse_command_str("set_cfg ppg hr_expiration 5");				  // dtriple
////dsInterface.parse_command_str("set_cfg wearblesuite scdenable 1");			  // dtriple
////dsInterface.parse_command_str("set_cfg report_period 25");					  // dtriple
////dsInterface.parse_command_str("read ppg 9"); // => 여러 명령이 하나로 묶여 있음
//
//int ssBegin();

#define SS_ALGORITHM_CONFIGURATION 	0x50

#define SS_WEARABLE_ALGORITHM		0x07

#define SS_ALGOMODE					0x0A
#define SS_AECENABLE				0x0B
#define SS_AUTOPDCURRENTENABLE		0x12
#define SS_TARGETPDPERIOD			0x0D
#define SS_MOTIONTHRESHOLD			0x0E
#define SS_MINPDCURRENT				0x0F
#define SS_INITPDCURRENT			0x10
#define SS_INITTINTOPTION			0x1A
#define SS_MINTINTOPTION			0x13
#define SS_MAXTINTOPTION			0x15
#define SS_INITFSMPOPTION			0x1B
#define SS_MINFSMPOPTION			0x14
#define SS_MAXFSMPOPTION			0x16

// 갑자기 왠 플레시 메모리???
//	dsInterface.parse_command_str("set_cfg ppg hr_conf_level 0");
//	dsInterface.parse_command_str("set_cfg ppg hr_expiration 5");
//#define SS_ a
//#define SS_ a

#define SS_SCDENABLE				0x0C

#define SS_SET_OUTPUT_MODE			0x10
#define SS_REPORT_PERIOD 			0x02

#define MFIO_PORT					GPIOD
#define MFIO_PIN					GPIO_PIN_4
#define RSTN_PORT					GPIOD
#define RSTN_PIN					GPIO_PIN_5

#include "main.h"

int ssRead_setting();
int ssRead(uint8_t* rxdata, uint8_t len);
int ssInit();
void rxDataSplit(uint8_t* rxdata, struct ssDataEx_format* pRxdataStruct);
int ssBegin(uint8_t algomode);

struct ssDataPPGData{
	int ppg1; // Green counter
	int ppg2;
	int ppg3;
	int ppg4; // Green2 counter
	int ppg5; // IR LED counter
	int ppg6; // Red LED counter
};
struct ssDataAcc{
	int16_t accX;
	int16_t accY;
	int16_t accZ;
};
struct ssDataAlgo{
	uint8_t mode;
	uint16_t hr;
	uint8_t hrConfidence;
	uint16_t rr;
	uint8_t rrConfidence;
	uint8_t activity;
	uint32_t totalWalkSteps;
	uint32_t totalRunSteps;
	uint32_t totalEnergyExpInKcal;
	uint32_t totalAMRInKcal;
	uint8_t isLEDCurrent1Req;
	uint16_t ledCurrent1;
	uint8_t isLEDCurrent2Req;
	uint16_t ledCurrent2;
	uint8_t isLEDCurrent3Req;
	uint16_t ledCurrent3;
	uint8_t isIntegrationTimeReq;
	uint8_t integrationTime;
	uint8_t isSampleRateReq;
	uint8_t sampleRate;
	uint8_t sampleRateAverage;
	uint8_t WHRM_AFE_ctrl_state;
	uint8_t isHighMotionForHRM;
	uint8_t SCDstate;
	uint16_t r;
	uint8_t spo2Confidence;
	uint16_t spo2;
	uint8_t spo2Complete;
	uint8_t spo2QualityFlag;
	uint8_t spo2MotionFlag;
	uint8_t spo2PIFlag;
	uint8_t spo2RFlag;
	uint8_t status;
};
#ifdef __cplusplus
extern "C" {
#endif
	struct ssDataEx_format{
		uint8_t readStatus;
		struct ssDataPPGData ppg;
		struct ssDataAcc acc;
		struct ssDataAlgo algo;
	};
#ifdef __cplusplus
}
#endif

