/*
 * cli_static_cmd.h
 */
#include "plane.h"
#include "usbd_cdc_if.h"

void cli_landinglights_cmd(char *command_str);
void cli_strobelights_cmd(char *command_str);
void cli_anticollition_cmd(char *command_str);
void cli_navigationlights_cmd(char *command_str);
void cli_logolights_cmd(char *command_str);
void cli_lightintensity_cmd(char *command_str);
void cli_aircraft_cmd(char * command_str);
void cli_about_cmd(char *command_str);
void cli_reboot_cmd(char *command_str);
