
//#include <MAX20303.h>
////extern "C" {
//////class PMIC
//////{
//////public:
//////	PMIC(void);
//////	int init(void);
//////
//////	MAX20303 max20303;
//////};
//
//	int pmic_init(void);
//	MAX20303 max20303;
////}


int pmic_init(void);
//MAX20303 max20303;

int pmicSOCRead(unsigned char *batterylevel);
int isBATTCharging();

void testHaptic();
