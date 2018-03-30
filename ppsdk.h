/**
 *@file  ppsdk.h
 *SDK document interface specification
 *@author HF.CHEN
 */

#ifndef _PPS_SDK_H_
#define _PPS_SDK_H_

/**<P2P type*/
#define UNUSE_P2P 1
#define USE_VV_P2P 0
#define USE_TUTK_P2P 0

/**<ffmpeg enable*/
#define PPS_FFMPEG_ENABLE 0

/**<nan ning customized*/
#define NANNING_CUSTOMIZED 1

/**<version*/
#define PPS_CURRENT_VERSION (PPS_VERSION_1_0|PPS_VERSION_1_1)

#define PPS_VERSION_1_0  1<<0
#define PPS_VERSION_1_1  1<<1
#define PPS_VERSION_1_2  1<<2

/**<common types*/
#define PPS_MAX_UUID_LENGTH 256
#define PPS_MAX_SN_LENGTH 64
#define PPS_MAX_SINGLE_SEARCH_DEVICE_INFO_NUMS 128
#define PPS_MAX_PPSDEV_STORAGE_SINGAL_INFO_NUMS 8
#define PPS_MAX_USERNAME_LENGTH 32
#define PPS_MAX_PASSWORD_LENGTH 32
#define PPS_MAX_SHORT_PASSWORD_LENGTH 16
#define PPS_MAX_SSID_LENGTH 32 
#define PPS_MAX_IP_LENGTH 32

#define PPS_MAX_DEVICE_NAME_LENGTH 32
#define PPS_MAX_DEVICE_MODEL_LENGTH 32
#define PPS_MAX_DEVICE_SERIANO_LENGTH 64
#define PPS_MAX_DEVICE_SOFTWAREVERSION_LENGTH 32
#define PPS_MAX_DEVICE_HAEDWAREVERSION_LENGTH 32
#define PPS_MAX_DEVICE_FIREWAREVERSION_LENGTH 128

#define PPS_MAX_CCID_LENGTH 32
#define PPS_MAX_IMSI_LENGTH 32
#define PPS_MAX_NTP_SERVER_LENGTH 64

#if defined(__APPLE__)||defined(__ANDROID__)||defined(__linux__)
#include <inttypes.h>
#endif

#if defined(__APPLE__)||defined(__linux__)
#ifndef CALLBACK
#define CALLBACK
#endif

#ifdef __cplusplus
#define PPSAPI extern "C"
#else
#define PPSAPI extern
#endif
#elif defined(_WIN32)
#ifndef  CALLBACK
#define  CALLBACK __stdcall
#endif
#ifdef __cplusplus
#define PPSAPI extern "C" __declspec(dllexport)
#else
#define PPSAPI
#endif
#endif

/***************************************************************************************
 *@brief ppsdk error code
 ***************************************************************************************/

#define  PPSDK_OP_SUCCESS                  0   /**<success*/
#define  PPSDK_OP_FAILED                  -1   /**<failed*/
#define  PPSDK_NOT_INIT                   -2   /**<ppsdk not init*/
#define  PPSDK_INVALID_HANDLE             -3   /**<invalid handle*/
#define  PPSDK_DEV_OFFLINE                -4   /**<device offline*/
#define  PPSDK_NOT_SUPPORT                -5   /**<not support*/
#define  PPSDK_INVALID_PARAMS             -6   /**<invalid param*/
#define  PPSDK_CONNECT_FAILED             -7   /**<connect failed*/
#define  PPSDK_GET_PARAMS_FAILED          -8   /**<get param failed*/
#define  PPSDK_CLOSE_PREVIEW_FAILED       -9   /**<get param failed*/
#define  PPSDK_CLOSE_PLAYBACK_FAILED      -10   /**<get param failed*/
#define  PPSDK_CLOSE_VOICETALK_FAILED     -11   /**<get param failed*/
#define  PPSDK_NOT_INIT_P2P               -12  /**<not init p2p*/
#define  PPSDK_DEFAULT_VALUE              -1 /**<if you not want to set param,then take it value*/

/***************************************************************************************
 *@brief 0.ppsdk init first.
 ***************************************************************************************/
/**
 *@brief Initialization ppsdk library.
 *This initialization function is mainly used to initialize global variables inside the library ppsdk
 *@param[in] NULL
 *@return 0- successfully <0 error code
 */
PPSAPI int CALLBACK pps_init(void);

/**
 *@brief Release ppsdk library.
 *This initialization function is mainly used for cast pp sdk repository internal global variables
 *@param[in] NULL
 *@return 0- successfully <0 error code
 */
PPSAPI int CALLBACK pps_free(void);

/***************************************************************************************
 *@brief 1.smart configure wifi or ap configure wifi
 ***************************************************************************************/
 typedef struct
{
    char SSID[PPS_MAX_SSID_LENGTH];    /**<SSID*/
    char password[PPS_MAX_PASSWORD_LENGTH];/**<password of SSID*/
    int  sleep_ms;  /**<Broadcast packet sending interval*/
    int  KEY_WPA_TYPE;/**<0-KEY_MGMT_OPEN 1-KEY_MGMT_WEP 2-KEY_MGMT_WPA_PSK 3-KEY_MGMT_WPA_ENTPRISE 4-KEY_MGMT_WPA2_PSK*/
    int  type; /**<The default is 0;Customized version of fill 1*/
    char name[PPS_MAX_USERNAME_LENGTH];/**<32 bytes padded with customized versions usrname[32]*/
    char passwd[PPS_MAX_PASSWORD_LENGTH];/**<32 bytes padded with customized versions passwd[32]*/
}WIFI_INFO;

/**
 *@brief Set line equipment wifi(call after pps_Init)
 *@param[in] wifiInfo- info of wifi
 *@return 0- successfully <0 error code
 */
PPSAPI int  CALLBACK pps_set_device_wifi(WIFI_INFO* wifiInfo);

PPSAPI int  CALLBACK pps_set_device_wifi_stop();

typedef struct
{
    char SSID[PPS_MAX_SSID_LENGTH];    /**<SSID*/
    char password[PPS_MAX_PASSWORD_LENGTH];/**<password of SSID*/
    int  KEY_WPA_TYPE;/**<0-KEY_MGMT_OPEN 1-KEY_MGMT_WEP 2-KEY_MGMT_WPA_PSK 3-KEY_MGMT_WPA_ENTPRISE 4-KEY_MGMT_WPA2_PSK*/
}WIFI_CFG;

/**
 *@brief Set the AP device wificfg.
 *@param[in] wificfg -Device wificfg.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK pps_set_AP_device_wificfg(WIFI_CFG* wificfg);

/***************************************************************************************
 *@brief 2.after smart configure wifi,we can call pps_search_device to search devices.
 ***************************************************************************************/
typedef struct
{
#if (PPS_CURRENT_VERSION&PPS_VERSION_1_1)
	char uuid[PPS_MAX_UUID_LENGTH]; /**<uuid of device*/
#endif
    char sn[PPS_MAX_SN_LENGTH]; /**<sn of device*/
    unsigned int  ip; /**<ip of device*/
}SINGLE_SEARCH_DEVICE_INFO;

typedef struct
{
    int nums;  /**<nums of online devices*/
    SINGLE_SEARCH_DEVICE_INFO deviceinfo[PPS_MAX_SINGLE_SEARCH_DEVICE_INFO_NUMS]; /**<info of one device*/
}SEARCH_DEVICE_INFO;

/**
 *@brief pps_search_device(call after pps_Init)
 *@param[out] searchdeviceinfo -- online devices
 *@return NULL
 */
PPSAPI int  CALLBACK pps_search_device(SEARCH_DEVICE_INFO* searchdeviceinfo);

PPSAPI void  CALLBACK pps_stop_search_device();

/***************************************************************************************
 *@brief 3.if sdk support tutk,we must init tutk
 ***************************************************************************************/
/**
 *@brief Get support P2P version
 *@return 0-no p2p 1-vv p2p 2-tutk p2p
 */
PPSAPI int  CALLBACK pps_get_support_p2p_type();

PPSAPI int CALLBACK pps_tutk_init(void);

PPSAPI int CALLBACK pps_tutk_exit(void);

/*
 *check tutk devices online or offline
 */
PPSAPI int CALLBACK ppsdev_tryconnect_tutk(char* uuid,int timeout);

PPSAPI int CALLBACK ppsdev_cancelconnect_tutk();

/**
 *@brief get P2P mode
 *@param[in] hdev -Session handle.
 *return 0: P2P mode, 1: Relay mode, 2: LAN mode, <0 see error code
 */
PPSAPI int  CALLBACK ppsdev_p2p_nat_type(int hdev);

/***************************************************************************************
 *@brief 4.login devices,before you set or get device info.
 ***************************************************************************************/
/**
 *@struct PPSDEV_LOGIN_INFO
 *@brief  Equipment login parameters structure
 */
typedef struct
{
	char uuid[PPS_MAX_UUID_LENGTH];    /**<Equipment uuid No.*/
	char username[PPS_MAX_USERNAME_LENGTH]; /**<Device Username*/
	char password[PPS_MAX_PASSWORD_LENGTH]; /**<Device password*/
	char devip[PPS_MAX_IP_LENGTH];    /**<devIP*/
    int  localport;    /**<P2p remote device 80 port mapping to the local port*/
}PPSDEV_LOGIN_INFO;

/**
 *@brief Log handle equipment and returns to the login.
 *This function is invoked pps_init () call after the function for logging equipment, and return to the conversations handle.
 *@param[in] info -Equipment login parameters structure.
 *@return > 0 session handle that behind interface calls hdev, <0 see error code
 */
PPSAPI int CALLBACK ppsdev_open(PPSDEV_LOGIN_INFO info);

/**
 *@brief if ppsdev_open not return,then you can ppsdev_stop_open.
 *@param[in] uuid -device uuid.
 *return 
 */
PPSAPI void CALLBACK ppsdev_stop_open(char* uuid);

/**
 *@brief Close Session Handle.
 *This function is used to shut down pps dev_open interface has returned session handle．
 *@param[in] hdev -Session handle.
 *@return 0- successfully <0 error code
 */
PPSAPI int CALLBACK ppsdev_close(int hdev);

/***************************************************************************************
 *@brief 5.get device caps.
 ***************************************************************************************/
/**
*@struct PPSDEV_CAPS_DEVICE_ETH
*@brief Equipment wired LAN capability set
*/
typedef struct
{
	char ipv6_support;   /**<0: ipv6 is not supported, 1: ipv6 support*/
	char dhcpv6_support; /**<0: dhcp ipv6 is not supported, 1: dhcpd ipv6 support*/
}PPSDEV_CAPS_DEVICE_ETH;

/**
*@struct PPSDEV_CAPS_DEVICE_DOT11
*@brief Equipment wireless LAN capability set
*/
typedef struct
{
	char ipv6_support;   /**<0: ipv6 is not supported, 1: ipv6 support*/
	char dhcpv6_support; /**<0: dhcp ipv6 is not supported, 1: dhcpd ipv6 support*/
}PPSDEV_CAPS_DEVICE_DOT11;

/**
*@struct PPSDEV_CAPS_DEVICE
*@brief Equipment capability set
*/
typedef struct
{
	PPSDEV_CAPS_DEVICE_ETH eth_caps;     /**<Equipment wired LAN capability set*/
	PPSDEV_CAPS_DEVICE_DOT11 dot11_caps; /**<Equipment wireless LAN capability set*/
	char ddns_support;                   /**<0: ddns not supported, 1: ddns Support*/
	char discovery_support;              /**<0: Device discovery is not supported, 1: device discovery support*/
	char firemware_upgrade_support;      /**<0: The firmware upgrade is not supported, 1: firmware upgrade support*/
	char systemlog_support;              /**<0: device does not support the system log, 1: Devices Syslog support*/
	char ntp_support;                    /**<0: The device does not support ntp school, 1: Support for the device sntp school*/
	char factory_reset_support;          /**<0: The device does not support the reset, 1: device reset support*/
	char reboot_support;                 /**<0: Reboot is not supported, 1: Reboot support*/
	char res[5];                         /**<Reserved field*/
}PPSDEV_CAPS_DEVICE;

/**
*@struct PPSDEV_CAPS_DEVICE_IO
*@brief The ability to set the device input and output ports
*/
typedef struct
{
	int video_sources; /**<The number of video sources*/
	int video_outputs; /**<The number of video source output*/
	int video_inputs; /**<The number of input video source*/
	int audio_sources; /**<The number of audio source*/
	int audio_outputs; /**<The number of output audio sources*/
	int audio_inputs; /**<The number of input audio sources*/
	int alarm_outputs; /**<The number of alarms output*/
	int alarm_inputs; /**<the number of alarm input*/
}PPSDEV_CAPS_DEVICE_IO;

/**
*@struct PPSDEV_CAPS_MEDIA_STREAM
*@brief Equipment stream transmission capability
*/
typedef struct
{
	char rtsp_support;   /**<0: rtsp not supported, 1: rtsp support*/
	char rtp_tcp_support; /**<0: rtp tcp does not support, 1: rtp tcp Support*/
	char rtp_rtsp_tcp_support; /**<0: rtp rtcp tcp does not support, 1: rtp rtsp tcp support*/
	char rtp_mult_support; /**<0: rtp_mult not supported, 1: rtp_mult Support*/
}PPSDEV_CAPS_MEDIA_STREAM;

/**
*@struct PPSDEV_CAPS_MEDIA
*@brief Equipment stream capability set
*/
typedef struct
{
    PPSDEV_CAPS_MEDIA_STREAM stream_caps; /**<Equipment stream transmission capability*/
}PPSDEV_CAPS_MEDIA;

/**
*@struct PPSDEV_CAPS_RECORD
*@brief Recording equipment capability set
*/
typedef struct
{
    char record_support; /**<0: The video is not supported, 1: Video support*/
	char res[3]; /**<Reserved field*/
}PPSDEV_CAPS_RECORD;

/**
*@struct PPSDEV_CAPS_EVENT
*@brief Device event capability set
*/
typedef struct
{
    int event_type; /**<0: Unsupported Event 1: System log Event 2: Motion Detection Event 3: Unusual system events*/
	int res[2]; /**<Reserved field*/
}PPSDEV_CAPS_EVENT;

/**
*@struct PPSDEV_CAPS_VOICETALK
*@brief The voice intercom capability set
*/
typedef struct
{
    char voicetalk_support; /**<0: does not support voice intercom 1: support voice intercom*/
	char voicetalk_type; /**<1: one-way intercom, 2: two-way intercom*/
	char res[2]; /**<Reserved field*/
}PPSDEV_CAPS_VOICETALK;

/**
*@struct PPSDEV_CAPS_PTZ
*@brief Equipment PTZ capability set
*/
typedef struct
{
	int ptz_caps;/**<PTZ capability set (can be combined): 0: none, 1: continuous movement, 2: relative position, 4: absolute position, 8: preset point, 16: scan up and down, 32: about scanning, 64: guard bit*/
}PPSDEV_CAPS_PTZ;

/**
*@struct PPSDEV_CAPS
*@brief Equipment total capability set
*/
typedef struct
{
	PPSDEV_CAPS_DEVICE 		device; /**<Equipment capability set*/
	PPSDEV_CAPS_DEVICE_IO 	device_io; /**<Device input and output capability set*/
	PPSDEV_CAPS_MEDIA		media; /**<Equipment stream capability set*/
	PPSDEV_CAPS_RECORD		record; /**<Recording equipment capability set*/
	PPSDEV_CAPS_EVENT		event; /**<Equipment capability set time*/
	PPSDEV_CAPS_VOICETALK	voicetalk; /**<The voice intercom capability set*/
	PPSDEV_CAPS_PTZ			ptz; /**<Equipment PTZ capability set*/
}PPSDEV_CAPS;

/**
 *@brief Total acquisition device capability set.
 *This function is invoked ppsdev_open () call after the function for acquiring a total capacity of set equipment.
 *@param[in] hdev -Equipment session handle.
 *@param[out] devcaps -Equipment total capability set.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_get_caps(int hdev, PPSDEV_CAPS* devcaps);

/***************************************************************************************
 *@brief 6.after login devices,you can get or set device info,such as devinfo,netlinkstatus,
 *energy,lteinfo,wificfg,ntp,timezone,reset,reboot,upgrade,format.
 ***************************************************************************************/
/**
*@struct PPSDEV_INFO
*@brief Device version
*/
typedef struct
{
	char devname[PPS_MAX_DEVICE_NAME_LENGTH];/**<Equipment name*/
	char model[PPS_MAX_DEVICE_MODEL_LENGTH];/**<Equipment Type*/
	char seriano[PPS_MAX_DEVICE_SERIANO_LENGTH];/**<Device serial number*/
	char softwareversion[PPS_MAX_DEVICE_SOFTWAREVERSION_LENGTH];/**<Device software version number*/
	char hardwareversion[PPS_MAX_DEVICE_HAEDWAREVERSION_LENGTH];/**<Device hardware version number*/
    char firmwareversion[PPS_MAX_DEVICE_FIREWAREVERSION_LENGTH];
#if NANNING_CUSTOMIZED
    char uuid[PPS_MAX_UUID_LENGTH];
#endif
}PPSDEV_INFO;

/**
 *@brief Basic information acquisition device.
 *This function is invoked ppsdev_open () call after the function, the device used to obtain basic information.
 *@param[in] hdev -Equipment session handle.
 *@param[out] devcaps -Equipment Basic information.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_get_info(int hdev, PPSDEV_INFO*devinfo);

/**
*@struct PPSDEV_SINGLE_ETH
*@brief A single network card device parameters structure
*/
typedef struct
{
	char	name[64];	/**<Card name, such as "eth0", read-only, setting meaningless*/
	int		dhcp;		/**<It is dhcp, 0 = no, 1 = yes*/
	int		wireless;	/**<Is wireless network (wifi), 0 = no, 1 = yes, read-only, set the meaningless*/
	char	ipv4[16];	/**<ipv4*/
	char	mask[16];	/**<Subnet Mask*/
	char	gate[16];	/**<Gateway*/
	char	dns1[16];	/**<Preferred dns*/
	char	dns2[16];	/**<Alternate dns*/
	char	ssid[64];	/**<ssid*/
	int		mode;		/**<0=Ad-hoc 1=Infrastructure 2=unknown*/
	int		secu_mode;	/**<0=None 1=WEP 2=PSK 3=Dot1X 4=unknown*/
	int		secu_algo;	/**<0=CCMP 1=TKIP 2=Any 3=unknown*/
	char	pass[64];	/**<password*/
}PPSDEV_SINGLE_ETH;

/**
*@struct　PPSDEV_NETWORK
*@brief　Device network parameters structure
*/
typedef struct
{
	int ethnum; /**<Card number available*/
	PPSDEV_SINGLE_ETH eth[4];/**<Single card parameters*/
}PPSDEV_NETWORK;

typedef struct
{
    unsigned char wifistatus;/**<0:disable 1:enable*/
	unsigned char wifilevel;/**<0-100*/
    unsigned char ltestatus;/**<*0:disbale 1:2G 2:3G 3:4G*/
	unsigned char ltelevel;/**<0-100*/
}NET_LINK_STATUS;

/**
 *@brief Get the device netlink status.
 *This function is invoked ppsdev_open () call after the function for Geting the device netlinkstatus.
 *@param[in] hdev -Equipment session handle.
 *@param[in] netlink -Device netlinkstatus.
 *@return 0- succeed <0 error code.
 */
PPSAPI int  CALLBACK pps_get_device_netlinkstatus(int hdev,NET_LINK_STATUS* netlink);

/**
 *@brief Get the device lte status.
 *This function is invoked ppsdev_open () call after the function for Geting the device netlinkstatus.
 *@param[in] hdev -Equipment session handle.
 *@return energy>=0, <0 error code.
 */
PPSAPI int  CALLBACK pps_get_device_battery_energy(int hdev);


typedef struct
{
    char ccid[PPS_MAX_CCID_LENGTH]; /**<ccid*/
    char imsi[PPS_MAX_IMSI_LENGTH]; /**<imsi*/
}PPSDEV_LTEINFO;

/**
 *@brief Get the device lteinfo.
 *This function is invoked ppsdev_open () call after the function for Geting the device netlinkstatus.
 *@param[in] hdev -Equipment session handle.
 *@return energy>=0, <0 error code.
 */
PPSAPI int  CALLBACK pps_get_device_lteinfo(int hdev,PPSDEV_LTEINFO* lteinfo);

/**
 *@brief Set the device wificfg.
 *This function is invoked ppsdev_open () call after the function for seting the device wifi.
 *@param[in] hdev -Equipment session handle.
 *@param[in] wificfg -Device wificfg.
 *@return 0- succeed <0 error code.
 */
PPSAPI int  CALLBACK pps_set_device_wificfg(int hdev,WIFI_CFG* wificfg);

/**
 *@brief Get the device wificfg.
 *This function is invoked ppsdev_open () call after the function for Geting the device wifi.
 *@param[in] hdev -Equipment session handle.
 *@param[in] wificfg -Device wificfg.
 *@return 0- succeed <0 error code.
 */
PPSAPI int  CALLBACK pps_get_device_wificfg(int hdev,WIFI_CFG* wificfg);

/**
 *@brief set the device 4g cfg.
 *This function is invoked ppsdev_open () call after the function for seting the device cfg.
 *@param[in] hdev -Equipment session handle.
 *@param[in] enable -1-enable 4g,0 disable 4g.
 *@return 0- succeed <0 error code.
 */
PPSAPI int  CALLBACK pps_set_device_ite(int hdev,int enable);

/**
 *@brief Set the device network parameters.
 *This function is invoked ppsdev_open () call after the function for setting the device network information.
 *@param[in] hdev -Equipment session handle.
 *@param[in] network -Device network parameters.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_set_network(int hdev, PPSDEV_NETWORK *network);

/**
 *@brief Get Device network parameters.
 *This function is invoked ppsdev_open () call after the function, the device used to obtain the network parameters.
 *@param[in] hdev -Equipment session handle.
 *@param[in] network -Device network parameters.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_get_network(int hdev, PPSDEV_NETWORK *network);

/**
*@struct PPSDEV_NTP
*@brief Equipment ntp parameter structure
*/
typedef struct
{
	int  enable;  /**<Whether to enable ntp 0: not enabled 1: Enabled*/
	char ntp[PPS_MAX_NTP_SERVER_LENGTH]; /**<ntp server*/
}PPSDEV_NTP;

/**
 *@brief Set the device ntp server.
 *This function is invoked ppsdev_open () call after the function for setting the device ntp server.
 *@param[in] hdev -Equipment session handle.
 *@param[in] ntp -ntp configuration.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_set_ntp(int hdev,PPSDEV_NTP* ntp);

/**
 *@brief Get device ntp server.
 *This function is invoked ppsdev_open () call after the function for acquiring equipment ntp server.
 *@param[in] hdev -Equipment session handle.
 *@param[out] ntp -ntp configuration.
 *@return 0- set successfully <0 error code.
 */
PPSAPI int CALLBACK ppsdev_get_ntp(int hdev,PPSDEV_NTP* ntp);

/**
 *@brief Set the device time zone configuration.
 *This function is invoked ppsdev_open () call after the function, the device used to set the time zone.
 *@param[in] hdev -Equipment session handle.
 *@param[in] size -Length of timezone.
 *@param[in] timezone -Time Zone Configuration.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_set_timezone(int hdev,char *timezone, int size);

PPSAPI int CALLBACK ppsdev_set_timezone_V2(char* ipaddr,char *timezone);

/**
 *@brief Get device Zone Configuration.
 *This function is invoked ppsdev_open () call after the function for acquiring equipment zone configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[out] size -Length of timezone.
 *@param[out] timezone -Time Zone Configuration.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_get_timezone(int hdev, char *timezone, int*size);

/**
 *@brief Restore the device to factory settings.
 *This function is invoked ppsdev_open () call after the function for the device to restore the factory settings.
 *@param[in] hdev -Equipment session handle.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_factory_reset(int hdev);

/**
 *@brief Device reboot.
 *This function is invoked ppsdev_open () call after the function for the device reboots.
 *@param[in] hdev -Equipment session handle.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_reboot(int hdev);

/**
 *@brief Equipment upgrades status callback.
 *@param[in] hdev -Equipment session handle.
 *@param[in] status - -1 means falied,>0 means updating,100 means update funish.
 *@return .
 */
typedef void (CALLBACK*updatecallback)(int status);

/**
 *@brief Equipment upgrades.
 *This function is invoked ppsdev_open () after the function call for equipment upgrades.
 *@param[in] hdev -Equipment session handle.
 *@param[in] data -Equipment upgrade package data.
 *@param[in] callback -updatecallback function.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_upgrade(int hdev, char *filename,updatecallback callback);

PPSAPI char* CALLBACK ppsdev_get_ipc_firmwareversion(int hdev);

PPSAPI int CALLBACK ppsdev_upgrade_V2(int hdev,char* upgradeurl,char* firmwareversion,updatecallback callback);

PPSAPI int CALLBACK ppsdev_upgrade_V2_stop(int hdev);

/**
 *@brief Set a device password.
 *This function is invoked ppsdev_open () call after the function for setting the device password.
 *@param[in] hdev -Equipment session handle.
 *@param[in] password -Equipment new password.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_set_password(int hdev, char *password);

/**
*@struct　PPSDEV_STORAGE_SINGAL_INFO
*@brief　Single hard disk information
*/
typedef struct
{
	unsigned char index;  /**<Hard index number*/
	unsigned char status; /**<0 =Unformatted 1=normal 2=Error*/
	unsigned char rw;     /**<Read-write mode, 1 = read only 2 = write only 3 = writeread*/
	unsigned char type;   /**<Hard disk storage interface Type 1 = 2 = SD / TF card 3 = flash 4 = Network Storage(NFS/NAS/iSCIS)*/
	int total_space;      /**<total volume,MB*/
	int free_space;       /**<Free space,MB*/
} PPSDEV_STORAGE_SINGAL_INFO;

/**
*@struct PPSDEV_STORAGE_INFO
*@brief All hard disk information
*/
typedef struct
{
	int count;                           /**<The total number of hard disk*/
	PPSDEV_STORAGE_SINGAL_INFO info[PPS_MAX_PPSDEV_STORAGE_SINGAL_INFO_NUMS];  /**<Single hard disk information*/
}PPSDEV_STORAGE_INFO;

/**
 *@brief Get all the hard disk information.
 *This function is invoked ppsdev_open () call after the function for acquiring all the hard disk information.
 *@param[in] hdev -Equipment session handle.
 *@param[in] storageinfo -Hard disk information structure.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_get_storage_info(int hdev, PPSDEV_STORAGE_INFO* storageinfo);

/**
 *@brief Formatting the hard drive status callback function.
 *@param[out] status:Percentage format0-100;-1 means failed.
 *@return.
 */
typedef void (CALLBACK*formatcallback)(int status);

/**
 *@brief Formatting the hard disk.
 *@param[in] hdev -Equipment session handle.
 *@param[in] index -Hard index number 0xff means the overall format.
 *@param[in] callback -Status callback function.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_storage_format(int hdev, unsigned char index,formatcallback callback);

/**
* @struct PPSDEV_FTP_CFG
* @brief FTP capture structure
*/
typedef struct
{
    unsigned int bValid;        /**<Whether ftp enabled*/
    unsigned int ipAddr;        /**<ftp server address*/
    unsigned int portNo;        /**<port*/
    unsigned char  usrname[PPS_MAX_USERNAME_LENGTH]; /**<ftp server name*/
    unsigned char  passwd[PPS_MAX_SHORT_PASSWORD_LENGTH];  /**<ftp server password*/
    unsigned int   dirLevel;    /**<0*/
    unsigned short topDirMode;  /**<0*/
    unsigned short subDirMode;  /**<0*/
    unsigned char  enableAnony; /**<Whether anony enable*/
    unsigned char  res[23];     /**<Reserved field*/
}PPSDEV_FTP_CFG;

/**
 * @brief Configuring ftp capture configuration
 * @param[in] hdev		Equipment session handle
 * @param[in] ftpcfg	FTP capture structure
 * @return  0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_ftp_setcfg(int hdev,int videoid,PPSDEV_FTP_CFG* ftpcfg);

/**
 * @brief Get ftp capture configuration
 * @param[in] hdev		Equipment session handle
 * @param[out] ftpcfg	FTP capture structure
 * @return  0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_ftp_getcfg(int hdev,int videoid,PPSDEV_FTP_CFG* ftpcfg);

/**
* @struct PPSDEV_DAYNIGHTPARA
* @brief The night of the handover parameters
*/
typedef struct
{
    unsigned char dayToNightFilterLevel; /**<0-5*/
    unsigned char nightToDayFilterLevel; /**<0-5*/
    unsigned char res[2];                /**<Reserved field*/
}PPSDEV_DAYNIGHTPARA;

/**
 * @brief Configuration night switching
 * @param[in] hdev		Equipment session handle
 * @param[int] daynight	The night of the handover parameters
 * @return  0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_day_night_setcfg(int hdev,int videoid,PPSDEV_DAYNIGHTPARA* daynight);

/**
 * @brief Get handover parameters night
 * @param[in] hdev		Equipment session handle
 * @param[out] ftpcfg	FTP capture structure
 * @return  0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_day_night_getcfg(int hdev,int videoid,PPSDEV_DAYNIGHTPARA* daynight);

typedef struct  
{
	int enable;   /**<0-disable 1-enable*/
    int sensitivity;/**<0-less 1-moderate 2-high 3-relatively high 4-highest*/
	int alarmtype;   /**<not used now*/
}ALARM_CFG;

/**
 * @brief Get alarm parameters
 * @param[in] hdev		Equipment session handle
 * @param[in] videoid	Video Source No.
 * @param[out] alarmcfg	Alarm structure.
 * @return  0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_alarm_getcfg(int hdev,int videoid,ALARM_CFG* alarmcfg);

/**
 * @brief Set alarm parameters
 * @param[in] hdev		Equipment session handle
 * @param[in] videoid	Video Source No.
 * @param[in] alarmcfg	Alarm structure.
 * @return  0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_alarm_setcfg(int hdev,int videoid,ALARM_CFG* alarmcfg);

/***************************************************************************************
 *@brief 7.after login devices,you can preview,ptz,playback and set videosource or audiosource.
 ***************************************************************************************/
/**
 *@brief PTZ control.
 *This function is invoked ppsdev_open () call after the function for PTZ control.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Video Source No.
 *@param[in] ps - panning speed (0 = not move negative left, positive right)-100~100.
 *@param[in] ts -Vertical movement speed (0 = not move,<0 vertically downward, >0 positive upward)-100~100.
 *@param[in] zs -Lens zooms speed (0 = not fixed, <0 negative pull away,>0 a time when closer)-100~100.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_ptz_move(int hdev, int videoid, int ps, int ts, int zs);

/**
 *@brief PTZ control is stopped.
 *This function is invoked ppsdev_open () call after the function for PTZ control stop.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Video Source No.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_ptz_stop(int hdev, int videoid);

#define SDK_SYSHEAD_DATA       (int)0  /**<Media head type*/
#define SDK_STREAM_DATA_VIDEO  (int)1  /**<Video data type*/
#define SDK_STREAM_DATA_AUDIO  (int)2  /**<Audio data types*/
#define SDK_STREAM_DATA_CLOSE  (int)3  /**<Close callback type*/
#define SDK_STREAM_DATA_SEEK   (int)4  /**<when you seek play,it will be called*/
#define SDK_STREAM_DATA_PAUSE  (int)5  /**<when you pause play,it will be called*/

/**
*@struct PPSDEV_MEDIA_HEADER
*@brief Device network parameters structure
*/
typedef struct 
{
	unsigned int   magic; /**<Media header: 0x56565099*/
	unsigned int   videoid; /**<Video Source No*/
	unsigned int   streamid; /**<Stream type: 0: The main stream 1: Sub-stream*/
	unsigned int media_format; /**<Media encoding format 0x01=H264 0x02=mpeg4 0x03=mjpeg 0x04=hevc 0x81=aac 0x82=g711u 0x83=g711a 0x84=g726_16 0x85=G726_32*/
	unsigned char frame_type; /**<0xF0- video frame type main frame 0xF1 = video fill the frame 0xF2 = pps 0xF3 = sps 0xFA = audio frame*/
	/**
	*@union PPSDEV_MEDIA_HEADER
	*@brief Device network parameters structure
	*/
	union{
		/**
		*@struct video
		*@brief Video parameter structure (If the media type is 0xf0 required when such data)
		*/
		struct{
			unsigned char frame_rate; /**<Frame rate*/
			unsigned char width; /**<Video width (a multiple of 8)*/
			unsigned char height; /**<Video High (a multiple of 8)*/
		}video;
		/**
		*@struct audio
		*@brief Audio parameters structure (If the media type is 0xfa required when such data)
		*/
		struct{
			unsigned char sample_rate; /**<Sampling Rate 0=8000 1=12000 2=11025 3=16000 4=22050 5=24000 6=32000 7=44100 8=48000*/
			unsigned char bit_rate; /**<Audio of bits*/
			unsigned char channels; /**<Number of channels*/
		}audio;
	};

	unsigned int timestamp; /**<Timestamp, millisecond*/
	unsigned int datetime; /**<Utc time the frame data, second grade*/
	unsigned int size; /**<The length of the frame data*/
}PPSDEV_MEDIA_HEADER,*PPSDEV_MEDIA_HEADER_PTR;

/**
 *@brief Stream callback.
 *This function is a stream callback.
 *@param[out] context -Call the class pointer.
 *@param[out] type -Callback data type.
 *@param[out] header -Stream head.
 *@param[out] buffer -Video stream or an audio stream.
 *@param[out] len -Length of the stream.
 *@return NULL.
 */
typedef void (CALLBACK * PPSDEV_MEDIA_CALLBACK)(void *context,int type,PPSDEV_MEDIA_HEADER_PTR header, char *buffer, int len);

/**
 *@struct PPSDEV_MEDIA_HEADER
 *@brief Device network parameters structure
 */
typedef struct
{
    unsigned int   magic; /**<Media header: 0x56565099*/
    unsigned int   videoid; /**<Video Source No*/
    unsigned int   streamid; /**<Stream type: 0: The main stream 1: Sub-stream*/
    unsigned int media_format; /**<Media encoding format 0x01=H264 0x02=mpeg4 0x03=mjpeg 0x04=hevc 0x81=aac 0x82=g711u 0x83=g711a 0x84=g726_16 0x85=G726_32*/
    unsigned char frame_type; /**<0xF0- video frame type main frame 0xF1 = video fill the frame 0xF2 = pps 0xF3 = sps 0xFA = audio frame*/
    /**
     *@union PPSDEV_MEDIA_HEADER
     *@brief Device network parameters structure
     */
    union{
        /**
         *@struct video
         *@brief Video parameter structure (If the media type is 0xf0 required when such data)
         */
        struct{
            unsigned char frame_rate; /**<Frame rate*/
            unsigned char width; /**<Video width (a multiple of 8)*/
            unsigned char height; /**<Video High (a multiple of 8)*/
        }video;
        /**
         *@struct audio
         *@brief Audio parameters structure (If the media type is 0xfa required when such data)
         */
        struct{
            unsigned char sample_rate; /**<Sampling Rate 0=8000 1=12000 2=11025 3=16000 4=22050 5=24000 6=32000 7=44100 8=48000*/
            unsigned char bit_rate; /**<Audio of bits*/
            unsigned char channels; /**<Number of channels*/
        }audio;
    };
#if defined(_WIN32)||defined(_WIN64)
	__int64 timestamp; /**<Timestamp, millisecond*/
#else
    int64_t timestamp; /**<Timestamp, millisecond*/
#endif
    unsigned int size; /**<The length of the frame data*/
}PPSDEV_MEDIA_HEADER_V2,*PPSDEV_MEDIA_HEADER_V2_PTR;

typedef void (CALLBACK * PPSDEV_MEDIA_CALLBACK_V2)(void *context,int type,PPSDEV_MEDIA_HEADER_V2_PTR header, char *buffer, int len);

/**
 *@brief Settings button callback.
 *This function is invoked ppsdev_open () call after the function for setting the stream callback.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Video Source No.
 *@param[in] callback -Callback function.
 *@param[in] context -Class pointer.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_media_set_callback(int hdev, int videoid,int streamid,PPSDEV_MEDIA_CALLBACK callback, void *context);

/**
 *@brief Open Preview.
 *This function is invoked ppsdev media_set callback () function called after.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Video Source No.
 *@param[in] streamtype -0- main stream 1- sub stream.
 *@param[in] linkmode -0-TCP 1-UDP.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_media_start_play(int hdev,int videoid,int streamid,int linkmode,int localport);

/**
 *@brief Stop preview.
 *This function is invoked ppsdev_media_start_play () after the function call for stopping Preview.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Video Source No.
 *@param[in] handle -value return by ppsdev_media_start_play.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_media_stop_play(int hdev,int videoid,int handle);

/**
 *@brief Grab Preview.(not support now)
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Video Source No.
 *@param[out] buffer -An image buffer address.
 *@param[out] len -An image size.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_media_snapshot(int hdev,int videoid,char *buffer, int *len);

/**
* @def DEFAULT_VALUE
* @brief  When used in a video or just want to set the parameters, set other parameters to 0x0, it indicates that a default is not set this parameter
*/
#define DEFAULT_VALUE    0x0 

/**
* @enum PPSDEV_VIDEOSOURCE_CODEC
* @brief Video encoding format
*/
typedef enum
{
	PPSDEV_VS_CODEC_H264 = 0x1,  /**<H264<*/
    PPSDEV_VS_CODEC_MPEG4 = 0x2  /**<MPEG4*/
} PPSDEV_VIDEOSOURCE_CODEC;

/**
* @enum PPSDEV_VIDEOSOURCE_RESOLUTION
* @brief Video resolution formats
*/
typedef enum 
{
	PPSDEV_VS_RES_1280_720 = 0x0, /**<720P*/
    PPSDEV_VS_RES_1280_960 = 0x1, /**<960P*/
    PPSDEV_VS_RES_640_480 = 0x2,  /**<480P*/
    PPSDEV_VS_RES_640_360 = 0x3,  /**<360P*/
    PPSDEV_VS_RES_1920_1080 = 0x4 /**<1080P*/
}PPSDEV_VIDEOSOURCE_RESOLUTION;

/**
* @enum PPSDEV_VIDEOSOURCE_BITRATE
* @brief Video bit rate format
*/
typedef enum 
{
	PPSDEV_VS_BR_32K  = 32,  /**<32K*/
	PPSDEV_VS_BR_128K = 128,  /**<128K*/
    PPSDEV_VS_BR_320K = 320,  /**<320K*/
	PPSDEV_VS_BR_512K = 512,  /**<512K*/
    PPSDEV_VS_BR_1M = 1024,    /**<1M*/
    PPSDEV_VS_BR_2M = 2048,   /**<2M*/
    PPSDEV_VS_BR_4M = 4096    /**<4M*/
}PPSDEV_VIDEOSOURCE_BITRATE;

/**
*@struct PPSDEV_VIDEOSOURCE_CONFIG
*@brief A single stream of video source device type configuration
*/
typedef struct
{
	int streamtype;                            /**<Stream Type 0- main stream 1- sub stream*/
	PPSDEV_VIDEOSOURCE_CODEC codec;			   /**<Video encoding format*/
	PPSDEV_VIDEOSOURCE_RESOLUTION resolution;  /**<Video resolution formats*/
	PPSDEV_VIDEOSOURCE_BITRATE bit_rate;       /**<Video bit rate format*/
	int frame_rate;                            /**<0-25*/
	int i_interval;                            /**<0-100*/
} PPSDEV_SINGLE_VIDEOSOURCE_CONFIG;

/**
*@struct PPSDEV_VIDEOSOURCE_CONFIG
*@brief A single stream of video source device type configuration
*/
typedef struct
{
    int confignum;                                   /**<The number of video source stream type configuration*/
 	PPSDEV_SINGLE_VIDEOSOURCE_CONFIG videoconfig[3]; /**<A single stream of video source device type configuration*/
}PPSDEV_VIDEOSOURCE_CONFIG;

/**
*@struct PPSDEV_VIDEOSOURCE_CAPS
*@brief Device video source capability
*/
typedef struct
{
	int codec_caps;         /**<PPSDEV_VIDEOSOURCE_CODEC,Stackable*/
	int resolution_caps;	/**<PPSDEV_VIDEOSOURCE_RESOLUTION*/
	int bitrate_caps;       /**<PPSDEV_VIDEOSOURCE_BITRATE*/
	int max_frame_rate;     /**<The maximum frame rate*/
	int max_i_interval;     /**<Maximum I-frame interval*/
} PPSDEV_VIDEOSOURCE_CAPS;

/**
 *@brief Get a video source device No. capacity.
 *This function is invoked ppsdev_open () call after the function, the device used to obtain a video source No. capability.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Equipment Source No.
 *@param[out] vscaps -Equipment source capability set.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_videosource_get_caps(int hdev, int videoid, PPSDEV_VIDEOSOURCE_CAPS *videocaps);

/**
 *@brief Set up a video source device number configuration.
 *This function is invoked ppsdev_open () call after the function for setting the device to a video source No. Configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Equipment frequency source No..
 *@param[in] videoconfig -Device video source configuration.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_videosource_setconfig(int hdev, int videoid, PPSDEV_VIDEOSOURCE_CONFIG *videoconfig);

/**
 *@brief Get a video source device number configuration.
 *This function is invoked ppsdev_open () call after the function for acquiring a video source device number configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[out] videoconfig -The current configuration of the video source device.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_videosource_getconfig(int hdev, int videoid, PPSDEV_VIDEOSOURCE_CONFIG *videoconfig);

/**
 *@brief Get bitrate.
 *This function is invoked ppsdev_open () call after the function for acquiring a video source device number configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[in] streamtype 0-main streamtype 1-sub streamtype 
 *@return >0-	PPSDEV_VS_BR_32K  = 0x0,
                PPSDEV_VS_BR_128K = 0x1,
                PPSDEV_VS_BR_512K = 0x2,
                PPSDEV_VS_BR_2M   = 0x4,
                PPSDEV_VS_BR_4M   = 0x8,
                <0 error code．
 */
PPSAPI int CALLBACK ppsdev_get_bitrate(int hdev,int videoid,int streamtype);

/**
 *@brief Get bitrate.
 *This function is invoked ppsdev_open () call after the function for acquiring a video source device number configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[in] streamtype 0-main streamtype 1-sub streamtype
 *@param[in] bitrate -PPSDEV_VIDEOSOURCE_BITRATE
 *@return =0 successed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_set_bitrate(int hdev,int videoid,int streamtype,PPSDEV_VIDEOSOURCE_BITRATE bitrate);

/**
 *@brief Get bitrate.
 *This function is invoked ppsdev_open () call after the function for acquiring a video source device number configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[in] streamtype 0-main streamtype 1-sub streamtype
 *@return >0-videoreate <0 error code.
 */
PPSAPI int CALLBACK ppsdev_get_framerate(int hdev,int videoid,int streamtype);

/**
 *@brief Get bitrate.
 *Thss function is invoked ppsdev_open () call after the function for acquiring a video source device number configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[in] streamtype 0-main streamtype 1-sub streamtype
 *@param[in] framerate - 1-25
 *@return >0- <0 error code.
 */
PPSAPI int CALLBACK ppsdev_set_framerate(int hdev,int videoid,int streamtype,int framerate);

/**
 *@brief Set up a mirror to a source channel.
 *This function is invoked ppsdev_open () call after the function for acquiring a video source device number configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[in] mirror -Set the default device images 0-default 1-up and down 2-left and right 3 up,down,left,right.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_videosource_setmirror(int hdev, int videoid, int mirror);

/**
 *@brief Get up a mirror to a source channel.
 *This function is invoked ppsdev_open () call after the function for acquiring a video source device number configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@return >=0 mirror 0-default 1-up and down 2-left and right 3 up,down,left,right. <0 error code.
 */
PPSAPI int CALLBACK ppsdev_videosource_getmirror(int hdev, int videoid);

/**
* @enum PPSDEV_AUDIOSOURCE_CODEC
* @brief Audio encoding format
*/
typedef enum
{
	PPSDEV_VS_CODEC_G711 = 0x1,  /**<G711*/
	PPSDEV_VS_CODEC_G726 = 0x2,  /**<G726*/
	PPSDEV_VS_CODEC_AAC = 0x4,   /**<ACC*/
} PPSDEV_AUDIOSOURCE_CODEC;

/**
* @struct PPSDEV_AUDIOSOURCE_CONFIG
* @brief Device Audio Source Configuration
*/
typedef struct
{
	PPSDEV_AUDIOSOURCE_CODEC codec;		/**<PPSDEV_AUDIOSOURCE_CODEC*/
	int sample_rate;	                /**<Sampling Rate bps*/
	int bit_rate;		                /**<Bit rate,bit*/
	int channles;		                /**<Number of channels*/
} PPSDEV_AUDIOSOURCE_CONFIG;

/**
* @struct PPSDEV_AUDIOSOURCE_CAPS
* @brief Equipment audio source capability
*/
typedef struct
{
	int codec_caps;            /**<PPSDEV_AUDIOSOURCE_CAPS*/
	int max_sample_rate;	   /**<Sampling Rate bps*/
	int max_bit_rate;		   /**<Bit rate,bit*/
	int max_channles;		   /**<Number of channels*/
} PPSDEV_AUDIOSOURCE_CAPS;

/**
 *@brief Get an audio source device to a number of capacity.
 *This function is invoked ppsdev_open () after the function call, the audio source is used to obtain equipment in a number of capacity.
 *@param[in] hdev -Equipment session handle.
 *@param[in] audioid -No audio source device.
 *@param[out] audiocaps -Equipment audio source capability set.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_audiosource_get_caps(int hdev, int audioid, PPSDEV_AUDIOSOURCE_CAPS *audiocaps);

/**
 *@brief Set the device to configure a number of audio sources.
 *This function is invoked ppsdev_open () call after the function for setting the device to configure a number of audio sources.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[in] videoconfig -Equipment Source Configuration.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_audiosource_setconfig(int hdev, int audioid, PPSDEV_AUDIOSOURCE_CONFIG *audioconfig);

/**
 *@brief Get an audio source device to a number of configuration.
 *This function is invoked ppsdev_open () call after the function for acquiring a video source device number configuration.
 *@param[in] hdev -Equipment session handle.
 *@param[in] audioid -No audio source device.
 *@param[out] audioconfig -Device Audio Source Configuration.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_audiosource_getconfig(int hdev, int audioid, PPSDEV_AUDIOSOURCE_CONFIG *audioconfig);

/**
 *@brief No recording a video source device.
 *This function is invoked ppsdev_open () after the function call, a device for recording a video source number.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No..
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_record_start(int hdev, int videoid);

/**
 *@brief Equipment to stop recording a video source number.
 *This function is invoked ppsdev_open () call after the function for the device to stop recording a video source number.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_record_stop(int hdev, int videoid);

/**
 * @struct PPSDEV_RECORD_SINGLE_SCHEDULE
 * @brief Equipment single video program structure
 */
typedef struct
{
	int  rec_type;             /**<Record Type Value*/
	char single_schedule[32];  /**<In the following format "DDHHMM" DD represents 10 20 30 ... 70 HH represents 00-23 MM represents 00-59*/
}PPSDEV_RECORD_SINGLE_SCHEDULE;

/**
 * @struct PPSDEV_RECORD_SCHEDULE
 * @brief Recording equipment program structure
 */
typedef struct
{
	int videoid;                                /**<Video Source No*/
	int schedule_num;                           /**<The number of video program*/
	PPSDEV_RECORD_SINGLE_SCHEDULE schedule[56]; /**<Recording Program*/
}PPSDEV_RECORD_SCHEDULE;

/**
 *@brief No recording a video source device program.
 *This function is invoked ppsdev_open () call after the function for the device to stop recording a video source number.
 *@param[in] hdev     -Equipment session handle.
 *@param[in] videoid  -Device video source No..
 *@param[in] schedule -Recording equipment program structure.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_record_set_schedule(int hdev, int videoid, PPSDEV_RECORD_SCHEDULE *schedule);

/**
 *@brief Get a video source device number recording plan.
 *This function is invoked ppsdev_open () call after the function for the device to stop recording a video source number.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No..
 *@param[out] schedule -Recording equipment program structure.
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_record_get_schedule(int hdev, int videoid, PPSDEV_RECORD_SCHEDULE *schedule);

/**
 * @brief Trigger a recording tasks(not support now)
 * @param[in] hdev		    Equipment session handle
 * @param[in] videoid       Device video source No.
 * @param[in] rec_type		Record Type 1 = 2 = alarm recording timer recording
 * @param[in] rec_secs		Required length recording (in seconds)
 * @return 0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_record_start_recording(int hdev, int videoid, int rec_type, int rec_secs);

/**
* @struct RECORD_DAY_LIST
* @brief Search by return day record list
*/
typedef struct
{
	int  recordnum;           /**<There Recording Days*/
	char recordlist[100][30]; /**<Number of seconds to return search list similar "HHMMSS-HHMMSS"*/
}RECORD_DAY_LIST;

/**
* @struct RECORD_MONTH_LIST
* @brief Back video list on a monthly basis
*/
typedef struct
{
	int recordnum;      /**<There Recording Days*/
	int recordlist[31]; /**<Back to search results month, 0 month 1- month there is no video recording*/
}RECORD_MONTH_LIST;

/**
* @struct RECORD_DAY_SEARCH
* @brief Search the structure by day
*/
typedef struct
{
	int year;  /**<After Year 1990*/
	int month; /**<1-12*/
	int day;   /**<1-31*/
}RECORD_DAY_SEARCH;

/**
* @struct RECORD_MONTH_SEARCH
* @brief Monthly search structure
*/
typedef struct
{
	int year;  /**<After Year 1990*/
	int month; /**<1-12*/
}RECORD_MONTH_SEARCH;

/**
 *@brief What day of the monthly return on video.
 *This function is invoked ppsdev_open () call after the function for the device to stop recording a video source number.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[in] rec_type -Recording type (0: All, 1: time recording, 2: Alarm Recording).
 *@param[int] monthsearch	-Monthly search structure
 *@param[out] daylist	-Back video list on a monthly basis
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_record_search_by_month(int hdev, int videoid, int rec_type,RECORD_MONTH_SEARCH*monthsearch,RECORD_MONTH_LIST*daylist);

/**
 *@brief What day of the monthly return on video.
 *This function is invoked ppsdev_open () call after the function for the device to stop recording a video source number.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Device video source No.
 *@param[in] rec_type -Recording type (0: All, 1: time recording, 2: Alarm Recording).
 *@param[int] daysearch	-Search the structure by day
 *@param[out] daylist	-Search by return day record list
 *@return 0- succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_record_search_by_day(int hdev, int videoid, int rec_type,RECORD_DAY_SEARCH*daysearch,RECORD_DAY_LIST*daylist);

/**
* @brief Returns the number of days a recording file
* @param[in] hdev			Equipment session handle
* @param[in] chl_id			>=0
* @param[in] start_time		YYYYMMDDHHNNSS
* @param[in] time_zone	    timezone
* @return  0- succeed <0 error code.
*/
PPSAPI int CALLBACK ppsdev_record_replay_by_time(int hdev,int hreplay,int videoid, char *start_time, int time_zone);

/**
 *@brief Set playback stream callback.
 *This function is invoked ppsdev_open () call after the function for setting the stream callback.
 *@param[in] hdev -Equipment session handle.
 *@param[in] videoid -Video Source No.
 *@param[in] callback -Callback function.
 *@param[in] context -user pointer.
 *@return hreplay >0-succeed <0 error code.
 */
PPSAPI int CALLBACK ppsdev_record_replay_set_callback(int hdev,PPSDEV_MEDIA_CALLBACK callback, void *context);

/**
 * @brief Stop playback
 * @param[in] hdev		Equipment session handle
 * @param[in] hreplay	Playback handle
 * @return 0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_record_stop_replay(int hdev, int hreplay);

/**
 * @brief Playback control(not support now)
 * @param[in] hdev		    Equipment session handle
 * @param[in] hreplay		Playback handle
 * @param[in] cmd			Control command 1=Normal Playback 2=pause 3=Stepping 4=Jog 5=Fast Forward 6=Rewind.
 * @param[in] cmd_param		Command parameters (slow forward, fast forward, rewind speed when.
 * @return 0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_record_replay_control(int hdev, int hreplay, int cmd, int cmd_param);

/**
 * @struct PPSDEV_VOICE_PARAMS
 * @brief Talkback parameter structure
 */
typedef struct
{
    int codec;					/**<Audio encoding type default 1*/
    int samplerate; 			/**<Sampling Rate,default 8000*/
    int bitrate;				/**<Bit rate,default 16*/
    int channels;				/**<Number of channels,default 1*/
    int buffsize;				/**<Audio sample length (after encoding),default 320,G711 format*/
}PPSDEV_VOICE_PARAMS;

/**
 * @brief Set voice intercom callback
 * @param[in]  hdev		    Equipment session handle
 * @param[out] callback		Equipment flow callback
 * @return 0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_set_voicetalk_callback(int hdev,int videoid,PPSDEV_MEDIA_CALLBACK callback,void *context);

/**
 * @brief      Talkback open process
 * @param[in] hdev		Equipment session handle
 * @param[in] videoid	Video source number (starting with 0)
 * @param[in] params	Talkback parameter structure
 * @return  >0 succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_voicetalk_open(int hdev, int videoid, PPSDEV_VOICE_PARAMS *params);

/**
 * @brief Talkback open process
 * @param[in] hdev		Equipment session handle
 * @param[in] hvoice	Talkback handle
 * @return 0- succeed <0 error code
 */
 PPSAPI int CALLBACK ppsdev_voicetalk_close(int hdev, int hvoice);

/**
 * @brief Write device-side audio (client -> device) default only support u_G711
 * @param[in] hdev		    Equipment session handle
 * @param[in] hvoice		Talkback handle
 * @param[in] buffer		Audio data buffer
 * @param[in] size			The size of the incoming audio data
 * @return 0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_voicetalk_write(int hdev, int hvoice, char *buffer, int size);

/***************************************************************************************
 *@brief 8.after pps_init(),you can playback videos on cloud.
 ***************************************************************************************/
/**
 * @brief start playback videos on cloud
 * @param[in] url		    url of hls
 * @param[in] callback		callback streams
 * @param[in] userData		Datas of user
 * @return 0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_start_live(char* url,PPSDEV_MEDIA_CALLBACK_V2 callback,void* userData);

/**
 * @brief stop playback videos on cloud
 * @return 0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_stop_live();

/**
 * @brief seek when playback videos on cloud
 * @param[in] frac		    (0-1) precent of duration
 * @return 0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_seek_live(double frac);

/**
 * @brief duration of videos
 * @return >=0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_get_duration();

/**
 * @brief pause playback on cloud
 * @return >=0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_pause_live();

/**
 * @brief continue playback on cloud
 * @return >=0- succeed <0 error code
 */
PPSAPI int CALLBACK ppsdev_contine_live();

/*
 *@brief common sdk Api
 */
#if (PPS_CURRENT_VERSION&PPS_VERSION_1_2)
typedef void (CALLBACK *SUCCESS_CALLBACK)(char* success_json_data);

typedef void (CALLBACK *FAILURE_CALLBACK)(char* failure_json_data);

typedef enum {
    PPS_INIT_TYPE,
    PPS_FREE_TYPE,
    PPS_SET_DEVICE_WIFI_TYPE,
    PPS_SET_DEVICE_WIFI_STOP_TYPE,
    PPS_SET_AP_DEVICE_WIFICFG_TYPE,
    PPS_SEARCH_DEVICE_TYPE,
    PPS_STOP_SEARCH_DEVICE_TYPE,
    PPS_GET_SUPPORT_P2P_TYPE,
    PPS_TRYCONNECT_TUTK_TYPE,
    PPS_CANCELCONNECT_TUTK_TYPE,
    PPS_P2P_NAT_TYPE,
    PPS_OPEN_TYPE,
    PPS_STOP_OPEN_TYPE,
    PPS_CLOSE_TYPE,
    PPS_GET_CAPS_TYPE,
    PPS_GET_INFO_TYPE,
    PPS_GET_DEVICE_NETLINKSTATUS_TYPE,
    PPS_GET_DEVICE_BATTERY_ENERGY_TYPE,
    PPS_GET_DEVICE_LTEINFO_TYPE,
    PPS_SET_DEVICE_WIFICFG_TYPE,
    PPS_GET_DEVICE_WIFICFG_TYPE,
    PPS_SET_DEVICE_ITE_TYPE,
    PPS_SET_NETWORK_TYPE,
    PPS_GET_NETWORK_TYPE,
    PPS_SET_NTP_TYPE,
    PPS_GET_NTP_TYPE,
    PPS_SET_TIMEZONE_TYPE,
    PPS_SET_TIMEZONE_V2_TYPE,
    PPS_GET_TIMEZONE_TYPE,
    PPS_FACTORY_RESET_TYPE,
    PPS_REBOOT_TYPE,
    PPS_UPGRADE_TYPE,
    PPS_GET_IPC_FIRMWAREVERSION_TYPE,
    PPS_UPGRADE_V2_TYPE,
    PPS_UPGRADE_V2_STOP_TYPE,
    PPS_SET_PASSWORD_TYPE,
    PPS_GET_STORAGE_INFO_TYPE,
    PPS_STORAGE_FORMAT_TYPE,
    PPS_FTP_SETCFG_TYPE,
    PPS_FTP_GETCFG_TYPE,
    PPS_DAY_NIGHT_SETCFG_TYPE,
    PPS_DAY_NIGHT_GETCFG_TYPE,
    PPS_ALARM_GETCFG_TYPE,
    PPS_ALARM_SETCFG_TYPE,
    PPS_PTZ_MOVE_TYPE,
    PPS_PTZ_STOP_TYPE,
    PPS_MEDIA_SET_CALLBACK_TYPE,
    PPS_MEDIA_START_PLAY_TYPE,
    PPS_MEDIA_STOP_PLAY_TYPE,
    PPS_MEDIA_SNAPSHOT_TYPE,
    PPS_VIDEOSOURCE_GET_CAPS_TYPE,
    PPS_VIDEOSOURCE_SETCONFIG_TYPE,
    PPS_VIDEOSOURCE_GETCONFIG_TYPE,
    PPS_GET_BITRATE_TYPE,
    PPS_SET_BITRATE_TYPE,
    PPS_GET_FRAMERATE_TYPE,
    PPS_SET_FRAMERATE_TYPE,
    PPS_VIDEOSOURCE_SETMIRROR_TYPE,
    PPS_VIDEOSOURCE_GETMIRROR_TYPE,
    PPS_AUDIOSOURCE_GET_CAPS_TYPE,
    PPS_AUDIOSOURCE_SETCONFIG_TYPE,
    PPS_AUDIOSOURCE_GETCONFIG_TYPE,
    PPS_RECORD_START_TYPE,
    PPS_RECORD_STOP_TYPE,
    PPS_RECORD_SET_SCHEDULE_TYPE,
    PPS_RECORD_GET_SCHEDULE_TYPE,
    PPS_RECORD_START_RECORDING_TYPE,
    PPS_RECORD_SEARCH_BY_MONTH_TYPE,
    PPS_RECORD_SEARCH_BY_DAY_TYPE,
    PPS_RECORD_REPLAY_BY_TIME_TYPE,
    PPS_RECORD_REPLAY_SET_CALLBACK_TYPE,
    PPS_RECORD_STOP_REPLAY_TYPE,
    PPS_RECOED_REPLAY_CONCTROL_TYPE,
    PPS_SET_VIOCETALK_CALLBACK_TYPE,
    PPS_VOICETALK_OPEN_TYPE,
    PPS_VOICETALK_CLOSE_TYPE,
    PPS_VOICETALK_WRITE_TYPE,
    PPS_START_LIVE_TYPE,
    PPS_STOP_LIVE_TYPE,
    PPS_SEEK_LIVE_TYPE,
    PPS_GET_DURATION_TYPE,
    PPS_PAUSE_LIVE_TYPE,
    PPS_CONTINUE_LIVE_TYPE,
    PPS_MAX_TYPE
}PPS_TYPE;

typedef struct
{
    const char* apiname;
    void* function;
    PPS_TYPE type;
    char* version;
}PPSDEV_REQUEST_API;

static PPSDEV_REQUEST_API pps_request_api[]={
    {"pps.init",(void*)pps_init,PPS_INIT_TYPE,"1.2"},
    {"pps.free",(void*)pps_free,PPS_FREE_TYPE,"1.2"},
    {"pps.set.device.wifi",(void*)pps_set_device_wifi,PPS_SET_DEVICE_WIFI_TYPE,"1.2"},
    {"pps.set.device.wifi.stop",(void*)pps_set_device_wifi_stop,PPS_SET_DEVICE_WIFI_STOP_TYPE,"1.2"},
    {"pps.set.AP.device.wificfg",(void*)pps_set_AP_device_wificfg,PPS_SET_AP_DEVICE_WIFICFG_TYPE,"1.2"},
    {"pps.search.device",(void*)pps_search_device,PPS_SEARCH_DEVICE_TYPE,"1.2"},
    {"pps.stop.search.device",(void*)pps_stop_search_device,PPS_STOP_SEARCH_DEVICE_TYPE,"1.2"},
    {"pps.get.support.p2p.type",(void*)pps_get_support_p2p_type,PPS_GET_SUPPORT_P2P_TYPE,"1.2"},
    {"ppsdev.tryconnect.tutk",(void*)ppsdev_tryconnect_tutk,PPS_TRYCONNECT_TUTK_TYPE,"1.2"},
    {"ppsdev.cancelconnect.tutk",(void*)ppsdev_cancelconnect_tutk,PPS_CANCELCONNECT_TUTK_TYPE,"1.2"},
    {"ppsdev.p2p.nat.type",(void*)ppsdev_p2p_nat_type,PPS_P2P_NAT_TYPE,"1.2"},
    {"ppsdev.open",(void*)ppsdev_open,PPS_OPEN_TYPE,"1.2"},
    {"ppsdev.stop.open",(void*)ppsdev_stop_open,PPS_STOP_OPEN_TYPE,"1.2"},
    {"ppsdev.close",(void*)ppsdev_close,PPS_CLOSE_TYPE,"1.2"},
    {"ppsdev.get.caps",(void*)ppsdev_get_caps,PPS_GET_CAPS_TYPE,"1.2"},
    {"ppsdev.get.info",(void*)ppsdev_get_info,PPS_GET_INFO_TYPE,"1.2"},
    {"pps.get.device.netlinkstatus",(void*)pps_get_device_netlinkstatus,PPS_GET_DEVICE_NETLINKSTATUS_TYPE,"1.2"},
    {"pps.get.device.battery.energy",(void*)pps_get_device_battery_energy,PPS_GET_DEVICE_BATTERY_ENERGY_TYPE,"1.2"},
    {"pps.get.device.lteinfo",(void*)pps_get_device_lteinfo,PPS_GET_DEVICE_LTEINFO_TYPE,"1.2"},
    {"pps.set.device.wificfg",(void*)pps_set_device_wificfg,PPS_SET_DEVICE_WIFICFG_TYPE,"1.2"},
    {"pps.get.device.wificfg",(void*)pps_get_device_wificfg,PPS_GET_DEVICE_WIFICFG_TYPE,"1.2"},
    {"pps.set.device.ite",(void*)pps_set_device_ite,PPS_SET_DEVICE_ITE_TYPE,"1.2"},
    {"ppsdev.set.network",(void*)ppsdev_set_network,PPS_SET_NETWORK_TYPE,"1.2"},
    {"ppsdev.get.network",(void*)ppsdev_get_network,PPS_GET_NETWORK_TYPE,"1.2"},
    {"ppsdev.set.ntp",(void*)ppsdev_set_ntp,PPS_SET_NTP_TYPE,"1.2"},
    {"ppsdev.get.ntp",(void*)ppsdev_get_ntp,PPS_GET_NTP_TYPE,"1.2"},
    {"ppsdev.set.timezone",(void*)ppsdev_set_timezone,PPS_SET_TIMEZONE_TYPE,"1.2"},
    {"ppsdev.set.timezone.V2",(void*)ppsdev_set_timezone_V2,PPS_SET_TIMEZONE_V2_TYPE,"1.2"},
    {"ppsdev.get.timezone",(void*)ppsdev_get_timezone,PPS_GET_TIMEZONE_TYPE,"1.2"},
    {"ppsdev.factory.reset",(void*)ppsdev_factory_reset,PPS_FACTORY_RESET_TYPE,"1.2"},
    {"ppsdev.reboot",(void*)ppsdev_reboot,PPS_REBOOT_TYPE,"1.2"},
    {"ppsdev.upgrade",(void*)ppsdev_upgrade,PPS_UPGRADE_TYPE,"1.2"},
    {"ppsdev.get.ipc.firmwareversion",(void*)ppsdev_get_ipc_firmwareversion,PPS_GET_IPC_FIRMWAREVERSION_TYPE,"1.2"},
    {"ppsdev.upgrade.V2",(void*)ppsdev_upgrade_V2,PPS_UPGRADE_V2_TYPE,"1.2"},
    {"ppsdev.upgrade.V2.stop",(void*)ppsdev_upgrade_V2_stop,PPS_UPGRADE_V2_STOP_TYPE,"1.2"},
    {"ppsdev.set.password",(void*)ppsdev_set_password,PPS_SET_PASSWORD_TYPE,"1.2"},
    {"ppsdev.get.storage.info",(void*)ppsdev_get_storage_info,PPS_GET_STORAGE_INFO_TYPE,"1.2"},
    {"ppsdev.storage.format",(void*)ppsdev_storage_format,PPS_STORAGE_FORMAT_TYPE,"1.2"},
    {"ppsdev.ftp.setcfg",(void*)ppsdev_ftp_setcfg,PPS_FTP_SETCFG_TYPE,"1.2"},
    {"ppsdev.ftp.getcfg",(void*)ppsdev_ftp_getcfg,PPS_FTP_GETCFG_TYPE,"1.2"},
    {"ppsdev.day.night.setcfg",(void*)ppsdev_day_night_setcfg,PPS_DAY_NIGHT_SETCFG_TYPE,"1.2"},
    {"ppsdev.day.night.getcfg",(void*)ppsdev_day_night_getcfg,PPS_DAY_NIGHT_GETCFG_TYPE,"1.2"},
    {"ppsdev.alarm.getcfg",(void*)ppsdev_alarm_getcfg,PPS_ALARM_GETCFG_TYPE,"1.2"},
    {"ppsdev.alarm.setcfg",(void*)ppsdev_alarm_setcfg,PPS_ALARM_SETCFG_TYPE,"1.2"},
    {"ppsdev.ptz.move",(void*)ppsdev_ptz_move,PPS_PTZ_MOVE_TYPE,"1.2"},
    {"ppsdev.ptz.stop",(void*)ppsdev_ptz_stop,PPS_PTZ_STOP_TYPE,"1.2"},
    {"ppsdev.media.set.callback",(void*)ppsdev_media_set_callback,PPS_MEDIA_SET_CALLBACK_TYPE,"1.2"},
    {"ppsdev.media.start.play",(void*)ppsdev_media_start_play,PPS_MEDIA_START_PLAY_TYPE,"1.2"},
    {"ppsdev.media.stop.play",(void*)ppsdev_media_stop_play,PPS_MEDIA_STOP_PLAY_TYPE,"1.2"},
    {"ppsdev.media.snapshot",(void*)ppsdev_media_snapshot,PPS_MEDIA_SNAPSHOT_TYPE,"1.2"},
    {"ppsdev.videosource.get.caps",(void*)ppsdev_videosource_get_caps,PPS_VIDEOSOURCE_GET_CAPS_TYPE,"1.2"},
    {"ppsdev.videosource.setconfig",(void*)ppsdev_videosource_setconfig,PPS_VIDEOSOURCE_SETCONFIG_TYPE,"1.2"},
    {"ppsdev.videosource.getconfig",(void*)ppsdev_videosource_getconfig,PPS_VIDEOSOURCE_GETCONFIG_TYPE,"1.2"},
    {"ppsdev.get.bitrate",(void*)ppsdev_get_bitrate,PPS_GET_BITRATE_TYPE,"1.2"},
    {"ppsdev.set.bitrate",(void*)ppsdev_set_bitrate,PPS_SET_BITRATE_TYPE,"1.2"},
    {"ppsdev.get.framerate",(void*)ppsdev_get_framerate,PPS_GET_FRAMERATE_TYPE,"1.2"},
    {"ppsdev.set.framerate",(void*)ppsdev_set_framerate,PPS_SET_FRAMERATE_TYPE,"1.2"},
    {"ppsdev.videosource.setmirror",(void*)ppsdev_videosource_setmirror,PPS_VIDEOSOURCE_SETMIRROR_TYPE,"1.2"},
    {"ppsdev.videosource.getmirror",(void*)ppsdev_videosource_getmirror,PPS_VIDEOSOURCE_GETMIRROR_TYPE,"1.2"},
    {"ppsdev.audiosource.get.caps",(void*)ppsdev_audiosource_get_caps,PPS_AUDIOSOURCE_GET_CAPS_TYPE,"1.2"},
    {"ppsdev.audiosource.setconfig",(void*)ppsdev_audiosource_setconfig,PPS_AUDIOSOURCE_SETCONFIG_TYPE,"1.2"},
    {"ppsdev.audiosource.getconfig",(void*)ppsdev_audiosource_getconfig,PPS_AUDIOSOURCE_GETCONFIG_TYPE,"1.2"},
    {"ppsdev.record.start",(void*)ppsdev_record_start,PPS_RECORD_START_TYPE,"1.2"},
    {"ppsdev.record.stop",(void*)ppsdev_record_stop,PPS_RECORD_STOP_TYPE,"1.2"},
    {"ppsdev.record.set.schedule",(void*)ppsdev_record_set_schedule,PPS_RECORD_SET_SCHEDULE_TYPE,"1.2"},
    {"ppsdev.record.get.schedule",(void*)ppsdev_record_get_schedule,PPS_RECORD_GET_SCHEDULE_TYPE,"1.2"},
    {"ppsdev.record.start.recording",(void*)ppsdev_record_start_recording,PPS_RECORD_START_RECORDING_TYPE,"1.2"},
    {"ppsdev.record.search.by.month",(void*)ppsdev_record_search_by_month,PPS_RECORD_SEARCH_BY_MONTH_TYPE,"1.2"},
    {"ppsdev.record.search.by.day",(void*)ppsdev_record_search_by_day,PPS_RECORD_SEARCH_BY_DAY_TYPE,"1.2"},
    {"ppsdev.record.replay.by.time",(void*)ppsdev_record_replay_by_time,PPS_RECORD_REPLAY_BY_TIME_TYPE,"1.2"},
    {"ppsdev.record.replay.set.callback",(void*)ppsdev_record_replay_set_callback,PPS_RECORD_REPLAY_SET_CALLBACK_TYPE,"1.2"},
    {"ppsdev.record.stop.replay",(void*)ppsdev_record_stop_replay,PPS_RECORD_STOP_REPLAY_TYPE,"1.2"},
    {"ppsdev.record.replay.control",(void*)ppsdev_record_replay_control,PPS_RECOED_REPLAY_CONCTROL_TYPE,"1.2"},
    {"ppsdev.set.voicetalk.callback",(void*)ppsdev_set_voicetalk_callback,PPS_SET_VIOCETALK_CALLBACK_TYPE,"1.2"},
    {"ppsdev.voicetalk.open",(void*)ppsdev_voicetalk_open,PPS_VOICETALK_OPEN_TYPE,"1.2"},
    {"ppsdev.voicetalk.close",(void*)ppsdev_voicetalk_close,PPS_VOICETALK_CLOSE_TYPE,"1.2"},
    {"ppsdev.voicetalk.write",(void*)ppsdev_voicetalk_write,PPS_VOICETALK_WRITE_TYPE,"1.2"},
    {"ppsdev.start.live",(void*)ppsdev_start_live,PPS_START_LIVE_TYPE,"1.2"},
    {"ppsdev.stop.live",(void*)ppsdev_stop_live,PPS_STOP_LIVE_TYPE,"1.2"},
    {"ppsdev.seek.live",(void*)ppsdev_seek_live,PPS_SEEK_LIVE_TYPE,"1.2"},
    {"ppsdev.get.duration",(void*)ppsdev_get_duration,PPS_GET_DURATION_TYPE,"1.2"},
    {"ppsdev.pause.live",(void*)ppsdev_pause_live,PPS_PAUSE_LIVE_TYPE,"1.2"},
    {"ppsdev.contine.live",(void*)ppsdev_contine_live,PPS_CONTINUE_LIVE_TYPE,"1.2"}
};

PPSAPI void requestWithApiName(char* apiname,char* postData,char* version,SUCCESS_CALLBACK success,FAILURE_CALLBACK failure,void* userData);
#endif

#endif








