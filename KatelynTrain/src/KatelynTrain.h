
#define PWM_PIN D2
#define POT_PIN A0

//max  MV that can be recorded on analog pins reading from 3V3 voltage source on Particle
#define MAX_ADC_BITS 4096
//usable PWM seems to be between 150-200 (update this if new data comes in, this was as of 11/29/2020)
#define PWM_RANGE 50
#define MAX_PWM 200
#define MIN_PWM 150

#define TEMP_PIN D3

#define OVERHEAT_TEMP 150

//the pot is paired with a 10K resistor on a voltage divider, so the lowest it will read is 1.65 V
#define MIN_BITS_WITH_POT 2048

int changeSpeed(String newSpeed);
int killSwitch(String argsNotImplemented);
void setup();
void lool();
void changeSpeedWithPotentiometer();
void checkTemp();