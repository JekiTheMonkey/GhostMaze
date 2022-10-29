#pragma once

DECLARE_LOG_CATEGORY_CLASS(LogGm, All, All);

#define EXEC_INFO_FORMAT "%s::%d: "
#define EXEC_INFO *FString(__FUNCTION__), __LINE__

#define _GM_LOG_IMPL(VERBOSITY, FORMAT, ...) \
	UE_LOG(LogGm, VERBOSITY, \
	TEXT(EXEC_INFO_FORMAT FORMAT), EXEC_INFO, __VA_ARGS__)

#define GM_FATAL(FORMAT, ...)		_GM_LOG_IMPL(Fatal,			FORMAT, __VA_ARGS__)
#define GM_ERROR(FORMAT, ...)		_GM_LOG_IMPL(Error,			FORMAT, __VA_ARGS__)
#define GM_WARN(FORMAT, ...)		_GM_LOG_IMPL(Warning,		FORMAT, __VA_ARGS__)
#define GM_DISPLAY(FORMAT, ...)		_GM_LOG_IMPL(Display,		FORMAT, __VA_ARGS__)
#define GM_LOG(FORMAT, ...)			_GM_LOG_IMPL(Log,			FORMAT, __VA_ARGS__)
#define GM_VERBOSE(FORMAT, ...)		_GM_LOG_IMPL(Verbose,		FORMAT, __VA_ARGS__)
#define GM_VVERBOSE(FORMAT, ...)	_GM_LOG_IMPL(VeryVerbose,	FORMAT, __VA_ARGS__)

#define S_EXEC_INFO_FORMAT "%s::%d %s: "
#define S_EXEC_INFO *FString(__FUNCTION__), __LINE__, *GetNameSafe(this)

#define _GMS_LOG_IMPL(VERBOSITY, FORMAT, ...) \
	UE_LOG(LogGm, VERBOSITY, \
	TEXT(S_EXEC_INFO_FORMAT FORMAT), S_EXEC_INFO, __VA_ARGS__)

#define GMS_FATAL(FORMAT, ...) \
	do { _GMS_LOG_IMPL(Fatal,			FORMAT, __VA_ARGS__); } while(0)
#define GMS_ERROR(FORMAT, ...) \
	do { _GMS_LOG_IMPL(Error,			FORMAT, __VA_ARGS__); } while(0)
#define GMS_WARN(FORMAT, ...) \
	do { _GMS_LOG_IMPL(Warning,			FORMAT, __VA_ARGS__); } while(0)
#define GMS_DISPLAY(FORMAT, ...) \
	do { _GMS_LOG_IMPL(Display,			FORMAT, __VA_ARGS__); } while(0)
#define GMS_LOG(FORMAT, ...) \
	do { _GMS_LOG_IMPL(Log,				FORMAT, __VA_ARGS__); } while(0)
#define GMS_VERBOSE(FORMAT, ...) \
	do { _GMS_LOG_IMPL(Verbose,			FORMAT, __VA_ARGS__); } while(0)
#define GMS_VVERBOSE(FORMAT, ...) \
	do { _GMS_LOG_IMPL(VeryVerbose,		FORMAT, __VA_ARGS__); } while(0)
