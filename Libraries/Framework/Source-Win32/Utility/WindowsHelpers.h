#ifndef __WindowsHelpers_H__
#define __WindowsHelpers_H__

void OutputMessage(const char* message, ...);
char* LoadCompleteFile(const char* filename, long* length);
double GetSystemTime();
double GetSystemTimeSinceGameStart();

#endif //__WindowsHelpers_H__
