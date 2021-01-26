/*
 * cli_static_cmd.c
 */

#include "cli_static_cmd.h"

/*
 * Available commands table *
 * Structure { "command", "help string", command_function, number_of_args }
 */
cli_command_definition_t cli_command_table[] = {
		{ "landing", "Landing lights. \r\nParameter 1 : on,off\r\nParameter 2 : pulseon,pulseoff\r\n", cli_landinglights_cmd, 1},
		{ "strobe", "Strobe lights. Options: on,off.\r\n", cli_strobelights_cmd, 1},
		{ "anticollision", "Anti-collision lights. Options: on,off.\r\n", cli_anticollition_cmd, 1},
		{ "navigation", "Navigation lights. Options: on,off.\r\n", cli_navigationlights_cmd, 1},
		{ "logo", "Logo lights. Options: on,off.\r\n", cli_logolights_cmd, 1},
		{ "intensity", "Light intensity. Options: dim,bright.\r\n", cli_lightintensity_cmd, 1},
		{ "aircraft", "Switch aircraft brand. Options: boeing,airbus.\r\n", cli_aircraft_cmd, 1},
		{ "reboot", "Reboot entire system.\r\n", cli_reboot_cmd, 0 },
		{ "about", "About project.\r\n", cli_about_cmd, 0 },
		{ NULL, NULL, NULL, 0 }
};

char param_on[2] = "on";
char param_off[3] = "off";
char param_dim[3] = "dim";
char param_bright[] = "bright";
char param_pulseon[7] = "pulseon";
char param_pulseoff[8] = "pulseoff";
char param_boeing[6] = "boeing";
char param_airbus[6] = "airbus";
char invalid_param[] = "Not a valid parameter!\r\n";
uint32_t sizeof_invalid_param = sizeof(invalid_param);
char about[] = "PlaneLights\r\nSource code: github.com/papadkostas/PlaneLights\r\n";
uint32_t sizeof_about = sizeof(about);


void cli_landinglights_cmd(char *command_str) {
	int i = 1;
	int str_len = 0;

	// get the first parameter
	char *param = cli_get_parameter(command_str, i, &str_len);
	// loop until there are no more valid parameters
	while (param != NULL) {
//		char param_to_process[str_len];
//		strncpy(param_to_process,param,str_len);
//		if(i == 1) {
			if(strncmp(param, param_on,str_len) == 0){

				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
				htim4.Instance->CCR1 = 10;
				htim4.Instance->CCR1 = 10;
				// increment index
				i++;

				// get the next parameter
				if((param = cli_get_parameter(command_str, i, &str_len))!= NULL) {
					continue;
				}
				else {
					uint8_t buf[] = "Turning on landing lights!\r\n";
					CDC_Transmit_FS(buf, strlen((const char*)buf));
					return;
				}
			}
			else if(strncmp(param, param_off,str_len) == 0){
				uint8_t buf[] = "Turning off landing lights!\r\n";
				CDC_Transmit_FS(buf, strlen((const char*)buf));
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
				HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_2);
			}
			else if(strncmp(param, param_pulseon,str_len) == 0){
				uint8_t buf[] = "Turning on pulsating landing lights!\r\n";
				CDC_Transmit_FS(buf, strlen((const char*)buf));
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, aCC_Landing_Buffer1, samples);
				HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, aCC_Landing_Buffer2, samples);
			}
			else if(strncmp(param, param_pulseoff, str_len) == 0){
				uint8_t buf[] = "Turning off pulsating landing lights!\r\n";
				CDC_Transmit_FS(buf, strlen((const char*)buf));
				HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
			}
			else {
				CDC_Transmit_FS(invalid_param, sizeof_invalid_param);
			}

		// increment index
		i++;

		// get the next parameter
		param = cli_get_parameter(command_str, i, &str_len);
	}
}

void cli_strobelights_cmd(char *command_str){
	int str_len = 0;

	// get the first parameter
	char *param = cli_get_parameter(command_str, 1, &str_len);
	// loop until there are no more valid parameters
	if(strcmp(param, param_on) == 0){
		uint8_t buf[] = "Turning on Strobe lights!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	}
	else if(strcmp(param, param_off) == 0){
		uint8_t buf[] = "Turning off Strobe lights!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	}
	else {
		CDC_Transmit_FS(invalid_param, sizeof_invalid_param);
	}
}

void cli_anticollition_cmd(char *command_str){
	int str_len = 0;

	// get the first parameter
	char *param = cli_get_parameter(command_str, 1, &str_len);
	// loop until there are no more valid parameters
	if(strcmp(param, param_on) == 0){
		uint8_t buf[] = "Turning on Anti-collision lights!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	}
	else if(strcmp(param, param_off) == 0){
		uint8_t buf[] = "Turning off Anti-collision lights!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	}
	else {
		CDC_Transmit_FS(invalid_param, sizeof_invalid_param);
	}
}

void cli_navigationlights_cmd(char *command_str){
	int str_len = 0;

	// get the first parameter
	char *param = cli_get_parameter(command_str, 1, &str_len);
	// loop until there are no more valid parameters
	if(strcmp(param, param_on) == 0){
		uint8_t buf[] = "Turning on Navigation lights!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	}
	else if(strcmp(param, param_off) == 0){
		uint8_t buf[] = "Turning off Navigation lights!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
	}
	else {
		CDC_Transmit_FS(invalid_param, sizeof_invalid_param);
	}
}

void cli_logolights_cmd(char *command_str){
	int str_len = 0;

	// get the first parameter
	char *param = cli_get_parameter(command_str, 1, &str_len);
	// loop until there are no more valid parameters
	if(strcmp(param, param_on) == 0){
		uint8_t buf[] = "Turning on Logo lights!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	}
	else if(strcmp(param, param_off) == 0){
		uint8_t buf[] = "Turning off Logo lights!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
	}
	else {
		CDC_Transmit_FS(invalid_param, sizeof_invalid_param);
	}
}

void cli_lightintensity_cmd(char *command_str) {
	int str_len = 0;

	// get the first parameter
	char *param = cli_get_parameter(command_str, 1, &str_len);
	// loop until there are no more valid parameters
	if(strcmp(param, param_dim) == 0){
		uint8_t buf[] = "Dimmed LED mode!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
	}
	else if(strcmp(param, param_bright) == 0){
		uint8_t buf[] = "Bright LED mode!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));

	}
	else {
		CDC_Transmit_FS(invalid_param, sizeof_invalid_param);
	}
}

void cli_aircraft_cmd(char * command_str) {
	int str_len = 0;

	// get the first parameter
	char *param = cli_get_parameter(command_str, 1, &str_len);
	// loop until there are no more valid parameters
	if(strcmp(param, param_boeing) == 0){
		uint8_t buf[] = "Switching mode to Boeing!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		myplane.brand = boeing;
	}
	else if(strcmp(param, param_airbus) == 0){
		uint8_t buf[] = "Switching mode to Airbus!\r\n";
		CDC_Transmit_FS(buf, strlen((const char*)buf));
		myplane.brand = airbus;
	}
	else {
		CDC_Transmit_FS(invalid_param, sizeof_invalid_param);
	}
}

void cli_reboot_cmd(char *command_str) {
	uint8_t buf[] = "Rebooting system in 1 second...\r\n";
	CDC_Transmit_FS(buf, strlen((const char*)buf));
	HAL_Delay(1000);
	NVIC_SystemReset();
}

void cli_about_cmd(char *command_str) {
	CDC_Transmit_FS(about, sizeof_about);
}
