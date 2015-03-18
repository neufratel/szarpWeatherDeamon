

// Parameters used by the cache file
#define WS_CACHE_READ	0
#define WS_CACHE_WRITE	1

// Weather Station buffer parameters
#define WS_BUFFER_SIZE		0x10000	// Size of total buffer
#define WS_BUFFER_START		0x100	// First address of up to 4080 buffer records
#define WS_BUFFER_END		0xFFF0	// Start of last buffer record
#define WS_BUFFER_RECORD	0x10	// Size of one buffer record
#define WS_BUFFER_CHUNK		0x20	// Size of chunk received over USB
#define WS_FIXED_BLOCK_START	0x0000	// First address of fixed block
#define WS_FIXED_BLOCK_SIZE	0x0100	// Size of fixed block

// Weather Station buffer memory positions
#define WS_DELAY		 0	// Position of delay parameter
#define WS_HUMIDITY_IN		 1	// Position of inside humidity parameter
#define WS_TEMPERATURE_IN	 2	// Position of inside temperature parameter
#define WS_HUMIDITY_OUT		 4	// Position of outside humidity parameter
#define WS_TEMPERATURE_OUT	 5	// Position of outside temperature parameter
#define WS_ABS_PRESSURE		 7	// Position of absolute pressure parameter
#define WS_WIND_AVE		 9	// Position of wind direction parameter
#define WS_WIND_GUST		10	// Position of wind direction parameter
#define WS_WIND_DIR		12	// Position of wind direction parameter
#define WS_RAIN			13	// Position of rain parameter
#define WS_STATUS		15	// Position of status parameter
#define WS_DATA_COUNT		27	// Position of data_count parameter
#define WS_CURRENT_POS		30	// Position of current_pos parameter
#define WS_CURR_REL_PRESSURE	32	// Position of current relative pressure parameter
#define WS_CURR_ABS_PRESSURE	34	// Position of current absolute pressure parameter

// Calculated rain parameters
// NOTE: These positions are NOT stored in the Weather Station
#define WS_RAIN_HOUR		0x08	// Position of hourly calculated rain
#define WS_RAIN_DAY		0x0A	// Position of daily calculated rain
#define WS_RAIN_WEEK		0x0C	// Position of weekly calculated rain
#define WS_RAIN_MONTH		0x0E	// Position of monthly calculated rain


// The following setting parameters are for reference only
// A future user interface could interpret these parameters
// Unit settings
#define WS_UNIT_SETTING_IN_T_C_F	0x01
#define WS_UNIT_SETTING_OUT_T_C_F	0x02
#define WS_UNIT_SETTING_RAIN_FALL_CM_IN	0x04
#define WS_UNIT_SETTING_PRESSURE_HPA	0x20
#define WS_UNIT_SETTING_PRESSURE_INHG	0x40
#define WS_UNIT_SETTING_PRESSURE_MMHG	0x80
// Unit wind speed settings
#define WS_UNIT_SETTING_WIND_SPEED_MS	0x01
#define WS_UNIT_SETTING_WIND_SPEED_KMH	0x02
#define WS_UNIT_SETTING_WIND_SPEED_KNOT	0x04
#define WS_UNIT_SETTING_WIND_SPEED_MH	0x08
#define WS_UNIT_SETTING_WIND_SPEED_BFT	0x10
// Display format 0
#define WS_DISPLAY_FORMAT_P_ABS_REL	0x01
#define WS_DISPLAY_FORMAT_WSP_AVG_GUST	0x02
#define WS_DISPLAY_FORMAT_H_24_12	0x04
#define WS_DISPLAY_FORMAT_DDMMYY_MMDDYY	0x08
#define WS_DISPLAY_FORMAT_TS_H_12_24	0x10
#define WS_DISPLAY_FORMAT_DATE_COMPLETE	0x20
#define WS_DISPLAY_FORMAT_DATE_AND_WK	0x40
#define WS_DISPLAY_FORMAT_ALARM_TIME	0x80
// Display format 1
#define WS_DISPLAY_FORMAT_OUT_T		0x01
#define WS_DISPLAY_FORMAT_OUT_WINDCHILL	0x02
#define WS_DISPLAY_FORMAT_OUT_DEW_POINT	0x04
#define WS_DISPLAY_FORMAT_RAIN_FALL_1H	0x08
#define WS_DISPLAY_FORMAT_RAIN_FALL_24H	0x10
#define WS_DISPLAY_FORMAT_RAIN_FALL_WK	0x20
#define WS_DISPLAY_FORMAT_RAIN_FALL_MO	0x40
#define WS_DISPLAY_FORMAT_RAIN_FALL_TOT	0x80
// Alarm enable 0
#define WS_ALARM_ENABLE_TIME		0x02
#define WS_ALARM_ENABLE_WIND_DIR	0x04
#define WS_ALARM_ENABLE_IN_RH_LO	0x10
#define WS_ALARM_ENABLE_IN_RH_HI	0x20
#define WS_ALARM_ENABLE_OUT_RH_LO	0x40
#define WS_ALARM_ENABLE_OUT_RH_HI	0x80
// Alarm enable 1
#define WS_ALARM_ENABLE_WSP_AVG		0x01
#define WS_ALARM_ENABLE_WSP_GUST	0x02
#define WS_ALARM_ENABLE_RAIN_FALL_1H	0x04
#define WS_ALARM_ENABLE_RAIN_FALL_24H	0x08
#define WS_ALARM_ENABLE_ABS_P_LO	0x10
#define WS_ALARM_ENABLE_ABS_P_HI	0x20
#define WS_ALARM_ENABLE_REL_P_LO	0x40
#define WS_ALARM_ENABLE_REL_P_HI	0x80
// Alarm enable 2
#define WS_ALARM_ENABLE_IN_T_LO		0x01
#define WS_ALARM_ENABLE_IN_T_HI		0x02
#define WS_ALARM_ENABLE_OUT_T_LO	0x04
#define WS_ALARM_ENABLE_OUT_T_HI	0x08
#define WS_ALARM_ENABLE_WINDCHILL_LO	0x10
#define WS_ALARM_ENABLE_WINDCHILL_HI	0x20
#define WS_ALARM_ENABLE_DEWPOINT_LO	0x40
#define WS_ALARM_ENABLE_DEWPOINT_HI	0x80


// Conversion parameters for english units
// Second and optional third factor is for adapting to actual stored values
#define WS_SCALE_DEFAULT	 1.0	// No scaling
#define WS_SCALE_MS_TO_MPH	 (2.2369362920544   * 0.1)
#define WS_SCALE_C_TO_F		 (1.8               * 0.1)
#define WS_SCALE_CM_TO_IN	 (0.3937007874      * 0.1 * 0.3)
#define WS_SCALE_RAW_TO_inHg	 (0.029530058646697 * 0.1)
#define WS_SCALE_hPa_TO_inHg	 (0.029530058646697)
#define WS_SCALE_OFFS_TO_DEGREE	22.5

#define WS_OFFSET_DEFAULT	 0.0	// No offset
#define WS_OFFSET_C_TO_F	32.0


// Table for decoding raw weather station data.
// Each key specifies a (pos, type, scale) tuple that is understood by CWS_decode().
// See http://www.jim-easterbrook.me.uk/weather/mm/ for description of data

enum ws_types {ub,sb,us,ss,dt,tt,pb,wa,wg,dp};

struct ws_record {
	char name[22];
	int pos;
	enum ws_types ws_type;
	float scale;
} ws_format[] = {
// Up to 4080 records with this format
	{"delay"	,  0, ub,  1.0}, // Minutes since last stored reading (1:240)
	{"hum_in"       ,  1, ub,  1.0}, // Indoor relative humidity %        (1:99)    , 0xFF means invalid
	{"temp_in"      ,  2, ss,  0.1}, // Multiply by 0.1 to get °C         (-40:+60) , 0xFFFF means invalid
	{"hum_out"      ,  4, ub,  1.0}, // Outdoor relative humidity %       (1:99)    , 0xFF means invalid
	{"temp_out"     ,  5, ss,  0.1}, // Multiply by 0.1 to get °C         (-40:+60) , 0xFFFF means invalid
	{"abs_pressure" ,  7, us,  0.1}, // Multiply by 0.1 to get hPa        (920:1080), 0xFFFF means invalid
	{"wind_ave"     ,  9, wa,  0.1}, // Multiply by 0.1 to get m/s        (0:50)    , 0xFF means invalid
	{"wind_gust"    , 10, wg,  0.1}, // Multiply by 0.1 to get m/s        (0:50)    , 0xFF means invalid
	// 11, wind speed, high bits     // Lower 4 bits are the average wind speed high bits, upper 4 bits are the gust wind speed high bits
	{"wind_dir"     , 12, ub, 22.5}, // Multiply by 22.5 to get ° from north (0-15), 7th bit indicates invalid data
	{"rain"         , 13, us,  0.3}, // Multiply by 0.3 to get mm
	{"status"       , 15, pb,  1.0}, // 6th bit indicates loss of contact with sensors, 7th bit indicates rainfall overflow
// The lower fixed block
	{"read_period"      , 16, ub, 1.0}, // Minutes between each stored reading (1:240)
	{"units0"           , 17, ub, 1.0}, // Unit setting flags       (Bits 0,1,2,    5,6,7)
	{"units_wind_speed" , 18, ub, 1.0}, // Unit wind speed settings (Bits 0,1,2,3,4      )
	{"display_format0"  , 19, ub, 1.0}, // Unit display settings    (Bits 0,1,2,3,4,5,6,7)
	{"display_format1"  , 20, ub, 1.0}, // Unit display settings    (Bits 0,1,2,3,4,5,6,7)
	{"alarm_enable0"    , 21, ub, 1.0}, // Unit alarm settings      (Bits   1,2,  4,5,6,7)
	{"alarm_enable1"    , 22, ub, 1.0}, // Unit alarm settings      (Bits 0,1,2,3,4,5,6,7)
	{"alarm_enable2"    , 23, ub, 1.0}, // Unit alarm settings      (Bits 0,1,2,3,4,5,6,7)
	{"timezone"         , 24, sb, 1.0}, // Hours offset from Central European Time, so in the UK this should be set to -1. In stations without a radio controlled clock this is always zero. 7th bit is sign bit
	{"data_refreshed"   , 26, us, 1.0}, // PC write AA indicating setting changed, base unit clear this byte for reading back the change
	{"data_count"       , 27, us, 1.0}, // Number of stored readings. Starts at zero, rises to 4080
	{"current_pos"      , 30, us, 1.0}, // Address of the stored reading currently being created. Starts at 256, rises to 65520 in steps of 16, then loops back to 256. The data at this address is updated every 48 seconds or so, until the read period is reached. Then the address is incremented and the next record becomes current.
	{"rel_pressure"     , 32, us, 0.1}, // Current relative atmospheric pressure, multiply by 0.1 to get hPa
	{"abs_pressure"     , 34, us, 0.1}, // Current absolute atmospheric pressure, multiply by 0.1 to get hPa
	{"date_time"        , 43, dt, 1.0}, // Current date & time
// Alarm settings
	{"alarm.hum_in.hi"       , 48, ub,  1.0}, {"alarm.hum_in.lo"       , 49, ub, 1.0}, // Indoor relative humidity %
	{"alarm.temp_in.hi"      , 50, ss,  0.1}, {"alarm.temp_in.lo"      , 52, ss, 0.1}, // Multiply by 0.1 to get °C
	{"alarm.hum_out.hi"      , 54, ub,  1.0}, {"alarm.hum_out.lo"      , 55, ub, 1.0}, // Indoor relative humidity %
	{"alarm.temp_out.hi"     , 56, ss,  0.1}, {"alarm.temp_out.lo"     , 58, ss, 0.1}, // Multiply by 0.1 to get °C
	{"alarm.windchill.hi"    , 60, ss,  0.1}, {"alarm.windchill.lo"    , 62, ss, 0.1}, // Multiply by 0.1 to get °C
	{"alarm.dewpoint.hi"     , 64, ss,  0.1}, {"alarm.dewpoint.lo"     , 66, ss, 0.1}, // Multiply by 0.1 to get °C
	{"alarm.abs_pressure.hi" , 68, ss,  0.1}, {"alarm.abs_pressure.lo" , 70, ss, 0.1}, // Multiply by 0.1 to get hPa
	{"alarm.rel_pressure.hi" , 72, ss,  0.1}, {"alarm.rel_pressure.lo" , 74, ss, 0.1}, // Multiply by 0.1 to get hPa
	{"alarm.wind_ave.bft"    , 76, ub,  1.0}, {"alarm.wind_ave.ms"     , 77, ub, 0.1}, // Multiply by 0.1 to get m/s
	{"alarm.wind_gust.bft"   , 79, ub,  1.0}, {"alarm.wind_gust.ms"    , 80, ub, 0.1}, // Multiply by 0.1 to get m/s
	{"alarm.wind_dir"        , 82, ub, 22.5},                                          // Multiply by 22.5 to get ° from north
	{"alarm.rain.hour"       , 83, us,  0.3}, {"alarm.rain.day"        , 85, us, 0.3}, // Multiply by 0.3 to get mm
	{"alarm.time"            , 87, tt,  1.0},
// Maximums with timestamps
	{"max.hum_in.val"       ,  98, ub, 1.0}, {"max.hum_in.date"       , 141, dt, 1.0},
	{"max.hum_out.val"      , 100, ub, 1.0}, {"max.hum_out.date"      , 151, dt, 1.0},
	{"max.temp_in.val"      , 102, ss, 0.1}, {"max.temp_in.date"      , 161, dt, 1.0}, // Multiply by 0.1 to get °C
	{"max.temp_out.val"     , 106, ss, 0.1}, {"max.temp_out.date"     , 171, dt, 1.0}, // Multiply by 0.1 to get °C
	{"max.windchill.val"    , 110, ss, 0.1}, {"max.windchill.date"    , 181, dt, 1.0}, // Multiply by 0.1 to get °C
	{"max.dewpoint.val"     , 114, ss, 0.1}, {"max.dewpoint.date"     , 191, dt, 1.0}, // Multiply by 0.1 to get °C
	{"max.abs_pressure.val" , 118, us, 0.1}, {"max.abs_pressure.date" , 201, dt, 1.0}, // Multiply by 0.1 to get hPa
	{"max.rel_pressure.val" , 122, us, 0.1}, {"max.rel_pressure.date" , 211, dt, 1.0}, // Multiply by 0.1 to get hPa
	{"max.wind_ave.val"     , 126, us, 0.1}, {"max.wind_ave.date"     , 221, dt, 1.0}, // Multiply by 0.1 to get m/s
	{"max.wind_gust.val"    , 128, us, 0.1}, {"max.wind_gust.date"    , 226, dt, 1.0}, // Multiply by 0.1 to get m/s
	{"max.rain.hour.val"    , 130, us, 0.3}, {"max.rain.hour.date"    , 231, dt, 1.0}, // Multiply by 0.3 to get mm
	{"max.rain.day.val"     , 132, us, 0.3}, {"max.rain.day.date"     , 236, dt, 1.0}, // Multiply by 0.3 to get mm
	{"max.rain.week.val"    , 134, us, 0.3}, {"max.rain.week.date"    , 241, dt, 1.0}, // Multiply by 0.3 to get mm
	{"max.rain.month.val"   , 136, us, 0.3}, {"max.rain.month.date"   , 246, dt, 1.0}, // Multiply by 0.3 to get mm
	{"max.rain.total.val"   , 138, us, 0.3}, {"max.rain.total.date"   , 251, dt, 1.0}, // Multiply by 0.3 to get mm
// Minimums with timestamps
	{"min.hum_in.val"       ,  99, ub, 1.0}, {"min.hum_in.date"       , 146, dt, 1.0},
	{"min.hum_out.val"      , 101, ub, 1.0}, {"min.hum_out.date"      , 156, dt, 1.0},
	{"min.temp_in.val"      , 104, ss, 0.1}, {"min.temp_in.date"      , 166, dt, 1.0}, // Multiply by 0.1 to get °C
	{"min.temp_out.val"     , 108, ss, 0.1}, {"min.temp_out.date"     , 176, dt, 1.0}, // Multiply by 0.1 to get °C
	{"min.windchill.val"    , 112, ss, 0.1}, {"min.windchill.date"    , 186, dt, 1.0}, // Multiply by 0.1 to get °C
	{"min.dewpoint.val"     , 116, ss, 0.1}, {"min.dewpoint.date"     , 196, dt, 1.0}, // Multiply by 0.1 to get °C
	{"min.abs_pressure.val" , 120, us, 0.1}, {"min.abs_pressure.date" , 206, dt, 1.0}, // Multiply by 0.1 to get hPa
	{"min.rel_pressure.val" , 124, us, 0.1}, {"min.rel_pressure.date" , 216, dt, 1.0}, // Multiply by 0.1 to get hPa
// Calculated rainfall, must be calculated prior to every record
	{"rain.hour"  , WS_RAIN_HOUR , us, 0.3}, // Multiply by 0.3 to get mm
	{"rain.day"   , WS_RAIN_DAY  , us, 0.3}, // Multiply by 0.3 to get mm
	{"rain.week"  , WS_RAIN_WEEK , us, 0.3}, // Multiply by 0.3 to get mm
	{"rain.month" , WS_RAIN_MONTH, us, 0.3}  // Multiply by 0.3 to get mm
};

#define	WS_LOWER_FIXED_BLOCK_START	11
#define	WS_LOWER_FIXED_BLOCK_END	96
#define WS_RECORDS			11

struct ws_record pywws_format[] = {
// Up to 4080 records with this format
	{"delay"	,  0, ub,  1.0}, // Minutes since last stored reading (1:240)
	{"hum_in"       ,  1, ub,  1.0}, // Indoor relative humidity %        (1:99)    , 0xFF means invalid
	{"temp_in"      ,  2, ss,  0.1}, // Multiply by 0.1 to get °C         (-40:+60) , 0xFFFF means invalid
	{"hum_out"      ,  4, ub,  1.0}, // Outdoor relative humidity %       (1:99)    , 0xFF means invalid
	{"temp_out"     ,  5, ss,  0.1}, // Multiply by 0.1 to get °C         (-40:+60) , 0xFFFF means invalid
	{"abs_pressure" ,  7, us,  0.1}, // Multiply by 0.1 to get hPa        (920:1080), 0xFFFF means invalid
	{"wind_ave"     ,  9, wa,  0.1}, // Multiply by 0.1 to get m/s        (0:50)    , 0xFF means invalid
	{"wind_gust"    , 10, wg,  0.1}, // Multiply by 0.1 to get m/s        (0:50)    , 0xFF means invalid
	// 11, wind speed, high bits     // Lower 4 bits are the average wind speed high bits, upper 4 bits are the gust wind speed high bits
	{"wind_dir"     , 12, ub, 22.5}, // Multiply by 22.5 to get ° from north (0-15), 7th bit indicates invalid data
	{"rain"         , 13, us,  0.3}, // Multiply by 0.3 to get mm
	{"status"       , 15, pb,  1.0}  // 6th bit indicates loss of contact with sensors, 7th bit indicates rainfall overflow
};

#define WS_PYWWS_RECORDS	11

struct ws_record2 {
	char          name[22];
	int           pos;
	enum ws_types ws_type;
	float         scale;
	float         offset;
} wug_format[] = {
	// (name, pos, type, scale, offset)
	// action [action=updateraw]
	// ID [ID as registered by wunderground.com]
	// PASSWORD [PASSWORD registered with this ID]
	// dateutc - [YYYY-MM-DD HH:MM:SS (mysql format)]
	{"winddir"      , WS_WIND_DIR        , ub , WS_SCALE_OFFS_TO_DEGREE , WS_OFFSET_DEFAULT},	// - [0-360]
	{"windspeedmph" , WS_WIND_AVE        , wa , WS_SCALE_MS_TO_MPH      , WS_OFFSET_DEFAULT},	// - [mph]
	{"windgustmph"  , WS_WIND_GUST       , wg , WS_SCALE_MS_TO_MPH      , WS_OFFSET_DEFAULT},	// - [windgustmph]
	{"humidity"     , WS_HUMIDITY_OUT    , ub , WS_SCALE_DEFAULT        , WS_OFFSET_DEFAULT},	// - [%]
	{"tempf"        , WS_TEMPERATURE_OUT , ss , WS_SCALE_C_TO_F         , WS_OFFSET_C_TO_F},	// - [temperature F]
	{"rainin"       , WS_RAIN_HOUR       , us , WS_SCALE_CM_TO_IN       , WS_OFFSET_DEFAULT},	// - [hourly rain in]
	{"dailyrainin"  , WS_RAIN_DAY        , us , WS_SCALE_CM_TO_IN       , WS_OFFSET_DEFAULT},	// - [daily rain in accumulated]
	{"baromin"      , WS_ABS_PRESSURE    , us , WS_SCALE_RAW_TO_inHg    , WS_OFFSET_DEFAULT},	// - [barom in]
	{"dewptf"       , 0                  , dp , WS_SCALE_C_TO_F         , WS_OFFSET_C_TO_F}		// - [dewpoint F]
	// weather - [text] -- metar style (+RA)
	// clouds - [text] -- SKC, FEW, SCT, BKN, OVC
	// softwaretype - [text] ie: vws or weatherdisplay
};

#define	WS_WUG_HOURLY_RAIN	5	// Position of hourly rain parameter
#define	WS_WUG_DAILY_RAIN	6	// Position of daily rain parameter
#define	WS_WUG_PRESSURE		7	// Position of pressure parameter
#define WS_WUG_RECORDS		9



struct ws_record2 pws_format[] = {
	// (name, pos, type, scale, offset)
	// ID [STATIONID as registered by pwsweather.com]
	// PASSWORD [PASSWORD registered with this ID]
	// dateutc - [YYYY-MM-DD+HH%3AMM%3ASS]
	{"winddir"      , WS_WIND_DIR        , ub , WS_SCALE_OFFS_TO_DEGREE , WS_OFFSET_DEFAULT},	// - [0-360]
	{"windspeedmph" , WS_WIND_AVE        , wa , WS_SCALE_MS_TO_MPH      , WS_OFFSET_DEFAULT},	// - [mph]
	{"windgustmph"  , WS_WIND_GUST       , wg , WS_SCALE_MS_TO_MPH      , WS_OFFSET_DEFAULT},	// - [windgustmph]
	{"tempf"        , WS_TEMPERATURE_OUT , ss , WS_SCALE_C_TO_F         , WS_OFFSET_C_TO_F},	// - [temperature F]
	{"rainin"       , WS_RAIN_HOUR       , us , WS_SCALE_CM_TO_IN       , WS_OFFSET_DEFAULT},	// - [hourly rain in]
	{"dailyrainin"  , WS_RAIN_DAY        , us , WS_SCALE_CM_TO_IN       , WS_OFFSET_DEFAULT},	// - [daily rain in accumulated]
	// monthrainin - [monthly rain in accumulated]
	// yearrainin - [yearly rain in accumulated]
	{"baromin"      , WS_ABS_PRESSURE    , us , WS_SCALE_RAW_TO_inHg    , WS_OFFSET_DEFAULT},	// - [barom in]
	{"dewptf"       , 0                  , dp , WS_SCALE_C_TO_F         , WS_OFFSET_C_TO_F},	// - [dewpoint F]
	{"humidity"     , WS_HUMIDITY_OUT    , ub , WS_SCALE_DEFAULT        , WS_OFFSET_DEFAULT}	// - [%]
	// weather - [text] -- metar style (+RA)
	// solarradiation
	// UV
	// softwaretype - [text] ie: vws or weatherdisplay
	// action [action=updateraw]
};

#define	WS_PWS_HOURLY_RAIN	4	// Position of hourly rain parameter
#define	WS_PWS_DAILY_RAIN	5	// Position of daily rain parameter
#define	WS_PWS_PRESSURE		6	// Position of pressure parameter
#define WS_PWS_RECORDS		9


struct ws_record2 ws3600_format[] = {
// Up to 4080 records with this format
//	{"delay"	,  0, ub,  1.0, 0}, // Minutes since last stored reading (1:240)
	{"RHi"		,  1, ub,  1.0, 0}, // Indoor relative humidity %        (1:99)    , 0xFF means invalid
	{"Ti"		,  2, ss,  0.1, 0}, // Multiply by 0.1 to get °C         (-40:+60) , 0xFFFF means invalid
	{"RHo"		,  4, ub,  1.0, 0}, // Outdoor relative humidity %       (1:99)    , 0xFF means invalid
	{"To"		,  5, ss,  0.1, 0}, // Multiply by 0.1 to get °C         (-40:+60) , 0xFFFF means invalid
	{"RP"		,  7, us,  0.1, 0}, // Multiply by 0.1 to get hPa        (920:1080), 0xFFFF means invalid
	{"WS"		,  9, wa,  0.1, 0}, // Multiply by 0.1 to get m/s        (0:50)    , 0xFF means invalid
	{"WG"		, 10, wg,  0.1, 0}, // Multiply by 0.1 to get m/s        (0:50)    , 0xFF means invalid
	// 11, wind speed, high bits     // Lower 4 bits are the average wind speed high bits, upper 4 bits are the gust wind speed high bits
	{"DIR"		, 12, ub, 22.5, 0}, // Multiply by 22.5 to get ° from north (0-15), 7th bit indicates invalid data
	{"Rtot"         , 13, us,  0.35,0},// Multiply by 0.3 to get mm
	{"state"	, 15, pb,  1.0, 0}, // 6th bit indicates loss of contact with sensors, 7th bit indicates rainfall overflow
// The lower fixed block
//	{"Timin"	,104, ss,  0.1, 0},
//	{"DTimin"       ,166, dt,  1.0, 0}, // Multiply by 0.1 to get °C
// End mark
	{ "" }
};

#define WS_W3600_PRESSURE 4
typedef long int time_t;





#include <usb.h>


class USBConnector{
	private:
		struct usb_dev_handle *devh;
		struct usb_device *dev;
		int vLevel;
		char vDst;
	public:
		USBConnector();
		struct usb_device* findUSBDevice(int vendor, int product);
		int open(int vendor, int product);
		int close();
		short read_block(unsigned short ptr, char* buffer);
	
};

class WeatherStation{
	private:
	
		USBConnector usb;
		
		unsigned short old_pos;
		char LogPath[255];
		unsigned char m_buf[WS_BUFFER_SIZE];
		float pressOffs_hPa;
		time_t m_previous_timestamp;
		time_t m_timestamp;
				

		unsigned short inc_ptr(unsigned short ptr);
		unsigned short dec_ptr(unsigned short ptr);
		int getData(float* buffer); //fill tab[10] with station data;
		int read();
		int open();
		int close(int new_data_flag);
		void cache(char isStoring);
		short dataHasChanged(unsigned char OldBuf[], unsigned char NewBuf[], size_t size);
		short read_fixed_block();
		int calculate_rain_period(unsigned short pos, unsigned short begin, unsigned short end);
		int calculate_rain(unsigned short current_pos, unsigned short data_count);
		float dew_point(char* raw, float scale, float offset);
		unsigned bcd_decode(unsigned char byte);
		unsigned short unsigned_short(unsigned char* raw);
		signed short signed_short(unsigned char* raw);
		int decode(unsigned char* raw, enum ws_types ws_type, float scale, float offset, char* result);
	public:
		int readStation(int tab[], int params_count);
		WeatherStation(){usb = USBConnector();
				 usb.open(0x1941, 0x8021);};
		
};

/*********************************************************
**********************************************************
**********************************************************
**********************************************************
**********************************************************
**********************************************************
**********************************************************
**********************************************************
**********************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <time.h>


#define WORKPATH "//var//log//szarp//"

void  MsgPrintf(int Level, const char *fmt, ...)
{
	char    Buf[200];
	va_list argptr;
	FILE	*f;

	
	va_start(argptr, fmt);
	vsprintf(Buf, fmt, argptr);
	va_end(argptr);
	
		printf("%s", Buf);
	
	
}
/*---------------------------------USBConnector--------------------------------*/	
/*---------------------------------------------------------------------------*/	
USBConnector::USBConnector(){
		devh =NULL;
		dev =NULL;
		vLevel=0;
		vDst=0;

;};
/*---------------------------------------------------------------------------*/
struct usb_device* USBConnector::findUSBDevice(int vendor, int product){
	struct usb_bus *bus;
	for (bus = usb_get_busses(); bus; bus = bus->next) {
		struct usb_device *dev;
	
		for (dev = bus->devices; dev; dev = dev->next) {
		    	if (dev->descriptor.idVendor == vendor
			&& dev->descriptor.idProduct == product)
				return dev;
		}
	}
    return NULL;		
}
/*---------------------------------------------------------------------------*/
int USBConnector::open(int vendor, int product){ /* returns 0 if OK, <0 if error */
	int ret;
	char buf[1000];

	usb_init();
	if(this->vDst!='f')
		usb_set_debug(this->vLevel+1);
	usb_find_busses();
	usb_find_devices();

	dev = this->findUSBDevice(vendor, product);
	if(dev==NULL) {
		MsgPrintf(0, "WeatherStation not found on USB (vendor,product)=(%04X,%04X)\n", vendor, product);
		printf( "WeatherStation not found on USB (vendor,product)=(%04X,%04X)\n", vendor, product);
		return -1;
	}
	devh = usb_open(dev);
	if(!devh) {
		MsgPrintf(0, "Open USB device failed (vendor,product)=(%04X,%04X)\n", vendor, product);
		printf( "Open USB device failed (vendor,product)=(%04X,%04X)\n", vendor, product);
		return -2;
	}
	//signal(SIGTERM, close); //CUZ... 
#ifdef LIBUSB_HAS_GET_DRIVER_NP
	ret = usb_get_driver_np(devh, 0, buf, sizeof(buf));
	MsgPrintf(3, "usb_get_driver_np returned %d\n", ret);
	if (ret == 0) {
		MsgPrintf(1, "interface 0 already claimed by driver \\'%s\\', attempting to detach it\n", buf);
#ifdef LIBUSB_HAS_DETACH_KERNEL_DRIVER_NP
		ret = usb_detach_kernel_driver_np(devh, 0);
		MsgPrintf(ret?0:1, "usb_detach_kernel_driver_np returned %d\n", ret);
#endif
	}
#endif
	ret = usb_claim_interface(devh, 0);
	if(ret<0) {
		MsgPrintf(0, "claim failed with error %d\n", ret);
		return 0;	// error, but device is already open and needs to be closed
	}

	ret = usb_set_altinterface(devh, 0);
	if(ret<0) {
		MsgPrintf(0, "set_altinterface failed with error %d\n", ret);
		return 0;	// error, but device is already open and needs to be closed
	}
	ret = usb_get_descriptor(devh, 1, 0, buf, 0x12);
	ret = usb_get_descriptor(devh, 2, 0, buf, 0x09);
	ret = usb_get_descriptor(devh, 2, 0, buf, 0x22);
	ret = usb_release_interface(devh, 0);
	if(ret) MsgPrintf(0, "failed to release interface before set_configuration: %d\n", ret);
	ret = usb_set_configuration(devh, 1);
	ret = usb_claim_interface(devh, 0);
	if(ret) MsgPrintf(0, "claim after set_configuration failed with error %d\n", ret);
	ret = usb_set_altinterface(devh, 0);
	ret = usb_control_msg(devh, USB_TYPE_CLASS + USB_RECIP_INTERFACE, 0xa, 0, 0, buf, 0, 1000);
	ret = usb_get_descriptor(devh, 0x22, 0, buf, 0x74);

	return 0;
}
/*---------------------------------------------------------------------------*/		



int USBConnector::close(){
	int ret = usb_release_interface(devh, 0);
	if(ret) MsgPrintf(0, "failed to release interface: %d\n", ret);
	ret = usb_close(devh);
	if(ret) MsgPrintf(0, "failed to close interface: %d\n", ret);
}
/*---------------------------------------------------------------------------*/
short USBConnector::read_block(unsigned short ptr, char* buffer)
{
/*
Read 32 bytes data command	

After sending the read command, the device will send back 32 bytes data wihtin 100ms. 
If not, then it means the command has not been received correctly.
*/
	char buf_1 = (char)(ptr / 256);
	char buf_2 = (char)(ptr & 0xFF);
	char tbuf[8];
	tbuf[0] = 0xA1;		// READ COMMAND
	tbuf[1] = buf_1;	// READ ADDRESS HIGH
	tbuf[2] = buf_2;	// READ ADDRESS LOW
	tbuf[3] = 0x20;		// END MARK
	tbuf[4] = 0xA1;		// READ COMMAND
	tbuf[5] = 0;		// READ ADDRESS HIGH
	tbuf[6] = 0;		// READ ADDRESS LOW
	tbuf[7] = 0x20;		// END MARK
	
	// Prepare read of 32-byte chunk from position ptr
	int ret = usb_control_msg(devh, USB_TYPE_CLASS + USB_RECIP_INTERFACE, 9, 0x200, 0, tbuf, 8, 1000);
	if(ret<0){
		 MsgPrintf(0, "usb_control_msg failed (%d) whithin USBConnector_read_block(%04X,...)\n", ret, ptr);
		
	}else {
		// Read 32-byte chunk and place in buffer buf
		ret = usb_interrupt_read(devh, 0x81, buffer, 0x20, 1000);
		if(ret<0) MsgPrintf(0, "usb_interrupt_read failed (%d) whithin USBConnector_read_block(%04X,...)\n", ret, ptr);
		
	}
	return ret;
}

/*----------------------------WeatherStation---------------------------------*/
/*---------------------------------------------------------------------------*/

unsigned short WeatherStation::inc_ptr(unsigned short ptr)
{
	// Step forward through buffer.
	ptr += WS_BUFFER_RECORD;             
	if((ptr > WS_BUFFER_END)||(ptr < WS_BUFFER_START))
		// End is reached, step to start of buffer.
		ptr = WS_BUFFER_START;
	return ptr;
}
/*---------------------------------------------------------------------------*/
unsigned short WeatherStation::dec_ptr(unsigned short ptr)
{
	// Step backwards through buffer.
	ptr -= WS_BUFFER_RECORD;             
	if (ptr < WS_BUFFER_START)
		// Start is reached, step to end of buffer.
		ptr = WS_BUFFER_END;
	return ptr;
}
/*---------------------------------------------------------------------------*/
int WeatherStation::getData( float* buffer)
{
// - Get current_pos
// - Get data_count
// Read data_count records forward from old_pos to current_pos. 
// Calculate timestamp and break if already written
// Step 0x10 in the range 0x10000 to 0x100

	

	time_t 		timestamp   = m_timestamp - m_timestamp%60;	// Set to current minute

	unsigned short	data_count  = unsigned_short(&m_buf[WS_DATA_COUNT]);
	unsigned short	current_pos = unsigned_short(&m_buf[WS_CURRENT_POS]);
	unsigned short	end_pos	    = current_pos, i;
	char		s1[1000]    = "", s2[1000] = "";
	int		n, j;

	unsigned short	dat2_count  = data_count;	//end point for rain calculation

	
	if((old_pos==0)||(old_pos==0xFFFF))	//cachefile empty or empty eeprom was read
		old_pos = current_pos;
	
	

	// Body
	while(current_pos!=old_pos) {		// get record & time to start output from
		timestamp  -= m_buf[current_pos+WS_DELAY]*60;	// Update timestamp
		current_pos = dec_ptr(current_pos);
		--dat2_count;
	}
	
	
	for(i=0; i<data_count; i++)
	{
		
			calculate_rain(current_pos, dat2_count+i);

		
				n=strftime(s1,100,"%Y-%m-%d %H:%M:%S", gmtime(&timestamp));
				for (j=0;j<WS_PYWWS_RECORDS;j++) {
					decode(&m_buf[current_pos+pywws_format[j].pos],
							pywws_format[j].ws_type,
							pywws_format[j].scale,
							0.0,
							s2);
					if(j<10) buffer[j]=atof(s2); //get data without timestams
				};

	

		strcat(s1,"\n");
		//fputs(s1,f);

		if(current_pos==end_pos)
			break;	// All new records written

		timestamp   += m_buf[current_pos+WS_DELAY]*60;	// Update timestamp
		current_pos =  inc_ptr(current_pos);
	};
	
	
	return(0);
}

/*****************************************************************************/
int WeatherStation::read(){
// Read fixed block
// - Get current_pos
// - Get data_count
// Read records backwards from current_pos untill previous current_pos reached
// Step 0x10 in the range 0x10000 to 0x100, wrap at 0x100
// USB is read in 0x20 byte chunks, so read at even positions only
// return 1 if new data, otherwise 0

	m_timestamp = time(NULL);	// Set to current time
	old_pos	    = unsigned_short(&m_buf[WS_CURRENT_POS]);
	
	int 		n, NewDataFlg = read_fixed_block();

	unsigned char	DataBuf[WS_BUFFER_CHUNK];
	
	unsigned short	data_count = unsigned_short(&m_buf[WS_DATA_COUNT]);
	unsigned short	current_pos= unsigned_short(&m_buf[WS_CURRENT_POS]);
	unsigned short	i;
	
	if(current_pos%WS_BUFFER_RECORD) {
		MsgPrintf(0, "CWS_Read: wrong current_pos=0x%04X\n", current_pos);
		exit(1);
	}
	for (i=0; i<data_count; ) {
		if (!(current_pos&WS_BUFFER_RECORD)) {
			// Read 2 records on even position
			n = usb.read_block(current_pos, (char*)DataBuf);
			if(n<32)
				exit(1);
			i += 2;
			NewDataFlg |= dataHasChanged(&m_buf[current_pos], DataBuf, sizeof(DataBuf));
		}
		if(current_pos==(old_pos &(~WS_BUFFER_RECORD)))
			break;	//break only on even position
		current_pos = dec_ptr(current_pos);
	}
	if((old_pos==0)||(old_pos==0xFFFF))	//cachefile empty or empty eeprom was read
		old_pos = inc_ptr(current_pos);

	return NewDataFlg;
}

int WeatherStation::open()
{ /* returns 0 if OK, <0 if error */
	char	Buf[40];
	int	ret = 0;

		ret = usb.open(0x1941, 0x8021);

	if(ret==0) {
		cache(WS_CACHE_READ);	// Read cache file
		strftime(Buf,sizeof(Buf),"%Y-%m-%d %H:%M:%S", localtime(&m_previous_timestamp));
		MsgPrintf(2, "last cached record %s\n", Buf);
		printf("USB WheterStation is open \n");
	}
	return ret;
}

int WeatherStation::close(int new_data_flag)
{
	char	Buf[40];

	if(new_data_flag) cache(WS_CACHE_WRITE);	// Write cache file
	strftime(Buf,sizeof(Buf),"%Y-%m-%d %H:%M:%S", localtime(&m_timestamp));
	MsgPrintf(2, "last record read   %s\n", Buf);
		usb.close();
	return 0;
}
short WeatherStation::dataHasChanged(unsigned char OldBuf[], unsigned char NewBuf[], size_t size)
{	// copies size bytes from NewBuf to OldBuf, if changed
	// returns 0 if nothing changed, otherwise 1
	short NewDataFlg = 0, i;
	
	for(i=0; i<size; ++i) {
		if(OldBuf[i]!=NewBuf[i]) {
			NewDataFlg = 1;
			MsgPrintf(3, "%04X(+%02X): %02X -> %02X\n",
				  (unsigned short)(&OldBuf[0]-m_buf), i,
				  OldBuf[i], NewBuf[i]); 
			OldBuf[i] = NewBuf[i];
		}
	}
	return NewDataFlg;
}

/*---------------------------------------------------------------------------*/

short WeatherStation::read_fixed_block()
{	// Read fixed block in 32 byte chunks
	unsigned short	i;
	unsigned char	fb_buf[WS_FIXED_BLOCK_SIZE];
	char		NewDataFlg = 0;
	
	for(i=WS_FIXED_BLOCK_START;i<WS_FIXED_BLOCK_SIZE;i+=WS_BUFFER_CHUNK)
		if(usb.read_block(i, (char*)&fb_buf[i])<0)
			return 0; //failure while reading data
	// Check for new data
	memcpy(&m_buf[WS_FIXED_BLOCK_START], fb_buf, 0x10); //disables change detection on the rain val positions 
	NewDataFlg = dataHasChanged(&m_buf[WS_FIXED_BLOCK_START], fb_buf, sizeof(fb_buf));
	// Check for valid data
	if(((m_buf[0]==0x55) && (m_buf[1]==0xAA))
	|| ((m_buf[0]==0xFF) && (m_buf[1]==0xFF)))
		return NewDataFlg;
	
	MsgPrintf(0, "Fixed block is not valid.\n");
	exit(1);
}

int WeatherStation::calculate_rain_period(unsigned short pos, unsigned short begin, unsigned short end)
{
	unsigned short begin_rain = unsigned_short(&m_buf[begin]);
	unsigned short end_rain   = unsigned_short(&m_buf[end]);

	if(begin_rain==0xFFFF) {
		MsgPrintf(0, "calc_rain: invalid rain value at 0x%04X\n", begin);
		return -1;				// invalid value
	}
	if(end_rain==0xFFFF) { 
		MsgPrintf(0, "calc_rain: invalid rain value at 0x%04X\n", end);
		return -2;				// invalid value
	}
	unsigned short result = end_rain - begin_rain;

	m_buf[pos]	= result & 0xFF;		// Lo byte
	m_buf[pos+1]	= (result >> 8) & 0xFF;		// Hi byte

	return 0;
}



int WeatherStation::calculate_rain(unsigned short current_pos, unsigned short data_count)
{
	// Initialize rain variables
	m_buf[WS_RAIN_HOUR]	= 0;	m_buf[WS_RAIN_HOUR +1]	= 0;
	m_buf[WS_RAIN_DAY]	= 0;	m_buf[WS_RAIN_DAY  +1]	= 0;
	m_buf[WS_RAIN_WEEK]	= 0;	m_buf[WS_RAIN_WEEK +1]	= 0;
	m_buf[WS_RAIN_MONTH]	= 0;	m_buf[WS_RAIN_MONTH+1]	= 0;

	// Set the different time periods
	unsigned short hour	=       60;
	unsigned short day	=    24*60;
	unsigned short week	=  7*24*60;
	unsigned short month	= 30*24*60;

	unsigned short initial_pos = current_pos;
	unsigned short dt       = 0;

	unsigned short i;
	// Calculate backwards through buffer, not all values will be calculated if buffer is too short
	for(i=0; i<data_count; i++) {
		if(m_buf[current_pos+WS_DELAY]==0xFF) {
			MsgPrintf(0, "CWS_calc_rain: invalid delay value at 0x%04X\n", current_pos+WS_DELAY);
			return -1;
		}
		if      (dt >= month) {
			calculate_rain_period(WS_RAIN_MONTH, current_pos+WS_RAIN, initial_pos+WS_RAIN);
			break;

		} else if(dt >= week) {
			calculate_rain_period(WS_RAIN_WEEK,  current_pos+WS_RAIN, initial_pos+WS_RAIN);
			week = 0xFFFF;

		} else if(dt >= day) {
			calculate_rain_period(WS_RAIN_DAY,   current_pos+WS_RAIN, initial_pos+WS_RAIN);
			day  = 0xFFFF;

		} else if(dt >= hour) {
			calculate_rain_period(WS_RAIN_HOUR,  current_pos+WS_RAIN, initial_pos+WS_RAIN);
			hour = 0xFFFF; //disable second calculation
		}
		dt         += m_buf[current_pos+WS_DELAY];	// Update time difference
		current_pos = dec_ptr(current_pos);
	}
	return (0);
}

float WeatherStation::dew_point(char* raw, float scale, float offset)
{
	float temp = signed_short((unsigned char*)raw+WS_TEMPERATURE_OUT) * 0.1; // °C
	float hum = raw[WS_HUMIDITY_OUT];

	// Compute dew point, using formula from
	// http://en.wikipedia.org/wiki/Dew_point.
	float a = 17.27;
	float b = 237.7;

	float gamma = ((a * temp) / (b + temp)) + log(hum / 100);

	float dpoint = (b * gamma) / (a - gamma);	// °C	
	return dpoint * 10 * scale + offset;
}

unsigned WeatherStation::bcd_decode(unsigned char byte)
{
        unsigned char lo = byte & 0x0F;
        unsigned char hi = byte / 16;
        return (lo + (hi * 10));
}
unsigned short WeatherStation::unsigned_short(unsigned char* raw)
{
 	return ((unsigned short)raw[1] << 8) | raw[0];
}
signed short WeatherStation::signed_short(unsigned char* raw)
{
 	unsigned short us = ((((unsigned short)raw[1])&0x7F) << 8) | raw[0];
	
	if(raw[1]&0x80)	// Test for sign bit
		return -us;	// Negative value
	else
		return us;	// Positive value
}
int WeatherStation::decode(unsigned char* raw, enum ws_types ws_type, float scale, float offset, char* result)
{
	int           b = -(log(scale)+0.5), i, m = 0, n = 0;
	float         fresult;
	
	if(b<1) b = 1;
	if(!result) return 0;
	else *result = '\0';
	switch(ws_type) {
		case ub:
			m = 1;
			fresult = raw[0] * scale + offset;
			n=sprintf(result,"%.*f", b, fresult);
		break;
		case sb:
			m = 1;
			fresult = raw[0] & 0x7F;
			if(raw[0] & 0x80)	// Test for sign bit
				fresult -= fresult;	//negative value
			fresult = fresult * scale + offset;
			n=sprintf(result,"%.*f", b, fresult);
		break;
		case us:
			m = 2;
			fresult = unsigned_short(raw) * scale + offset;
			n=sprintf(result,"%.*f", b, fresult);
		break;
		case ss:
			m = 2;
			fresult = signed_short(raw) * scale + offset;
			n=sprintf(result,"%.*f", b, fresult);
		break;
		case dt:
		{
			unsigned char year, month, day, hour, minute;
			year   = bcd_decode(raw[0]);
			month  = bcd_decode(raw[1]);
			day    = bcd_decode(raw[2]);
			hour   = bcd_decode(raw[3]);
			minute = bcd_decode(raw[4]);
			m = 5;
			n=sprintf(result,"%4d-%02d-%02d %02d:%02d", year + 2000, month, day, hour, minute);
		}
		break;
		case tt:
			m = 2;
			n=sprintf(result,"%02d:%02d", bcd_decode(raw[0]), bcd_decode(raw[1]));
		break;
		case pb:
			m = 1;
			n = sprintf(result,"%02x", raw[0]);
		break;
		case wa:
			m = 3;
			// wind average - 12 bits split across a byte and a nibble
			fresult = raw[0] + ((raw[2] & 0x0F) * 256);
			fresult = fresult * scale + offset;
			n=sprintf(result,"%.*f", b, fresult);
		break;
		case wg:
			m = 3;
			// wind gust - 12 bits split across a byte and a nibble
			fresult = raw[0] + ((raw[1] & 0xF0) * 16);
			fresult = fresult * scale + offset;
			n=sprintf(result,"%.*f", b, fresult);
		break;
		case dp:
			m = 1; //error checking for delay
			// Scale outside temperature and calculate dew point
			fresult = dew_point((char*)raw, scale, offset);
			n=sprintf(result,"%.*f", b, fresult);
		break;
		default:
			MsgPrintf(0, "CWS_decode: Unknown type %u\n", ws_type);
	}
	for(i=0; i<m; ++i) {
		if(raw[i]!=0xFF) return n;
	}
	if(m) {
		MsgPrintf(0, "CWS_decode: invalid value at 0x%04X\n", raw);
		sprintf(result,"--.-");
		n = 0;
	}
	return n;	
}
void WeatherStation::cache(char isStoring){
	{
	int	n;
	char	fname[] = WORKPATH"wetdmn.dat";	// cache file
	char	Buf[40];
	FILE*	f = NULL;
	
	if (isStoring == WS_CACHE_READ) {
		if (f=fopen(fname,"rb")) {
			n=fread(&m_previous_timestamp,sizeof(m_previous_timestamp),1,f);
			n=fread(m_buf,sizeof(m_buf[0]),WS_BUFFER_SIZE,f);
		}
	}
	else {	// WS_CACHE_WRITE
		if(m_timestamp<3600) {
			strftime(Buf,sizeof(Buf),"%Y-%m-%d %H:%M:%S", localtime(&m_timestamp));
			MsgPrintf(0, "wrong timestamp %s - cachefile not written\n", Buf);
		
		}
		else if (f=fopen(fname,"wb")) {
			n=fwrite(&m_timestamp,sizeof(m_timestamp),1,f);
			n=fwrite(m_buf,sizeof(m_buf[0]),WS_BUFFER_SIZE,f);
		}
	}
	if (f) fclose(f);
}
}

int WeatherStation::readStation(int tab[], int params_count)
{
	

	
	int NewDataFlg	= 1;	// write to cache file or not
	char	Buf[40], Buf2[200];

	
	strcpy(LogPath, WORKPATH);

	if(this->open()==0) {	// Read the cache file and open the weather station
	
		if (true)
			if(read())		// Read the weather station
				NewDataFlg = 1;
		
	
		//calc press. offset (representing station height)
		pressOffs_hPa = 0.1 * (
			unsigned_short(&m_buf[WS_CURR_REL_PRESSURE])
		      - unsigned_short(&m_buf[WS_CURR_ABS_PRESSURE])
		);

		float buffet[10];

		getData(buffet ); // write data to buffer;
		
		for(int i=0; i<params_count ; i++) {tab[i]=buffet[i]*10; printf(" %f \n", buffet[i] );};		
		
		
		close(NewDataFlg);	// Write the cache file and close the weather station

	
	}	
	return 0;
}


