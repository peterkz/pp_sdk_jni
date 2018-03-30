#include <string.h>
#include <jni.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */
#include <stdio.h>
 #include <stdlib.h>
#include "ppsdk.h"
#include <android/log.h>
#include <unistd.h>
#define LOGI(...) __android_log_print(4   , "ppstrong", __VA_ARGS__)
#include <pthread.h>
long handleMain = 0;

long handleVoice = 0;
long hvoice = 0;
/*
此函数用于把设备注册成为一个wifi热点
**/
jint Java_com_wetoop_camera_CameraJni_setApwifi(JNIEnv* env,jobject thiz, jstring wifi,jstring password,jint type){
	long handle = 0;
    long bfirst =0;
    jint ret=1;

    pps_init();
	WIFI_CFG wificfg = {0};
	//const修饰的数据类型是指常类型，常类型的变量或对象的值是不能被更新的
	const char* wifi_char = (*env)->GetStringUTFChars(env,wifi,0);
	const char* password_char = (*env)->GetStringUTFChars(env,password,NULL);
	/*const char* devip_char = (*env)->GetStringUTFChars(env,devip,NULL);
	const char* adminName_char = (*env)->GetStringUTFChars(env,adminName,NULL);
	const char* adminPwd_char = (*env)->GetStringUTFChars(env,adminPwd,NULL);*/
	
	strncpy(wificfg.SSID,wifi_char,32);
	strncpy(wificfg.password,password_char,32);
	wificfg.KEY_WPA_TYPE = type;//可以直接更改为数字
	//wificfg.KEY_WPA_TYPE = 4;
    (*env)->ReleaseStringUTFChars(env,wifi,wifi_char);
    (*env)->ReleaseStringUTFChars(env,password,password_char);
	// (*env)->ReleaseStringUTFChars(env,devip,devip_char);
	ret = pps_set_AP_device_wificfg(&wificfg);//@return 0- succeed <0 error code.
	/*if(!bfirst)
	{ 
		pps_init();
		PPSDEV_LOGIN_INFO loginInfo = {0};
		//memcpy()是内存拷贝函数，从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
		//储存登陆信息
		strncpy(loginInfo.devip,"192.168.0.1",32);
		strncpy(loginInfo.username,"admin",32);
		strncpy(loginInfo.password,"admin",32);
		loginInfo.localport = 80;
		handle = ppsdev_open(loginInfo);
		bfirst = 1;
	}

    if(handle>0){
         ret = pps_set_device_wificfg(handle,&wificfg);//@return 0- succeed <0 error code.
    }*/
	
	return ret;
}
jint Java_com_wetoop_camera_CameraJni_setApwifiWay(JNIEnv* env,jobject thiz, jstring wifi,jstring password,jint type){
	long handle = 0;
    long bfirst =0;
    jint ret=1;
  //const修饰的数据类型是指常类型，常类型的变量或对象的值是不能被更新的
  const char* wifi_char = (*env)->GetStringUTFChars(env,wifi,0);
  const char* password_char = (*env)->GetStringUTFChars(env,password,NULL);
  

  if(!bfirst)
  {
    pps_init();
    /*WIFI_INFO wifiInfo = {0};

    strncpy(wifiInfo.SSID,wifi_char,32);
      strncpy(wifiInfo.password,password_char,32);
      strncpy(wifiInfo.name,"",32);
      strncpy(wifiInfo.passwd,"",32);
      
      wifiInfo.KEY_WPA_TYPE = 4;//可以直接更改为数字

      (*env)->ReleaseStringUTFChars(env,wifi,wifi_char);
      (*env)->ReleaseStringUTFChars(env,password,password_char);
      
      ret = pps_set_device_wifi(&wifiInfo);//@return 0- succeed <0 error code.*/
    WIFI_CFG wifiInfo = {0};

    strncpy(wifiInfo.SSID,wifi_char,32);
      strncpy(wifiInfo.password,password_char,32);
      //strncpy(wifiInfo.name,"",32);
      //strncpy(wifiInfo.passwd,"",32);
      
      wifiInfo.KEY_WPA_TYPE = 4;//可以直接更改为数字

      (*env)->ReleaseStringUTFChars(env,wifi,wifi_char);
      (*env)->ReleaseStringUTFChars(env,password,password_char);
      
      ret = pps_set_AP_device_wificfg(&wifiInfo);
  }
  
  return ret;
}

//获取wifi信息
jint Java_com_wetoop_camera_CameraJni_stringFromJNI( JNIEnv* env,
         jobject thiz,jint WPA,jstring wifi,jstring password,jint type,jstring tokenname,jstring tokenpassword)
{
	WIFI_INFO wifi1 = {0};

	const char* wifi_char = (*env)->GetStringUTFChars(env,wifi,0);
	const char* password_char = (*env)->GetStringUTFChars(env,password,NULL);
	if(type == 1)
	{
		const char* tokenname_char = (*env)->GetStringUTFChars(env,tokenname,NULL);
		const char* tokenpassword_char = (*env)->GetStringUTFChars(env,tokenpassword,NULL);
		if(strlen(tokenname_char))
		{
			memcpy(wifi1.name,tokenname_char,32);
		}
		if(strlen(tokenpassword_char))
		{
			memcpy(wifi1.passwd,tokenpassword_char,32);
		}
		(*env)->ReleaseStringUTFChars(env,tokenname,tokenname_char);
		(*env)->ReleaseStringUTFChars(env,tokenpassword,tokenpassword_char);
	}

	memcpy(wifi1.SSID,wifi_char,32);
	memcpy(wifi1.password,password_char,32);
	(*env)->ReleaseStringUTFChars(env,wifi,wifi_char);
	(*env)->ReleaseStringUTFChars(env,password,password_char);

	wifi1.KEY_WPA_TYPE = WPA;
	wifi1.sleep_ms = 100;
	wifi1.type = type;

	LOGI("1111111");
	LOGI("SSID:%s,password:%s",wifi1.SSID,wifi1.password);
	pps_init();
	jint ret = pps_set_device_wifi(&wifi1);
	LOGI("2222");
    return ret;
}
/*typedef struct
{
    int nums;  /**<nums of online devices
    SINGLE_SEARCH_DEVICE_INFO deviceinfo[128]; /**<info of one device
}SEARCH_DEVICE_INFO;*///获取设备的序列号
jobjectArray Java_com_wetoop_camera_CameraJni_searchDevice(JNIEnv* env,jobject thiz){
	jint num;
	jint size;
	jint ip;
	jstring jstr;
	jstring sn;
	int i;

	pps_init(); 
	SEARCH_DEVICE_INFO search_device_info;
	SINGLE_SEARCH_DEVICE_INFO deviceinfo;
	pps_search_device(&search_device_info);

	num=search_device_info.nums;
	size = num*2;
    jclass objClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray info_sn = (*env)->NewObjectArray(env,size, objClass, 0);

	for(i=0;i<size;i=i+2){
		if(i==0){
			jstr = (*env)->NewStringUTF( env,  search_device_info.deviceinfo[i].sn);
			(*env)->SetObjectArrayElement(env, info_sn, i, jstr);//必须放入jstring
		//jstring sn=(*env)->NewStringUTF( env,  "sn");
			ip = search_device_info.deviceinfo[i].ip;
			char str[25];
			sprintf(str, "%d", ip); 
			sn =(*env)->NewStringUTF( env,  str);
			(*env)->SetObjectArrayElement(env, info_sn, i+1, sn);//必须放入jstring
		}else if(i>=2){
			//int j=i/2;
			jstr = (*env)->NewStringUTF( env,  search_device_info.deviceinfo[i/2].sn);
			(*env)->SetObjectArrayElement(env, info_sn, i, jstr);//必须放入jstring
		//jstring sn=(*env)->NewStringUTF( env,  "sn");
			ip = search_device_info.deviceinfo[i/2].ip;
			char str[25];
			sprintf(str, "%d", ip); 
			sn =(*env)->NewStringUTF( env,  str);
			(*env)->SetObjectArrayElement(env, info_sn, i+1, sn);//必须放入jstring
		}
		
	}

	return info_sn;
}

jobjectArray  Java_com_wetoop_camera_CameraJni_uuidDevice(JNIEnv* env,jobject thiz,jstring username,jstring pwd,jstring devip){
	jstring jstr;
	int i;
	int handle = 0;
	int check = 0;
	long bfirst =0;

    const char* username_char = (*env)->GetStringUTFChars(env,username,NULL);
	const char* pwd_char = (*env)->GetStringUTFChars(env,pwd,NULL);
	const char* devip_char = (*env)->GetStringUTFChars(env,devip,NULL);

	jclass objClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray info_uuid = (*env)->NewObjectArray(env,1, objClass, 0);

    //num = sizeof(devip)/sizeof(devip[0]);
    if(!bfirst)
	{
		pps_init(); 
		
		    PPSDEV_LOGIN_INFO loginInfo = {0};
		    //储存登陆信息
		    strncpy(loginInfo.devip, devip_char,32);
		    strncpy(loginInfo.username,username_char,32);
		    strncpy(loginInfo.password,pwd_char,32);
		    loginInfo.localport = 80;
		    handle = ppsdev_open(loginInfo);

		    PPSDEV_INFO devInfo;
            devInfo.devname[0] = '\0';
            
		    check = ppsdev_get_info(handle,&devInfo);
		    (*env)->ReleaseStringUTFChars(env,username,username_char);
		    (*env)->ReleaseStringUTFChars(env,pwd,pwd_char);
		    (*env)->ReleaseStringUTFChars(env,devip,devip_char);
		    if(check<0){
		    	jstr = (*env)->NewStringUTF( env,  "false");
		    	(*env)->SetObjectArrayElement(env, info_uuid, 0, jstr);
    	    }else{
    	    	jstr = (*env)->NewStringUTF( env,  devInfo.uuid);
    	    	(*env)->SetObjectArrayElement(env, info_uuid, 0, jstr);
    	    }
    	    ppsdev_close(handle);
		bfirst = 1;
	}  
	pps_free(); 	
    
	
	return info_uuid;
}

//获取设备的ip地址
jintArray Java_com_wetoop_camera_CameraJni_searchDeviceIp(JNIEnv* env,jobject thiz){
	
	jint num;
	int i;

	pps_init();
	SEARCH_DEVICE_INFO search_device_info;
	SINGLE_SEARCH_DEVICE_INFO deviceinfo;
	pps_search_device(&search_device_info);

	num=search_device_info.nums;
	jintArray  array;//定义数组对象

    array = (*env)-> NewIntArray(env, num);
    jint ip[num];
    for(i=0;i<num;i++){
    	ip[i]=search_device_info.deviceinfo[i].ip;	
    }
    (*env)->SetIntArrayRegion(env, array, 0, num,ip);
    

    return array;
}

//获取设备基本信息
jobjectArray Java_com_wetoop_camera_CameraJni_deviceInfo(JNIEnv* env,jobject thiz,jstring username,jstring pwd,jstring devip,jint port){
	jstring jstr;
	jstring devname;
	jstring uuid;
	jstring model;
	jstring seriano;
	jstring softwareversion;//软件版本
	jstring hardwareversion;//硬件版本
	jstring firmwareversion;
	int i;
	//int handle = 0;
	int check_devInfo = 0;
	long bfirst =0;

    const char* username_char = (*env)->GetStringUTFChars(env,username,NULL);
	const char* pwd_char = (*env)->GetStringUTFChars(env,pwd,NULL);
	const char* devip_char = (*env)->GetStringUTFChars(env,devip,NULL);
	jclass objClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray info_sn = (*env)->NewObjectArray(env,6, objClass, 0);
    //num = sizeof(devip)/sizeof(devip[0]);
    if(!bfirst)
	{
		    pps_init(); 
		
		    PPSDEV_LOGIN_INFO loginInfo = {0};
		    //储存登陆信息
		    strncpy(loginInfo.devip, devip_char,32);
		    strncpy(loginInfo.username,username_char,32);
		    strncpy(loginInfo.password,pwd_char,32);
		    loginInfo.localport = port;
		    long handleMain = ppsdev_open(loginInfo);
		    PPSDEV_INFO devInfo = {0};
            //devInfo.devname[0] = '\0';
		    check_devInfo = ppsdev_get_info(handleMain,&devInfo);//搜索设备信息

		    (*env)->ReleaseStringUTFChars(env,username,username_char);
		    (*env)->ReleaseStringUTFChars(env,pwd,pwd_char);
		    (*env)->ReleaseStringUTFChars(env,devip,devip_char);
		    
		    if(check_devInfo<0){
		    	jstr = (*env)->NewStringUTF( env,  "false");
		    	(*env)->SetObjectArrayElement(env, info_sn, 0, jstr);//必须放入jstring
    	    }else{
    	    	devname = (*env)->NewStringUTF( env,  devInfo.devname);
    	    	(*env)->SetObjectArrayElement(env, info_sn, 0, devname);//必须放入jstring
    	    	model = (*env)->NewStringUTF( env,  devInfo.model);
    	    	(*env)->SetObjectArrayElement(env, info_sn, 1, model);//必须放入jstring
    	    	seriano = (*env)->NewStringUTF( env,  devInfo.seriano);
    	    	(*env)->SetObjectArrayElement(env, info_sn, 2, seriano);//必须放入jstring
    	    	softwareversion = (*env)->NewStringUTF( env,  devInfo.softwareversion);
    	    	(*env)->SetObjectArrayElement(env, info_sn, 3, softwareversion);//必须放入jstring
    	    	hardwareversion = (*env)->NewStringUTF( env,  devInfo.hardwareversion);
    	    	(*env)->SetObjectArrayElement(env, info_sn, 4, hardwareversion);//必须放入jstring
    	    	uuid = (*env)->NewStringUTF( env,  devInfo.uuid);
    	    	(*env)->SetObjectArrayElement(env, info_sn, 5, uuid);//必须放入jstring

    	    }
		bfirst = 1;
	}  
	
	return info_sn;
}

//获取设备网络基本信息
jobjectArray Java_com_wetoop_camera_CameraJni_netlinkInfo(JNIEnv* env,jobject thiz){
	jclass objClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray info_sn = (*env)->NewObjectArray(env,3, objClass, 0);
	//jstring wifistatus;//wifi连接状态<0:disable 1:enable*/
	int wifilevel;//wifi信号强度<0-100*/
	int ltestatus;//运营商信号<*0:disbale 1:2G 2:3G 3:4G*/
	int ltelevel;//运营商信号强度<0-100*/
	jstring wifilevelString;
	jstring ltestatusString;
	jstring ltelevelString;
	jstring jstr;
	int check_netlinkstatus = 0;

	NET_LINK_STATUS net_link_status = {0};
	check_netlinkstatus = pps_get_device_netlinkstatus(handleMain,&net_link_status);
	if(check_netlinkstatus<0){
		jstr = (*env)->NewStringUTF( env,  "false");
		(*env)->SetObjectArrayElement(env, info_sn, 0, jstr);//必须放入jstring
    }else{
    	wifilevel = net_link_status.wifilevel;
    	char wifilevelStr[50];
    	sprintf(wifilevelStr, "%d", wifilevel); 
    	wifilevelString = (*env)->NewStringUTF( env,  wifilevelStr);
    	(*env)->SetObjectArrayElement(env, info_sn, 0, wifilevelString);//必须放入jstring

        ltestatus = net_link_status.ltestatus;
    	char ltestatusStr[50];
    	sprintf(ltestatusStr, "%d", ltestatus);
    	ltestatusString = (*env)->NewStringUTF( env,  ltestatusStr);
    	(*env)->SetObjectArrayElement(env, info_sn, 1, ltestatusString);//必须放入jstring

        ltelevel = net_link_status.ltelevel;
    	char ltelevelStr[50];
    	sprintf(ltelevelStr, "%d", ltelevel);
    	ltelevelString = (*env)->NewStringUTF( env,  ltelevelStr);
    	(*env)->SetObjectArrayElement(env, info_sn, 2, ltelevelString);//必须放入jstring
    }
    return info_sn;
}

//获取设备电池百分比
jint Java_com_wetoop_camera_CameraJni_batteryInfo(JNIEnv* env,jobject thiz){
	int check_battery = -1;
	check_battery = pps_get_device_battery_energy(handleMain);//电池剩余电量
	if(check_battery<0){
		check_battery = -1;
    }
    return check_battery;
}

//获取设备红外显示
jint Java_com_wetoop_camera_CameraJni_alarmInfo(JNIEnv* env,jobject thiz){
	ALARM_CFG alarm_cfg = {0};
	int alarm_getcfg = ppsdev_alarm_getcfg(handleMain,0,&alarm_cfg);
	int alarm_static;
	if(alarm_getcfg < 0){
		alarm_static = alarm_getcfg;
	}else{
		alarm_static = alarm_cfg.enable;
	}
	
    return alarm_static;
}

//获取设备储存卡信息
jobjectArray Java_com_wetoop_camera_CameraJni_spaceInfo(JNIEnv* env,jobject thiz){
	//储存卡容量
	int total_space;
	int free_space;
	jstring total_spaceStr;
	jstring free_spaceStr;
	jstring jstr;

	jclass objClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray info_sn = (*env)->NewObjectArray(env,2, objClass, 0);
	PPSDEV_STORAGE_INFO ppsdev_storage_info = {0};
    int check_storage = ppsdev_get_storage_info(handleMain,&ppsdev_storage_info);
    if(check_storage<0){
		jstr = (*env)->NewStringUTF( env,  "false");
		(*env)->SetObjectArrayElement(env, info_sn, 0, jstr);
    }else{
    	int count = ppsdev_storage_info.count;
        PPSDEV_STORAGE_SINGAL_INFO info;
        total_space = ppsdev_storage_info.info[0].total_space;
        char ltelevelChar[50];
        sprintf(ltelevelChar, "%d", total_space);
        total_spaceStr = (*env)->NewStringUTF( env,  ltelevelChar);
        (*env)->SetObjectArrayElement(env, info_sn, 0, total_spaceStr);
        
        free_space = ppsdev_storage_info.info[0].free_space;
        char free_spaceChar[50];
        sprintf(free_spaceChar, "%d", free_space);
        free_spaceStr = (*env)->NewStringUTF( env,  free_spaceChar);
        (*env)->SetObjectArrayElement(env, info_sn, 1, free_spaceStr);
    }
	
    return info_sn;
}

void Java_com_wetoop_camera_CameraJni_ppsdevClose(JNIEnv* env,jobject thiz){
    ppsdev_close(handleMain);
    pps_free();
}

//设置红外移动侦测
jint Java_com_wetoop_camera_CameraJni_setAlarmCfg(JNIEnv* env,jobject thiz,jstring username,jstring pwd,jstring devip,jint port,jint check){
	//long handle = 0;
    long bfirst =0;
    jint ret=-1;
	
	const char* username_char = (*env)->GetStringUTFChars(env,username,NULL);
	const char* pwd_char = (*env)->GetStringUTFChars(env,pwd,NULL);
	const char* devip_char = (*env)->GetStringUTFChars(env,devip,NULL);

	if(!bfirst)
	{
		//pps_init();

		ALARM_CFG alarm_getcfg;
		/*PPSDEV_LOGIN_INFO loginInfo = {0};
		    //储存登陆信息
		strncpy(loginInfo.devip, devip_char,32);
		strncpy(loginInfo.username,username_char,32);
		strncpy(loginInfo.password,pwd_char,32);
		loginInfo.localport = port;
		handle = ppsdev_open(loginInfo);*/
	    
	    alarm_getcfg.enable=check;
	    alarm_getcfg.sensitivity=2;
	    ret = ppsdev_alarm_setcfg(handleMain,0,&alarm_getcfg);//@return 0- succeed <0 error code.

	    bfirst = 1;
	}

	return ret;
}


static JavaVM *gs_jvm=NULL; 
static jobject gs_object=NULL; 
static int upgradeCount=0; 

static void updatecallbackStatus(int status){
	upgradeCount = status;
}
jint Java_com_wetoop_camera_CameraJni_upgrade(JNIEnv* env,jobject thiz,jstring username,jstring pwd,jstring devip,jint port,jstring filename){
	//long handle = 0;
    long bfirst =0;
    jint ret=-1;

    (*env)->GetJavaVM(env,&gs_jvm);
    (*gs_jvm)->AttachCurrentThread(gs_jvm,&env, NULL); 
    jclass cls = (*env)->GetObjectClass(env,thiz);
    jfieldID fieldPtr = (*env)->GetFieldID(env,cls,"upgradeNum","I");
	
	const char* username_char = (*env)->GetStringUTFChars(env,username,NULL);
	const char* pwd_char = (*env)->GetStringUTFChars(env,pwd,NULL);
	const char* devip_char = (*env)->GetStringUTFChars(env,devip,NULL);
	const char* filename_char = (*env)->GetStringUTFChars(env,filename,NULL);
	(*env)->GetJavaVM(env,&gs_jvm);
	//直接赋值obj到DLL中的全局变量是不行的,应该调用以下函数:  
     gs_object=(*env)->NewGlobalRef(env,thiz);

	if(!bfirst)
	{
		//pps_init();

		ALARM_CFG alarm_getcfg;
		/*PPSDEV_LOGIN_INFO loginInfo = {0};
		    //储存登陆信息
		strncpy(loginInfo.devip, devip_char,32);
		strncpy(loginInfo.username,username_char,32);
		strncpy(loginInfo.password,pwd_char,32);
		loginInfo.localport = port;
		handle = ppsdev_open(loginInfo);*/
	    
	    jstring jstr = (*env)->NewStringUTF( env,  filename_char);
	    ret = ppsdev_upgrade(handleMain,jstr,updatecallbackStatus);//@return 0- succeed <0 error code.
	    if(ret>=0){
	    	while(upgradeCount<100||upgradeCount==-1){
	    		sleep(1);//休息一秒
	    		(*env)->SetIntField(env,gs_object,fieldPtr,(jint)upgradeCount);
	    	}
	    }

	    bfirst = 1;
	}

	return ret;
}

//设置访问密码
jint Java_com_wetoop_camera_CameraJni_setPwd(JNIEnv* env,jobject thiz,jstring setPwd){
    jint ret=-1;
	
	char* setPwd_char = (char*)(*env)->GetStringUTFChars(env,setPwd,NULL);
	LOGI("完成初始化setPwd");

	//if(!bfirst)
	//{
		//pps_init();

		//ALARM_CFG alarm_getcfg;
		/*PPSDEV_LOGIN_INFO loginInfo = {0};
		    //储存登陆信息
		strncpy(loginInfo.devip, devip_char,32);
		strncpy(loginInfo.username,username_char,32);
		strncpy(loginInfo.password,pwd_char,32);
		loginInfo.localport = port;//使用音频的端口
		handle = ppsdev_open(loginInfo);*/
	    
	    //jstring jstr = (*env)->NewStringUTF(env, setPwd_char);
	    LOGI("jstr=%s",setPwd_char);
	    ret = ppsdev_set_password(handleMain,setPwd_char);//@return 0- succeed <0 error code.
	    LOGI("ret=%d",ret);

	    //bfirst = 1;
	//}

	return ret;
}

jint Java_com_wetoop_camera_CameraJni_voiceTalkOpen(JNIEnv* env,jobject thiz,jstring username,jstring pwd,jstring devip,jint port){
	PPSDEV_VOICE_PARAMS ppsdev_voice_params;
    long bfirst =0;
    jint ret=-1;
	
	const char* username_char = (*env)->GetStringUTFChars(env,username,NULL);
	const char* pwd_char = (*env)->GetStringUTFChars(env,pwd,NULL);
	const char* devip_char = (*env)->GetStringUTFChars(env,devip,NULL);
	//unsigned char* buffer_char = (*env)->GetByteArrayElements(env,buffer,NULL);

	if(!bfirst){
		pps_init();

		ALARM_CFG alarm_getcfg;
		PPSDEV_LOGIN_INFO loginInfo = {0};
		    //储存登陆信息
		strncpy(loginInfo.devip, devip_char,32);
		strncpy(loginInfo.username,username_char,32);
		strncpy(loginInfo.password,pwd_char,32);
		loginInfo.localport = port;
		handleVoice = ppsdev_open(loginInfo);

		ppsdev_voice_params.codec = 1;
		ppsdev_voice_params.samplerate = 8000;
		ppsdev_voice_params.bitrate = 16;
		ppsdev_voice_params.channels = 1;
		ppsdev_voice_params.buffsize = 320;
		hvoice = ppsdev_voicetalk_open(handleVoice,0,&ppsdev_voice_params);
		/*if(hvoice>0){
			ret = ppsdev_voicetalk_write(handleVoice,hvoice,buffer_char,320);  
		}else{
			ret=-1;
		}*/

		bfirst = 1;
	}
	return hvoice;
}

jint Java_com_wetoop_camera_CameraJni_voiceTalkWrite(JNIEnv* env,jobject thiz,jbyteArray buffer){
	jint ret=-1;
	unsigned char* buffer_char = (*env)->GetByteArrayElements(env,buffer,NULL);
	if(hvoice>0){
		ret = ppsdev_voicetalk_write(handleVoice,hvoice,buffer_char,320);    
	}else{
		ret=-1;
	}
	return ret;
}

void Java_com_wetoop_camera_CameraJni_voiceTalkClose(JNIEnv* env,jobject thiz){
	ppsdev_voicetalk_close(handleVoice,hvoice);
}

jintArray Java_com_wetoop_camera_CameraJni_searchByMonth(JNIEnv* env,jobject thiz,
	int year,int month){    
	RECORD_MONTH_SEARCH recrd_month_search;//传入年和月
	recrd_month_search.year = year;
	recrd_month_search.month = month;
	RECORD_MONTH_LIST record_month_list;//获取列表
	LOGI("searchByMonth 进入");
	int callBack = ppsdev_record_search_by_month(handleMain,0,0,&recrd_month_search,&record_month_list);
	if(callBack<0){
		LOGI("callBack<0");
		int size = 1;
        jintArray info_sn1 = (*env)->NewIntArray(env,size);
        jint list[size];
        int i;
        for(i=0;i<size;i++){
        	list[i]=32;
        }
        (*env)->SetIntArrayRegion(env,info_sn1, 0, size, list);
        return info_sn1;
	}else{
		LOGI("callBack>0");
		int size = record_month_list.recordnum;
        jintArray info_sn2 = (*env)->NewIntArray(env,size);
        int i;
        jint list[size];
        for(i=0;i<size;i++){
        	list[i]=record_month_list.recordlist[i];
            //(*env)->SetObjectArrayElement(env, info_sn[i], i, recordlist[i]);
        }
        (*env)->SetIntArrayRegion(env,info_sn2, 0, size, list);
        return info_sn2;
	}
}
jobjectArray Java_com_wetoop_camera_CameraJni_searchByDay(JNIEnv* env,jobject thiz,
	int year,int month,int day){
	jclass objClass = (*env)->FindClass(env, "java/lang/String");
	RECORD_DAY_SEARCH recrd_day_search;//传入年和月
	recrd_day_search.year = year;
	recrd_day_search.month = month;
	recrd_day_search.day = day;
	RECORD_DAY_LIST record_day_list;//获取列表
    LOGI("jobjectArray进入");
	int callBack = ppsdev_record_search_by_day(handleMain,0,0,&recrd_day_search,&record_day_list);
	LOGI("ppsdev_record_search_by_day完成,%d",callBack);
	if(callBack<0){
		int size = 1;
		LOGI("callBack<0");
        jobjectArray info_sn = (*env)->NewObjectArray(env,size, objClass, 0);
        int i;
        for(i=0;i<size;i++){
        	LOGI("size=%d",i);
        	jstring str = (*env)->NewStringUTF(env,"error");
        	(*env)->SetObjectArrayElement(env, info_sn, i, str);
        }
        //jstring error = "error";
        //(*env)->SetObjectArrayElement(env, info_sn, 0, error);
        return info_sn;
	}else{
		int size = record_day_list.recordnum;
		LOGI("callBack>0");
        jobjectArray info_sn = (*env)->NewObjectArray(env,size, objClass, 0);
        int i;
        for(i=0;i<size;i++){
        	LOGI("size=%d",i);
        	jstring str = (*env)->NewStringUTF(env,record_day_list.recordlist[i]);
        	(*env)->SetObjectArrayElement(env, info_sn, i, str);
        }
        return info_sn;
	}
	
}