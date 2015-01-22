/*  Fine Offset Weather Station Reader - Main file

   (C) Arne-Jørgen Auberg (arne.jorgen.auberg@gmail.com)

   This application reads WH1080 compatible devices using the USB port.
   Compatible with all USB stations that can use the EasyWeather app (www.foshk.com)

   The application is written with inspiration from the following projects:

  1)	WeatherStation.py - The pywws poject. http://pywws.googlecode.com

  2)	usbsnoop2libusb.pl - The usbsnoop log file.
	The latest version of the script should be in http://iki.fi/lindi/usb/usbsnoop2libusb.pl

  3)	wwsr.c - Wireless Weather Station Reader
	Michael Pendec (michael.pendec@gmail.com)

28.05.13 Josch (Josch at abwesend dot de) CUSB_Close(): ret-Auswertung korrigiert, assert entfernt
               log-Pfad einstellbar zur Compilezeit, Warnungen beseitigt, Option -v, Option -f
01.06.13 Josch neues Format WS3600
15.06.13 Josch option-Handling komplett �berarbeitet
17.06.13 Josch Meldungslog mit versch. Levels wahlweise auf Console und/oder in Datei
02.07.13 Josch CWS_signed_short() korrigiert
05.07.13 Josch bei -c nur aktuellen Datensatz ausgeben
12.07.13 Josch Check return codes in CUSB_read_block()
16.07.13 Josch CWS_print_decoded_data() vereinfacht
23.07.13 Josch Log Levels ge�ndert
19.08.13 Josch Dougs barometer correction from 27.09.12 included
10.09.13 Josch cache file nur schreiben bei gueltigem Zeitstempel, Typ von CUSB_read_block() geaendert
               Test auf falschen Zeiger und Lesefehler in CWS_Read()
26.09.13 Josch Includes moved from fowsr.h, c99 style removed
01.10.13 Josch default name of fhem logfile changed, msg if log could not be opened,
	       delimiters for WUG changed
02.10.13 Josch CWS_decode: prec depending on scale
05.10.13 Josch conversion of negative values corrected
10.10.13 Josch calculation of rain and rel. pressure corrected
11.10.13 Josch output rel. pressure in ws3600_format
15.10.13 Josch checking for invalid values in CWS_decode()
18.10.13 Josch time format for pws corrected
28.03.14 Josch CWS_dew_point() corrected for �F
*/

#define VERSION "V2.0.140328"

#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include <usb.h>



//#include "base_daemon.h"
//#include "log_prefix.h"

/***************** macros ****************************************************/
// WORKPATH	default path for all outputfiles (log, dat, msg)
//		path for dat can be changed with option -n
// LOGPATH	default full name for weather log files
/* original, but bad */
//#define WORKPATH "//var//

/* on PC e.g. Ubuntu */
//#define WORKPATH "//home//user//FOWSR//fowsr-read-only//fowsr.src//"

/* on Raspberry */
#define WORKPATH "//var//log//fowsr//"

#define LOGPATH WORKPATH"%s.log"

/***************** variables *************************************************/
//global used options
int		LogToScreen	= 0;	// log to screen
int		readflag	= 0;	// Read the weather station or use the cache file.
int		vLevel		= 0;	// print more messages (0=only Errors, 3=all)
char		vDst		= 'c';	// print more messages ('c'=ToScreen, 'f'=ToFile, 'b'=ToBoth)

unsigned short	old_pos		= 0;	// last index of previous read
char		LogPath[255]	= "";
float		pressOffs_hPa   = 0;

/*****************************************************************************/
#include "daemon.h"

/******* helper functions ****************************************************/
void  MsgPrintf(int Level, const char *fmt, ...)
{
	char    Buf[200];
	va_list argptr;
	FILE	*f;

	if(Level>vLevel)
		return;
	va_start(argptr, fmt);
	vsprintf(Buf, fmt, argptr);
	va_end(argptr);
	if(vDst!='f') {
		printf("%s", Buf);
	}
	if((vDst=='b')||(vDst=='f')) {
		f = fopen(WORKPATH"fowsr.msg", "at");
		if(f) {
			fprintf(f, "%s", Buf);
			fclose(f);
		}
	}
}



/***************** libusb functions ******************************************/
/*void list_devices() {
    struct usb_bus *bus;
    for (bus = usb_get_busses(); bus; bus = bus->next) {
	struct usb_device *dev;

	for (dev = bus->devices; dev; dev = dev->next)
	    printf("0x%04x 0x%04x\n",
		   dev->descriptor.idVendor,
		   dev->descriptor.idProduct);
    }
}*/

/*---------------------------------------------------------------------------*/
struct usb_device *find_device(int vendor, int product) {
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

/***************** The CUSB class ********************************************/
int CUSB_Open(int vendor, int product)
{ /* returns 0 if OK, <0 if error */
	int ret;
	char buf[1000];

	usb_init();
	if(vDst!='f')
		usb_set_debug(vLevel+1);
	usb_find_busses();
	usb_find_devices();

	dev = find_device(vendor, product);
	if(!dev) {
		MsgPrintf(0, "Weatherstation not found on USB (vendor,product)=(%04X,%04X)\n", vendor, product);
		return -1;
	}
	devh = usb_open(dev);
	if(!devh) {
		MsgPrintf(0, "Open USB device failed (vendor,product)=(%04X,%04X)\n", vendor, product);
		return -2;
	}
	signal(SIGTERM, CUSB_Close);
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
void CUSB_Close()
{
	int ret = usb_release_interface(devh, 0);
	if(ret) MsgPrintf(0, "failed to release interface: %d\n", ret);
	ret = usb_close(devh);
	if(ret) MsgPrintf(0, "failed to close interface: %d\n", ret);
}

/*---------------------------------------------------------------------------*/
short CUSB_read_block(unsigned short ptr, char* buf)
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
	if(ret<0) MsgPrintf(0, "usb_control_msg failed (%d) whithin CUSB_read_block(%04X,...)\n", ret, ptr);
	else {
		// Read 32-byte chunk and place in buffer buf
		ret = usb_interrupt_read(devh, 0x81, buf, 0x20, 1000);
		if(ret<0) MsgPrintf(0, "usb_interrupt_read failed (%d) whithin CUSB_read_block(%04X,...)\n", ret, ptr);
	}
	return ret;
}

/*---------------------------------------------------------------------------*/
#ifdef NotUsed
unsigned short CUSB_write_byte(unsigned short ptr, char* buf)
{
/*
Write one byte data to ADDR command	

If data has been received and written correctly, 
the device will return 8 bytes 0xA5 indicating the command has been carried out sucessfully.
*/
	char buf_1 = (char)(ptr / 256);
	char buf_2 = (char)(ptr & 0xFF);
	char tbuf[8];
	tbuf[0] = 0xA2;		// WRITE COMMAND
	tbuf[1] = buf_1;	// WRITE ADDRESS HIGH
	tbuf[2] = buf_2;	// WRITE ADDRESS LOW
	tbuf[3] = 0x20;		// END MARK
	tbuf[4] = 0xA2;		// WRITE COMMAND
	tbuf[5] = *buf;		// DATA TO BE WRITTEN
	tbuf[6] = 0;		// DON'T CARE
	tbuf[7] = 0x20;		// END MARK

	int ret;
	// Prepare write of 32-byte chunk from position ptr
	ret = usb_control_msg(devh, USB_TYPE_CLASS + USB_RECIP_INTERFACE, 9, 0x200, 0, tbuf, 8, 1000);
	// Write 32-byte chunk from buffer buf
	ret = usb_interrupt_write(devh, 0x81, buf, 0x20, 1000);
	// Read 8-byte result and place in buffer tbuf
	ret = usb_interrupt_read(devh, 0x81, tbuf, 0x08, 1000);

	return ret;
}

/*---------------------------------------------------------------------------*/
unsigned short CUSB_write_block(unsigned short ptr, char* buf)
{
/*
Write 32 bytes data command	
	
After sending the write command, the 32 bytes data load must be sent to device within 500ms. 
Once the 32 bytes data have been written to the EEPROM sucessfully, 
then the device will return 8 bytes of 0xA5 telling that the data has been written correctly.
*/
	char buf_1 = (char)(ptr / 256);
	char buf_2 = (char)(ptr & 0xFF);
	char tbuf[8];
	tbuf[0] = 0xA0;		// WRITE COMMAND
	tbuf[1] = buf_1;	// WRITE ADDRESS HIGH
	tbuf[2] = buf_2;	// WRITE ADDRESS LOW
	tbuf[3] = 0x20;		// END MARK
	tbuf[4] = 0xA0;		// WRITE COMMAND
	tbuf[5] = 0;		// DON'T CARE
	tbuf[6] = 0;		// DON'T CARE
	tbuf[7] = 0x20;		// END MARK

	int ret;
	// Prepare write of 32-byte chunk from position ptr
	ret = usb_control_msg(devh, USB_TYPE_CLASS + USB_RECIP_INTERFACE, 9, 0x200, 0, tbuf, 8, 1000);
	// Write 32-byte chunk from buffer buf
	ret = usb_interrupt_write(devh, 0x81, buf, 0x20, 1000);
	// Read 8-byte result and place in buffer tbuf
	ret = usb_interrupt_read(devh, 0x81, tbuf, 0x08, 1000);

	return ret;
}
#endif // NotUsed

/***************** The CWS class *********************************************/
void CWS_Cache(char isStoring)
{
	int	n;
	char	fname[] = WORKPATH"fowsr.dat";	// cache file
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

/*---------------------------------------------------------------------------*/
/*void CWS_decode_data(int * buffor)
{
	char s2[100];
	int  i;
	int n=0;
	
	for(i=WS_LOWER_FIXED_BLOCK_START; i<WS_LOWER_FIXED_BLOCK_START+15; i++) {
		
		CWS_decode(&m_buf[ws_format[i].pos], ws_format[i].ws_type, ws_format[i].scale,	0.0, 	s2);
		//printf("%s=%s\n", ws_format[i].name, s2);
		if(n<15){
			
			buffor[n]=(int)atoi(s2);	
			n++;
		}
	}
}*/

/*---------------------------------------------------------------------------*/
unsigned short CWS_inc_ptr(unsigned short ptr)
{
	// Step forward through buffer.
	ptr += WS_BUFFER_RECORD;             
	if((ptr > WS_BUFFER_END)||(ptr < WS_BUFFER_START))
		// End is reached, step to start of buffer.
		ptr = WS_BUFFER_START;
	return ptr;
}

/*---------------------------------------------------------------------------*/
/***************** The CWF class *********************************************/
int CWF_Write(int arg, const char* fname, const char* ftype, float* buffer)
{
// - Get current_pos
// - Get data_count
// Read data_count records forward from old_pos to current_pos. 
// Calculate timestamp and break if already written
// Step 0x10 in the range 0x10000 to 0x100
// Store output file in requested format
	

	time_t 		timestamp   = m_timestamp - m_timestamp%60;	// Set to current minute

	unsigned short	data_count  = CWS_unsigned_short(&m_buf[WS_DATA_COUNT]);
	unsigned short	current_pos = CWS_unsigned_short(&m_buf[WS_CURRENT_POS]);
	unsigned short	end_pos	    = current_pos, i;
	char		s1[1000]    = "", s2[1000] = "";
	int		n, j;
	//FILE* 		f	    = stdout;
	//int		FileIsEmpty = 0;
	unsigned short	dat2_count  = data_count;	//end point for rain calculation

	
	if((old_pos==0)||(old_pos==0xFFFF))	//cachefile empty or empty eeprom was read
		old_pos = current_pos;
	
	// Header
	/*switch (arg) {
		case 'x':
			fputs("<ws>\n",f);
			break;
	};*/

	// Body
	if(arg!=0) while(current_pos!=old_pos) {		// get record & time to start output from
		timestamp  -= m_buf[current_pos+WS_DELAY]*60;	// Update timestamp
		current_pos = CWS_dec_ptr(current_pos);
		--dat2_count;
	}
	
	printf("data_count %d \n", data_count);	
	for(i=0; i<data_count; i++)
	{
		if((arg!=0))
			CWS_calculate_rain(current_pos, dat2_count+i);

		//if((arg!=0)&&LogToScreen&&(current_pos==end_pos))
		//	break;	// current record is logged by FHEM itself if -c is set
		
		// Save in pywws raw format
				n=strftime(s1,100,"%Y-%m-%d %H:%M:%S", gmtime(&timestamp));
				for (j=0;j<WS_PYWWS_RECORDS;j++) {
					CWS_decode(&m_buf[current_pos+pywws_format[j].pos],
							pywws_format[j].ws_type,
							pywws_format[j].scale,
							0.0,
							s2);
					//sprintf(s1+strlen(s1), ",%s", s2);
					//printf("%s \n", s2);
					if(j<10) buffer[j]=atof(s2); //get data without timestams
				};

	

		strcat(s1,"\n");
		//fputs(s1,f);

		if(current_pos==end_pos)
			break;	// All new records written

		timestamp   += m_buf[current_pos+WS_DELAY]*60;	// Update timestamp
		current_pos =  CWS_inc_ptr(current_pos);
	};
	
	// Footer
	

	//if(arg!='c') fclose(f);
	
	return(0);
}

/*****************************************************************************/

/*---------------------------------------------------------------------------*/
int CWS_Open()
{ /* returns 0 if OK, <0 if error */
	char	Buf[40];
	int	ret = 0;

	if(readflag)
		ret = CUSB_Open(0x1941, 0x8021);

	if(ret==0) {
		CWS_Cache(WS_CACHE_READ);	// Read cache file
		strftime(Buf,sizeof(Buf),"%Y-%m-%d %H:%M:%S", localtime(&m_previous_timestamp));
		MsgPrintf(2, "last cached record %s\n", Buf);
	}
	return ret;
}

/*---------------------------------------------------------------------------*/
int CWS_Close(int NewDataFlg)
{
	char	Buf[40];

	if(NewDataFlg) CWS_Cache(WS_CACHE_WRITE);	// Write cache file
	strftime(Buf,sizeof(Buf),"%Y-%m-%d %H:%M:%S", localtime(&m_timestamp));
	MsgPrintf(2, "last record read   %s\n", Buf);
	if(readflag)
		CUSB_Close();
	return 0;
}

/*---------------------------------------------------------------------------*/
unsigned short CWS_dec_ptr(unsigned short ptr)
{
	// Step backwards through buffer.
	ptr -= WS_BUFFER_RECORD;             
	if (ptr < WS_BUFFER_START)
		// Start is reached, step to end of buffer.
		ptr = WS_BUFFER_END;
	return ptr;
}


short CWS_DataHasChanged(unsigned char OldBuf[], unsigned char NewBuf[], size_t size)
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
short CWS_read_fixed_block()
{	// Read fixed block in 32 byte chunks
	unsigned short	i;
	unsigned char	fb_buf[WS_FIXED_BLOCK_SIZE];
	char		NewDataFlg = 0;

	for(i=WS_FIXED_BLOCK_START;i<WS_FIXED_BLOCK_SIZE;i+=WS_BUFFER_CHUNK)
		if(CUSB_read_block(i, &fb_buf[i])<0)
			return 0; //failure while reading data
	// Check for new data
	memcpy(&m_buf[WS_FIXED_BLOCK_START], fb_buf, 0x10); //disables change detection on the rain val positions 
	NewDataFlg = CWS_DataHasChanged(&m_buf[WS_FIXED_BLOCK_START], fb_buf, sizeof(fb_buf));
	// Check for valid data
	if(((m_buf[0]==0x55) && (m_buf[1]==0xAA))
	|| ((m_buf[0]==0xFF) && (m_buf[1]==0xFF)))
		return NewDataFlg;
	
	MsgPrintf(0, "Fixed block is not valid.\n");
	exit(1);
}

/*---------------------------------------------------------------------------*/
int CWS_calculate_rain_period(unsigned short pos, unsigned short begin, unsigned short end)
{
	unsigned short begin_rain = CWS_unsigned_short(&m_buf[begin]);
	unsigned short end_rain   = CWS_unsigned_short(&m_buf[end]);

	if(begin_rain==0xFFFF) {
		MsgPrintf(0, "CWS_calc_rain: invalid rain value at 0x%04X\n", begin);
		return -1;				// invalid value
	}
	if(end_rain==0xFFFF) { 
		MsgPrintf(0, "CWS_calc_rain: invalid rain value at 0x%04X\n", end);
		return -2;				// invalid value
	}
	unsigned short result = end_rain - begin_rain;

	m_buf[pos]	= result & 0xFF;		// Lo byte
	m_buf[pos+1]	= (result >> 8) & 0xFF;		// Hi byte

	return 0;
}

/*---------------------------------------------------------------------------*/
int CWS_calculate_rain(unsigned short current_pos, unsigned short data_count)
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
			CWS_calculate_rain_period(WS_RAIN_MONTH, current_pos+WS_RAIN, initial_pos+WS_RAIN);
			break;

		} else if(dt >= week) {
			CWS_calculate_rain_period(WS_RAIN_WEEK,  current_pos+WS_RAIN, initial_pos+WS_RAIN);
			week = 0xFFFF;

		} else if(dt >= day) {
			CWS_calculate_rain_period(WS_RAIN_DAY,   current_pos+WS_RAIN, initial_pos+WS_RAIN);
			day  = 0xFFFF;

		} else if(dt >= hour) {
			CWS_calculate_rain_period(WS_RAIN_HOUR,  current_pos+WS_RAIN, initial_pos+WS_RAIN);
			hour = 0xFFFF; //disable second calculation
		}
		dt         += m_buf[current_pos+WS_DELAY];	// Update time difference
		current_pos = CWS_dec_ptr(current_pos);
	}
	return (0);
}

/*---------------------------------------------------------------------------*/
float CWS_dew_point(char* raw, float scale, float offset)
{
	float temp = CWS_signed_short(raw+WS_TEMPERATURE_OUT) * 0.1; // �C
	float hum = raw[WS_HUMIDITY_OUT];

	// Compute dew point, using formula from
	// http://en.wikipedia.org/wiki/Dew_point.
	float a = 17.27;
	float b = 237.7;

	float gamma = ((a * temp) / (b + temp)) + logarytm(hum / 100);

	float dpoint = (b * gamma) / (a - gamma);	// �C	
	return dpoint * 10 * scale + offset;
}

/*---------------------------------------------------------------------------*/
unsigned char CWS_bcd_decode(unsigned char byte)
{
        unsigned char lo = byte & 0x0F;
        unsigned char hi = byte / 16;
        return (lo + (hi * 10));
}

/*---------------------------------------------------------------------------*/
unsigned short CWS_unsigned_short(unsigned char* raw)
{
 	return ((unsigned short)raw[1] << 8) | raw[0];
}

signed short CWS_signed_short(unsigned char* raw)
{
 	unsigned short us = ((((unsigned short)raw[1])&0x7F) << 8) | raw[0];
	
	if(raw[1]&0x80)	// Test for sign bit
		return -us;	// Negative value
	else
		return us;	// Positive value
}

/*---------------------------------------------------------------------------*/
int CWS_decode(unsigned char* raw, enum ws_types ws_type, float scale, float offset, char* result)
{
	int           b = -(logarytm(scale)+0.5), i, m = 0, n = 0;
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
			fresult = CWS_unsigned_short(raw) * scale + offset;
			n=sprintf(result,"%.*f", b, fresult);
		break;
		case ss:
			m = 2;
			fresult = CWS_signed_short(raw) * scale + offset;
			n=sprintf(result,"%.*f", b, fresult);
		break;
		case dt:
		{
			unsigned char year, month, day, hour, minute;
			year   = CWS_bcd_decode(raw[0]);
			month  = CWS_bcd_decode(raw[1]);
			day    = CWS_bcd_decode(raw[2]);
			hour   = CWS_bcd_decode(raw[3]);
			minute = CWS_bcd_decode(raw[4]);
			m = 5;
			n=sprintf(result,"%4d-%02d-%02d %02d:%02d", year + 2000, month, day, hour, minute);
		}
		break;
		case tt:
			m = 2;
			n=sprintf(result,"%02d:%02d", CWS_bcd_decode(raw[0]), CWS_bcd_decode(raw[1]));
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
			fresult = CWS_dew_point(raw, scale, offset);
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

/*---------------------------------------------------------------------------*/
int CWS_Read()
{
// Read fixed block
// - Get current_pos
// - Get data_count
// Read records backwards from current_pos untill previous current_pos reached
// Step 0x10 in the range 0x10000 to 0x100, wrap at 0x100
// USB is read in 0x20 byte chunks, so read at even positions only
// return 1 if new data, otherwise 0

	m_timestamp = time(NULL);	// Set to current time
	old_pos	    = CWS_unsigned_short(&m_buf[WS_CURRENT_POS]);

	int 		n, NewDataFlg = CWS_read_fixed_block();
	unsigned char	DataBuf[WS_BUFFER_CHUNK];

	unsigned short	data_count = CWS_unsigned_short(&m_buf[WS_DATA_COUNT]);
	unsigned short	current_pos= CWS_unsigned_short(&m_buf[WS_CURRENT_POS]);
	unsigned short	i;

	if(current_pos%WS_BUFFER_RECORD) {
		MsgPrintf(0, "CWS_Read: wrong current_pos=0x%04X\n", current_pos);
		exit(1);
	}
	for (i=0; i<data_count; ) {
		if (!(current_pos&WS_BUFFER_RECORD)) {
			// Read 2 records on even position
			n = CUSB_read_block(current_pos, DataBuf);
			if(n<32)
				exit(1);
			i += 2;
			NewDataFlg |= CWS_DataHasChanged(&m_buf[current_pos], DataBuf, sizeof(DataBuf));
		}
		if(current_pos==(old_pos &(~WS_BUFFER_RECORD)))
			break;	//break only on even position
		current_pos = CWS_dec_ptr(current_pos);
	}
	if((old_pos==0)||(old_pos==0xFFFF))	//cachefile empty or empty eeprom was read
		old_pos = CWS_inc_ptr(current_pos);

	return NewDataFlg;
}

/***************** The CWF class *********************************************/

int readStation()
{
	int bflag	= 0;
	int rflag	= 0;
	int dflag	= 0;	// Dump decoded fixed block data
	int pflag = 1;
	

	
	int NewDataFlg	= 0;	// write to cache file or not
	int 	c;
	time_t	tAkt	= time(NULL);
	char	Buf[40], Buf2[200];

	//strcpy(LogPath, LOGPATH);
	
	
	if(0==CWS_Open()) {	// Read the cache file and open the weather station

		if (readflag)
			if(CWS_Read())		// Read the weather station
				NewDataFlg = 1;
		printf("New data %d", NewDataFlg);
		//calc press. offset (representing station height)
		pressOffs_hPa = 0.1 * (
			CWS_unsigned_short(&m_buf[WS_CURR_REL_PRESSURE])
		      - CWS_unsigned_short(&m_buf[WS_CURR_ABS_PRESSURE])
		);
		// Write the log files
		float buffet[10];
		if (pflag)
			CWF_Write(pflag, LogPath, "pywws",buffet );
		
		int i;
		for(i=0; i<10 ; i++) printf(" %f \n", buffet[i] );		
		
		
		CWS_Close(NewDataFlg);	// Write the cache file and close the weather station

	
	}	
	return 0;
}

int main(int argc, char **argv){
	readStation();
}
/******************************** EOF ****************************************/