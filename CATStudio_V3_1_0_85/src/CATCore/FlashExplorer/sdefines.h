
#pragma once

#define WM_START_PROGRESS		(WM_USER+100)
#define WM_UPDATE_PROGRESS_BAR	(WM_USER+101)
#define WM_STOP_PROGRESS_BAR		(WM_USER+102)
#define WM_CANCEL_FILE			(WM_USER+103)

#define TIMERID_FORMAT			1
#define TIMERID_DELETE			2


#define GUI_INSTANCE_NAME	"GUI Instance"


#define FILE_STATE_READ			1
#define FILE_STATE_WRITE		2
#define FILE_STATE_DELETE		3
#define FILE_STATE_FORMAT		4
#define FILE_STATE_VERIFY		5
