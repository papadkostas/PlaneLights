/*
 * cli_static_cmd.h
 */
#include "plane.h"
#include "usbd_cdc_if.h"

extern uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

void cli_landingon_command(char *command_str);
void cli_landingoff_command(char *command_str);
void cli_strobeon_command(char *command_str);
void cli_strobeoff_command(char *command_str);
void cli_beaconon_command(char *command_str);
void cli_beaconoff_command(char *command_str);
void cli_navigationon_command(char *command_str);
void cli_navigationoff_command(char *command_str);
void cli_logoon_command(char *command_str);
void cli_logooff_command(char *command_str);
void cli_aircraft_command(char * command_str);
void cli_about_command(char *command_str);
void cli_reboot_command(char *command_str);
