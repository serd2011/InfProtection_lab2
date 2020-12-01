#pragma once

#ifdef __COMPILER_VISUAL_C__

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)

#endif

#include "wx/app.h"
#include "wx/string.h"
#include "wx/stattext.h"
#include "wx/filepicker.h"
#include "wx/sizer.h"
#include "wx/radiobox.h"
#include "wx/textctrl.h"
#include "wx/button.h"
#include "wx/menu.h"
#include "wx/statusbr.h"
#include "wx/frame.h"
#include "wx/filefn.h"
#include "wx/gauge.h"
#include "wx/msgdlg.h"
#include "wx/timer.h"
#include "wx/event.h"

#if defined(__WXMSW__) || defined(__WXOSX_COCOA__)
#define __APP_PROGRESS_AVAILABLE__
#include "wx/appprogress.h"
#endif

#ifdef __COMPILER_VISUAL_C__

#pragma warning(pop) 

#endif
