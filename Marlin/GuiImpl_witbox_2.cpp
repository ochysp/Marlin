#include "GuiImpl_witbox_2.h"
#include "GuiBitmaps_witbox_2.h"
#include "GuiAction.h"

#include "Screen.h"
#include "ScreenMenu.h"
#include "ScreenPrint.h"
#include "ScreenDialog.h"
#include "ScreenSelector.h"
#include "ScreenList.h"
#include "ScreenStatus.h"
#include "ScreenTransition.h"
#include "ScreenAction.h"
#include "ScreenPrint.h"

#include "LightManager.h"
#include "PrintManager.h"
#include "SteppersManager.h"
#include "TemperatureManager.h"

#include "language.h"

namespace screen
{
	Size icon_size = Size(icon_width, icon_height);
	///////////////////////
	// Instantiate Icons //
	///////////////////////
	Icon icon_nosd                = Icon(icon_size, bits_nosd_normal, bits_nosd_focused, MSG_NOSD);
	Icon icon_sd                  = Icon(icon_size, bits_sd_normal, bits_sd_focused, MSG_SD);
	Icon icon_filament_unload     = Icon(icon_size, bits_filament_unload_normal, bits_filament_unload_focused, MSG_FILAMENT_UNLOAD);
	Icon icon_filament_load       = Icon(icon_size, bits_filament_load_normal, bits_filament_load_focused, MSG_FILAMENT_LOAD);
	Icon icon_leveling            = Icon(icon_size, bits_leveling_normal, bits_leveling_focused, MSG_LEVELING);
	Icon icon_homing              = Icon(icon_size, bits_homing_normal, bits_homing_focused, MSG_HOMING);
	Icon icon_steppers            = Icon(icon_size, bits_steppers_normal, bits_steppers_focused, MSG_STEPPERS);
	Icon icon_steppers_off        = Icon(icon_size, bits_steppers_off_normal, bits_steppers_off_focused, MSG_STEPPERS_OFF);
	Icon icon_moveaxis            = Icon(icon_size, bits_moveaxis_normal, bits_moveaxis_focused, MSG_MOVEAXIS);
	Icon icon_temperature         = Icon(icon_size, bits_temperature_normal, bits_temperature_focused, MSG_TEMPERATURE);
	Icon icon_lightled_disable    = Icon(icon_size, bits_lightled_disable_normal, bits_lightled_disable_focused, MSG_LIGHTLED_DISABLE);
	Icon icon_lightled            = Icon(icon_size, bits_lightled_normal, bits_lightled_focused, MSG_LIGHTLED);
	Icon icon_info                = Icon(icon_size, bits_info_normal, bits_info_focused, MSG_INFO);
	Icon icon_play                = Icon(icon_size, bits_play_normal, bits_play_focused, MSG_PLAY);
	Icon icon_pause               = Icon(icon_size, bits_pause_normal, bits_pause_focused, MSG_PAUSE);
	Icon icon_stop                = Icon(icon_size, bits_stop_normal, bits_stop_focused, MSG_STOP);
	Icon icon_change_filament     = Icon(icon_size, bits_change_filament_normal, bits_change_filament_focused, MSG_CHANGE_FILAMENT);
	Icon icon_change_speed        = Icon(icon_size, bits_change_speed_normal, bits_change_speed_focused, MSG_CHANGE_SPEED);
	Icon icon_back                = Icon(icon_size, bits_back_normal, bits_back_focused, MSG_BACK);
	Icon icon_retry               = Icon(icon_size, bits_retry_normal, bits_retry_focused, MSG_RETRY);
	Icon icon_ok                  = Icon(icon_size, bits_ok_normal, bits_ok_focused, MSG_OK2);

	Icon icon_move_x              = Icon(icon_size, bits_x_axis_normal, bits_x_axis_focused, MSG_SCREEN_MOVE_X);
	Icon icon_move_y              = Icon(icon_size, bits_y_axis_normal, bits_y_axis_focused, MSG_SCREEN_MOVE_Y);
	Icon icon_move_z              = Icon(icon_size, bits_z_axis_normal, bits_z_axis_focused, MSG_SCREEN_MOVE_Z);
	Icon icon_move_e              = Icon(icon_size, bits_e_axis_normal, bits_e_axis_focused, MSG_SCREEN_MOVE_E);

	Icon icon_move_01mm           = Icon(icon_size, bits_01mm_normal, bits_01mm_focused, MSG_SCREEN_MOVE_01MM);
	Icon icon_move_1mm            = Icon(icon_size, bits_1mm_normal, bits_1mm_focused, MSG_SCREEN_MOVE_1MM);
	Icon icon_move_10mm           = Icon(icon_size, bits_10mm_normal, bits_10mm_focused, MSG_SCREEN_MOVE_10MM);




	/////////////////////////
	// Instantiate Screens //
	/////////////////////////
	//Logo Splash
	ScreenDialog screen_logo            = ScreenDialog(MSG_SCREEN_LOGO,"");
	//Main Menu
	ScreenMenu screen_main              = ScreenMenu(MSG_SCREEN_MAIN);
	//SD Card screens
	ScreenList screen_SD_list           = ScreenList(MSG_SCREEN_SD_LIST);
	ScreenMenu screen_SD_confirm        = ScreenMenu(MSG_SCREEN_SD_CONFIRM);
	ScreenAction<void> screen_SD_OK		= ScreenAction<void>(MSG_SCREEN_SD_BACK, PrintManager::startPrint);
	Screen screen_SD_back               = Screen(MSG_SCREEN_SD_BACK, Screen::SIMPLE);
	//Unload Filament screens
	ScreenSelector<void, uint16_t> screen_unload_select = ScreenSelector<void, uint16_t>(MSG_SCREEN_UNLOAD_TITLE, 170, 230, default_temp_change_filament, action_set_temperature);
	ScreenTransition<float> screen_unload_heating	= ScreenTransition<float>(MSG_SCREEN_UNLOAD_TITLE, MSG_SCREEN_UNLOAD_ABORT, &TemperatureManager::getInstance());
	ScreenDialog screen_unload_pull     = ScreenDialog(MSG_SCREEN_UNLOAD_TITLE,MSG_SCREEN_UNLOAD_CONTINUE);
	ScreenMenu screen_unload_confirm    = ScreenMenu(MSG_SCREEN_UNLOAD_CONFIRM);
	//Load Filament screens
	ScreenSelector<void, uint16_t> screen_load_select   = ScreenSelector<void, uint16_t>(MSG_SCREEN_LOAD_TITLE, 170, 230, default_temp_change_filament, action_set_temperature);
	ScreenTransition<float> screen_load_heating	= ScreenTransition<float>(MSG_SCREEN_LOAD_TITLE, MSG_SCREEN_LOAD_ABORT, &TemperatureManager::getInstance());
	ScreenDialog screen_load_press      = ScreenDialog(MSG_SCREEN_LOAD_TITLE, MSG_SCREEN_LOAD_CONTINUE);
	ScreenMenu screen_load_confirm      = ScreenMenu(MSG_SCREEN_LOAD_CONFIRM);
	//Level Plate screens
	ScreenMenu screen_level_confirm     = ScreenMenu(MSG_SCREEN_LEVEL_TITLE);
	ScreenTransition<float> screen_level_cooling	= ScreenTransition<float>(MSG_SCREEN_LEVEL_TITLE, MSG_SCREEN_LEVEL_ABORT, &TemperatureManager::getInstance());
	ScreenDialog screen_level1          = ScreenDialog("",MSG_SCREEN_LEVEL1);
	ScreenDialog screen_level2          = ScreenDialog("",MSG_SCREEN_LEVEL2);
	ScreenDialog screen_level3          = ScreenDialog("",MSG_SCREEN_LEVEL3);
	ScreenDialog screen_level4          = ScreenDialog("",MSG_SCREEN_LEVEL4);
	ScreenMenu screen_level_retry       = ScreenMenu(MSG_SCREEN_LEVEL_RETRY);
	//AutoHome
	ScreenAction<void> screen_autohome = ScreenAction<void>(MSG_SCREEN_AUTOHOME, action_homing);
	//Steppers
	ScreenStatus<bool, void> screen_stepper   = ScreenStatus<bool, void>(MSG_SCREEN_STEPPER, SteppersManager::setState, &SteppersManager::getInstance());
	//Move Axis screens
	ScreenMenu screen_move              = ScreenMenu(MSG_SCREEN_MOVE);
	Screen screen_move_back2main        = Screen(MSG_SCREEN_MOVE_2MAIN, Screen::SIMPLE);
	ScreenMenu screen_move_x            = ScreenMenu(MSG_SCREEN_MOVE_X);
	ScreenMenu screen_move_y            = ScreenMenu(MSG_SCREEN_MOVE_Y);
	ScreenMenu screen_move_z            = ScreenMenu(MSG_SCREEN_MOVE_Z);
	ScreenMenu screen_move_e            = ScreenMenu(MSG_SCREEN_MOVE_E);
	Screen screen_move_back2move        = Screen(MSG_SCREEN_MOVE_2MOVE, Screen::SIMPLE);
	ScreenSelector<void, uint16_t> screen_move_10       = ScreenSelector<void, uint16_t>(MSG_SCREEN_MOVE_10MM, 0, 100, 50, action_set_temperature);
	ScreenSelector<void, uint16_t> screen_move_1        = ScreenSelector<void, uint16_t>(MSG_SCREEN_MOVE_1MM, 0, 100, 50, action_set_temperature);
	ScreenSelector<void, uint16_t> screen_move_01       = ScreenSelector<void, uint16_t>(MSG_SCREEN_MOVE_01MM, 0, 100, 50, action_set_temperature);
	//Temperature
	ScreenSelector<void, uint16_t> screen_temperature   = ScreenSelector<void, uint16_t>(MSG_SCREEN_TEMP_TITLE, 0, 250, default_temp_change_filament, action_set_temperature);
	//Light
	ScreenStatus<bool, void> screen_light = ScreenStatus<bool, void>(MSG_SCREEN_LIGHT, LightManager::setState, &LightManager::getInstance());
	//Info
	ScreenDialog screen_info            = ScreenDialog(MSG_SCREEN_INFO,MSG_SCREEN_INFO);

	//Print screen
	ScreenPrint screen_print            = ScreenPrint(MSG_SCREEN_PRINT_PRINTING);
	//Play/Pause
	//ScreenStatus screen_play_pause      = ScreenStatus("Pause", action_pause_print);
	//Stop
	ScreenMenu screen_stop_confirm      = ScreenMenu(MSG_SCREEN_STOP_CONFIRM);
	Screen screen_stop_back             = Screen(MSG_SCREEN_STOP_BACK, Screen::SIMPLE);
	ScreenAction<void> screen_stop_OK = ScreenAction<void>(MSG_SCREEN_STOP_OK, action_stop_print);
	//Change Filament Screens
	ScreenMenu screen_change_confirm	= ScreenMenu(MSG_SCREEN_CHANGE_CONFIRM);
	ScreenDialog screen_change_start    = ScreenDialog("",MSG_SCREEN_CHANGE_START);
	ScreenDialog screen_change_pullout  = ScreenDialog("",MSG_SCREEN_CHANGE_PULLOUT);
	ScreenDialog screen_change_insert   = ScreenDialog("",MSG_SCREEN_CHANGE_INSERT);
	ScreenMenu screen_change_retry      = ScreenMenu(MSG_SCREEN_CHANGE_RETRY);
	//Change Speed screen
	ScreenSelector<void, uint16_t> screen_speed			= ScreenSelector<void, uint16_t>(MSG_SCREEN_SPEED, 10, 400, 100, action_set_temperature);


	Screen * GuiBuild()
	{
		// Build the UI
		//Main Menu
		screen_main.add(screen_SD_list);
		screen_main.add(screen_unload_select);
		screen_main.add(screen_load_select);
		screen_main.add(screen_level_confirm);
		screen_main.add(screen_autohome);
		screen_main.add(screen_stepper);
		screen_main.add(screen_move);
		screen_main.add(screen_temperature);
		screen_main.add(screen_light);
		screen_main.add(screen_info);
		//SD Card List
		screen_SD_list.add(screen_main);
		screen_SD_list.add(screen_SD_confirm);
		screen_SD_list.icon(icon_nosd);
		screen_SD_list.icon(icon_sd);
		//SD Card Confirm
		screen_SD_confirm.add(screen_SD_back);
		screen_SD_confirm.add(screen_SD_OK);
		//SD Confirm back
		screen_SD_back.add(screen_SD_list);
		screen_SD_back.icon(icon_back);
		//SD Confirm OK
		screen_SD_OK.add(screen_print);
		screen_SD_OK.icon(icon_ok);
		//screen_print.icon(icon_ok);
		//Unload Filament Select
		screen_unload_select.add(screen_unload_heating);
		screen_unload_select.icon(icon_filament_unload);
		//Unload Filament Heating
		screen_unload_heating.add(screen_main);
		screen_unload_heating.add(screen_unload_pull);
		//Unload Filament Pull
		screen_unload_pull.add(screen_unload_confirm);
		//Unload Filament Confirm
		screen_unload_confirm.add(screen_unload_pull);
		screen_unload_confirm.add(screen_main);
		//Load Filament Select
		screen_load_select.add(screen_load_heating);
		screen_load_select.icon(icon_filament_load);
		//Load Filament Heating
		screen_load_heating.add(screen_main);
		screen_load_heating.add(screen_load_press);
		//Load Filament Pull
		screen_load_press.add(screen_load_confirm);
		//Load Filament Confirm
		screen_load_confirm.add(screen_load_press);
		screen_load_confirm.add(screen_main);
		//Level Plate
		screen_level_confirm.add(screen_level_cooling);
		screen_level_confirm.icon(icon_leveling);
		//Level Plate Cooling
		screen_level_cooling.add(screen_level_cooling);
		screen_level_cooling.add(screen_level1);
		//AutoHome
		screen_autohome.add(screen_main);
		screen_autohome.icon(icon_homing);
		//Stepper
		screen_stepper.add(screen_main);
		screen_stepper.icon(icon_steppers);
		screen_stepper.icon(icon_steppers_off);
		//Move Axis

		screen_move.add(screen_move_back2main);
		screen_move.add(screen_move_x);
		screen_move.add(screen_move_y);
		screen_move.add(screen_move_z);
		screen_move.add(screen_move_e);
		screen_move.icon(icon_moveaxis);

		screen_move_back2main.add(screen_main);
		screen_move_back2main.icon(icon_back);

		screen_move_back2move.add(screen_move);
		screen_move_back2move.icon(icon_back);

		screen_move_x.add(screen_move_back2move);
		screen_move_x.add(screen_move_10);
		screen_move_x.add(screen_move_1);
		screen_move_x.add(screen_move_01);
		screen_move_x.icon(icon_move_x);

		screen_move_y.add(screen_move_back2move);
		screen_move_y.add(screen_move_10);
		screen_move_y.add(screen_move_1);
		screen_move_y.add(screen_move_01);
		screen_move_y.icon(icon_move_y);

		screen_move_z.add(screen_move_back2move);
		screen_move_z.add(screen_move_10);
		screen_move_z.add(screen_move_1);
		screen_move_z.add(screen_move_01);
		screen_move_z.icon(icon_move_z);

		screen_move_e.add(screen_move_back2move);
		screen_move_e.add(screen_move_1);
		screen_move_e.add(screen_move_01);
		screen_move_e.icon(icon_move_e);

		screen_move_01.icon(icon_move_01mm);
		screen_move_1.icon(icon_move_1mm);
		screen_move_10.icon(icon_move_10mm);
		//screen_move_e.icon(icon_move_e);
		//Temperature
		screen_temperature.add(screen_main);
		screen_temperature.icon(icon_temperature);
		//Light
		screen_light.add(screen_main);
		screen_light.icon(icon_lightled_disable);
		screen_light.icon(icon_lightled);
		//Info
		screen_info.add(screen_main);
		screen_info.icon(icon_info);

		//Print Menu
//		screen_print.add(screen_play_pause);
		screen_print.add(screen_stop_confirm);
		screen_print.add(screen_change_confirm);
		screen_print.add(screen_speed);
		screen_print.add(screen_temperature);
		//Play/Pause
//		screen_play_pause.add(screen_main);
//		screen_play_pause.icon(icon_pause);
//		screen_play_pause.icon(icon_play); 
		//Stop Confirm
		screen_stop_confirm.add(screen_stop_back);
		screen_stop_confirm.add(screen_stop_OK);
		screen_stop_confirm.icon(icon_stop);
		//Stop Confirm back
		screen_stop_back.add(screen_print);
		screen_stop_back.icon(icon_back);
		//Stop Confirm OK
		screen_stop_OK.add(screen_main);
		screen_stop_OK.icon(icon_ok);
		//Change filament
		screen_change_confirm.add(screen_print);
		screen_change_confirm.add(screen_change_start);
		screen_change_confirm.icon(icon_change_filament);
		//Change filament start
		screen_change_start.add(screen_change_pullout);
		//Change filament pullout
		screen_change_pullout.add(screen_change_insert);
		//Change filament insert
		screen_change_insert.add(screen_change_retry);
		//Change filament retry
		screen_change_retry.add(screen_change_start);
		screen_change_retry.add(screen_print);
		//Change speed screens
		screen_speed.add(screen_print);
		screen_speed.icon(icon_change_speed);
		//

		return new ScreenMenu(screen_main);
	}
}