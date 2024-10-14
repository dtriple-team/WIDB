#include "smartsensor.h"
#include "main.h"

#include "i2c.h"
#include "tim.h"

#include "cmsis_os2.h"

#define slave_addr 	0b10101010
#define write_bit 	0b0
#define read_bit 	0b1

struct packit{
	uint8_t family_byte;
	uint8_t index_byte;
	uint8_t* write_byte;
	uint8_t wait_delay_for_data_ready;
	uint8_t read_status_byte;
	uint8_t* read_byte;
};

int set_command(uint8_t family_name, uint8_t description, uint8_t* cmd, uint8_t cmd_len){
	uint8_t buffer[128];

	buffer[0] = family_name;
	buffer[1] = description;
	for(int i=0; i<cmd_len; i++){
		buffer[2+i] = cmd[i];
	}

	HAL_GPIO_WritePin(MFIO_PORT, MFIO_PIN, GPIO_PIN_RESET);	// MFIO
	delay_us(277); // >= 250us

	int error = HAL_I2C_Master_Transmit(&hi2c2, slave_addr, buffer, cmd_len+2, HAL_MAX_DELAY);

	delay_us(80); // 8
	HAL_GPIO_WritePin(MFIO_PORT, MFIO_PIN, GPIO_PIN_SET);	// MFIO
	return error;
}

int get_command(uint8_t* rxbuffer, uint8_t temp_len){
//	HAL_Delay(2);
	delay_us(2000);

	HAL_GPIO_WritePin(MFIO_PORT, MFIO_PIN, GPIO_PIN_RESET);	// MFIO
	delay_us(277); // >= 250us

	int error = HAL_I2C_Master_Receive(&hi2c2, slave_addr, rxbuffer, temp_len, 10);

	delay_us(80); // 8
	HAL_GPIO_WritePin(MFIO_PORT, MFIO_PIN, GPIO_PIN_SET);	// MFIO

	return error;
}

int set_command_wearablesuite_algomode(uint8_t mode){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_ALGOMODE, mode};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return status;
}

int set_command_wearablesuite_aecenable(uint8_t enable){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_AECENABLE, enable};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_autopdcurrentenable(uint8_t enable){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_AUTOPDCURRENTENABLE, enable};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_targetpdperiod(uint16_t period){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_TARGETPDPERIOD, period>>8, period};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_motionthreshold(uint8_t threshold){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_MOTIONTHRESHOLD, threshold>>8, threshold};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_minpdcurrent(uint8_t current){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_MINPDCURRENT, current>>8, current};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_initpdcurrent(uint8_t current){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_INITPDCURRENT, current>>8, current};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_inittintoption(uint8_t option){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_INITTINTOPTION, option};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_mintintoption(uint8_t option){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_MINTINTOPTION, option};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_maxtintoption(uint8_t option){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_MAXTINTOPTION, option};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_initfsmpoption(uint8_t option){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_INITFSMPOPTION, option};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_minfsmpoption(uint8_t option){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_MINFSMPOPTION, option};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_wearablesuite_maxfsmpoption(uint8_t option){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_MAXFSMPOPTION, option};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

//int set_command_ppg_hr_conf_level(uint8_t mode){
//	return 0;
//}
//
//int set_command_ppg_hr_expiration(uint8_t mode){
//	return 0;
//}
//
int set_command_wearblesuite_scdenable(uint8_t enable){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {SS_SCDENABLE, enable};
	int status = set_command(SS_ALGORITHM_CONFIGURATION, SS_WEARABLE_ALGORITHM, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int set_command_report_period(uint8_t period){
	uint8_t rxbuffer[1] = {0,};
	uint8_t write[] = {period};
	int status = set_command(SS_SET_OUTPUT_MODE, SS_REPORT_PERIOD, write, sizeof(write));
	status = (status << 8) | get_command(rxbuffer, sizeof(rxbuffer));
	return 0;
}

int read_ppg_9_setting (void){

	uint8_t rxbuffer_1[1] = {0,};
	uint8_t rxbuffer_3[3] = {0,};

	uint8_t temp[] = {};
	set_command(0x13, 0x01, temp, sizeof(temp));
	get_command(rxbuffer_3, sizeof(rxbuffer_3));

	uint8_t data_type[] = {0x03};
	set_command(0x10, 0x00, data_type, sizeof(data_type));
	get_command(rxbuffer_1, sizeof(rxbuffer_1));

	// set_fifo_thresh
	uint8_t thresh[] = {0x05};
	set_command(0x10, 0x01, thresh, sizeof(data_type));
	get_command(rxbuffer_1, sizeof(rxbuffer_1));

	// enable_algo
	uint8_t mode[] = {0x02}; // extended algorithm report => 76byte(data) + 1byte(status)
	set_command(0x52, 0x07, mode, sizeof(data_type)); // 1
	osDelay(320);
	get_command(rxbuffer_1, sizeof(rxbuffer_1));

	uint8_t algo_cfg[] = {0x18};
	set_command(0x51, 0x07, algo_cfg, sizeof(algo_cfg));
	get_command(rxbuffer_3, sizeof(rxbuffer_3));

	return 0;
}

int read_ppg_9(uint8_t* rxdata, uint8_t rxbuff_len){

	uint8_t rxbuffer_2[2] = {0,};

	uint8_t len = 0;
	uint8_t status = 0;

	set_command(0x00, 0x00, 0, 0);
	get_command(rxbuffer_2, sizeof(rxbuffer_2));
	status = rxbuffer_2[1];

	if(((status >> 3) & 0x01) != 0x01){
		return -1;
	}

	set_command(0x12, 0x00, 0, 0);
	get_command(rxbuffer_2, sizeof(rxbuffer_2));
	len = rxbuffer_2[1];

	set_command(0x12, 0x01, 0, 0);
	HAL_GPIO_WritePin(MFIO_PORT, MFIO_PIN, GPIO_PIN_RESET);	// MFIO
	delay_us(277);
	for(uint8_t i=0; i<len; i++){
		HAL_I2C_Master_Receive(&hi2c2, slave_addr, rxdata, rxbuff_len, HAL_MAX_DELAY);
		delay_us(5);
	}
	delay_us(8);
	HAL_GPIO_WritePin(MFIO_PORT, MFIO_PIN, GPIO_PIN_SET);	// MFIO

	return 0;
}

int ssInit(){
	HAL_GPIO_WritePin(RSTN_PORT, RSTN_PIN, GPIO_PIN_SET);	// RSTN
	HAL_GPIO_WritePin(MFIO_PORT, MFIO_PIN, GPIO_PIN_RESET);	// MFIO
	osDelay(100);
	HAL_GPIO_WritePin(RSTN_PORT, RSTN_PIN, GPIO_PIN_SET); 	// RSTN
	HAL_GPIO_WritePin(RSTN_PORT, RSTN_PIN, GPIO_PIN_RESET);	// RSTN
	osDelay(5);
	HAL_GPIO_WritePin(MFIO_PORT, MFIO_PIN, GPIO_PIN_SET);	// MFIO
	osDelay(5);
	HAL_GPIO_WritePin(RSTN_PORT, RSTN_PIN, GPIO_PIN_SET); 	// RSTN

	osDelay(1500);

	return 0;
}

int ssBegin(){
	set_command_wearablesuite_algomode(0);
	set_command_wearablesuite_aecenable(1);
	set_command_wearablesuite_autopdcurrentenable(1);
	set_command_wearablesuite_targetpdperiod(0x708);
	set_command_wearablesuite_motionthreshold(0x32);
	set_command_wearablesuite_minpdcurrent(0x32);
	set_command_wearablesuite_initpdcurrent(0x32);
	set_command_wearablesuite_inittintoption(3);
	set_command_wearablesuite_mintintoption(0);
	set_command_wearablesuite_maxtintoption(3);
	set_command_wearablesuite_initfsmpoption(0);
	set_command_wearablesuite_minfsmpoption(0);
	set_command_wearablesuite_maxfsmpoption(0);
//	set_command_ppg_hr_conf_level(0);
//	set_command_ppg_hr_expiration(5);
	set_command_wearblesuite_scdenable(1);
	set_command_report_period(1); // 몇개를 모아서 한번에 알려줄까?

	return 0;
}

int ssRead_setting(){
	read_ppg_9_setting();
	return 0;
}

int ssRead(uint8_t* rxdata, uint8_t len){
	return read_ppg_9(rxdata, len);
}

void rxDataSplit(uint8_t* rxdata, struct ssDataEx_format* pRxdataStruct){
	pRxdataStruct->readStatus = rxdata[0];

	pRxdataStruct->ppg.ppg1 = rxdata[0+1] << 8  | rxdata[1+1] << 8  | rxdata[2+1] << 8;
	pRxdataStruct->ppg.ppg2 = rxdata[3+1] << 8  | rxdata[4+1] << 8  | rxdata[5+1] << 8;
	pRxdataStruct->ppg.ppg3 = rxdata[6+1] << 8  | rxdata[7+1] << 8  | rxdata[8+1] << 8;
	pRxdataStruct->ppg.ppg4 = rxdata[9+1] << 8  | rxdata[10+1] << 8 | rxdata[11+1] << 8;
	pRxdataStruct->ppg.ppg5 = rxdata[12+1] << 8 | rxdata[13+1] << 8 | rxdata[14+1] << 8;
	pRxdataStruct->ppg.ppg6 = rxdata[15+1] << 8 | rxdata[16+1] << 8 | rxdata[17+1] << 8;

	pRxdataStruct->acc.accX = rxdata[18+1] << 8 | rxdata[19+1] << 0;
	pRxdataStruct->acc.accY = rxdata[20+1] << 8 | rxdata[21+1] << 0;
	pRxdataStruct->acc.accZ = rxdata[22+1] << 8 | rxdata[23+1] << 0;

	pRxdataStruct->algo.hr  = rxdata[25+1] << 8 | rxdata[26+1] << 0;

	pRxdataStruct->algo.SCDstate  = rxdata[64+1];

	pRxdataStruct->algo.spo2  = rxdata[68+1] << 8 | rxdata[69+1] << 0;

	pRxdataStruct->algo.totalWalkSteps  = rxdata[32+1] << 24 | rxdata[33+1] << 16 | rxdata[34+1] << 8 | rxdata[35+1] << 0;

	return;
}

