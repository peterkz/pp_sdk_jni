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
	wificfg.KEY_WPA_TYPE = 4;//可以直接更改为数字
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
	/*const char* devip_char = (*env)->GetStringUTFChars(env,devip,NULL);
	const char* adminName_char = (*env)->GetStringUTFChars(env,adminName,NULL);
	const char* adminPwd_char = (*env)->GetStringUTFChars(env,adminPwd,NULL);*/
	// (*env)->ReleaseStringUTFChars(env,devip,devip_char);

	if(!bfirst)
	{
		pps_init();
		WIFI_INFO wifiInfo = {0};
		/*PPSDEV_LOGIN_INFO loginInfo = {0};
		//memcpy()是内存拷贝函数，从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
		//储存登陆信息
		strncpy(loginInfo.devip,devip_char,32);
		strncpy(loginInfo.username,adminName_char,32);
		strncpy(loginInfo.password,adminPwd_char,32);
		loginInfo.localport = 80;
		handle = ppsdev_open(loginInfo);
		bfirst = 1;*/

		strncpy(wifiInfo.SSID,wifi_char,32);
	    strncpy(wifiInfo.password,password_char,32);
	    strncpy(wifiInfo.name,"",32);
	    strncpy(wifiInfo.passwd,"",32);
	    
	    wifiInfo.KEY_WPA_TYPE = 4;//可以直接更改为数字

	    (*env)->ReleaseStringUTFChars(env,wifi,wifi_char);
	    (*env)->ReleaseStringUTFChars(env,password,password_char);
	    //wifiInfo.sleep_ms = 1000;
	    //wifiInfo.type = 1;
	    //wificfg.KEY_WPA_TYPE = 4;
	    ret = pps_set_device_wifi(&wifiInfo);//@return 0- succeed <0 error code.
	}

    /*if(handle>0){
        
    }*/
	
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
jobjectArray Java_com_wetoop_camera_CameraJni_deviceInfo(JNIEnv* env,jobject thiz,jstring username,jstring pwd,jstring devip){
	jstring jstr;

	jstring devname;
	jstring uuid;
	jstring model;
	jstring seriano;
	jstring softwareversion;//软件版本
	jstring hardwareversion;//硬件版本
	jstring firmwareversion;
	PPSDEV_INFO device_info;

	int i;
	int handle = 0;
	int check = 0;
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
    	    ppsdev_close(handle);
		//}
		bfirst = 1;
	}  
	pps_free(); 	
	
	return info_sn;
}