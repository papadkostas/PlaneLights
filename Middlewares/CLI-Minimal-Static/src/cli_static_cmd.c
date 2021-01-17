/*
 * cli_static_cmd.c
 */

#include "cli_static_cmd.h"

/*
 * Available commands table *
 * Structure { "command", "help string", command_function, number_of_args }
 */
cli_command_definition_t cli_command_table[] = {
		{ "landingon", "Landing lights. Usage: 0->OFF,1->ON\r\n", cli_landingon_command, 1},
		{ "landingoff", "Landing lights. Usage: 0->OFF,1->ON\r\n", cli_landingoff_command, 0},
		{ "strobeon", "Strobe lights. Usage: 0->OFF,1->ON\r\n", cli_strobeon_command, 0},
		{ "strobeoff", "Strobe lights. Usage: 0->OFF,1->ON\r\n", cli_strobeoff_command, 0},
		{ "beaconon", "Beacon lights. Usage: 0->OFF,1->ON\r\n", cli_beaconon_command, 0},
		{ "beaconoff", "Beacon lights. Usage: 0->OFF,1->ON\r\n", cli_beaconoff_command, 0},
		{ "navigationon", "Logo light. Usage: 0->OFF,1->ON\r\n", cli_navigationon_command, 0},
		{ "navigationoff", "Logo light. Usage: 0->OFF,1->ON\r\n", cli_navigationoff_command, 0},
		{ "logoon", "Logo light. Usage: 0->OFF,1->ON\r\n", cli_logoon_command, 0},
		{ "logooff", "Logo light. Usage: 0->OFF,1->ON\r\n", cli_logooff_command, 0},
		{ "aircraft", "Switch aircraft brand\r\n", cli_aircraft_command, 0},
		{ "reboot", "Reboot entire system\r\n", cli_reboot_command, 0 },
		{ "about", "About project\r\n", cli_about_command, 0 },
		{ NULL, NULL, NULL, 0 }
};

void cli_landingon_command(char *command_str) {
	uint8_t buf[] = "Turning on landing lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
}

void cli_landingoff_command(char *command_str) {
	uint8_t buf[] = "Turning off landing lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
}

void cli_strobeon_command(char *command_str){
	uint8_t buf[] = "Turning on Strobe lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void cli_strobeoff_command(char *command_str){
	uint8_t buf[] = "Turning off Strobe lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void cli_navigationon_command(char *command_str){
	uint8_t buf[] = "Turning on Navigation lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
}

void cli_beaconon_command(char *command_str){
	uint8_t buf[] = "Turning on Beacon lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void cli_beaconoff_command(char *command_str){
	uint8_t buf[] = "Turning off Beacon lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
}

void cli_navigationoff_command(char *command_str){
	uint8_t buf[] = "Turning off Navigation lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
}

void cli_logoon_command(char *command_str){
	uint8_t buf[] = "Turning on Logo lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
}

void cli_logooff_command(char *command_str){
	uint8_t buf[] = "Turning off Logo lights!\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
}

/*
 * ToDo: get parameter from command and switch brand
 * myplane.brand = airrbus or boeing
 */
void cli_aircraft_command(char * command_str) {

	CDC_Transmit_FS((uint8_t *)"Wrong parameter!\r\n", 26);
}

void cli_reboot_command(char *command_str) {
	uint8_t buf[] = "Rebooting system in 1 second...\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_Delay(1000);
	NVIC_SystemReset();
}

void cli_about_command(char *command_str) {
	uint8_t buf[] = "PlaneLights\r\nSource code: github.com/papadkostas/PlaneLights\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
}
