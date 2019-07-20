#ifndef __UtilityAndroid_H__
#define __UtilityAndroid_H__

extern struct android_app* g_pAndroidApp;

double GetSystemTime();
double GetSystemTimeSinceGameStart();
void OutputMessage(const char* message, ...);
char* LoadCompleteFile(const char* filename, long* length);

#endif //__UtilityAndroid_H__
