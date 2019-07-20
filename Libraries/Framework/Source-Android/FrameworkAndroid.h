#ifndef __FrameworkAndroid_H__
#define __FrameworkAndroid_H__

#include <jni.h>

// In Game project ATM.
void OutputMessage(const char* message, ...);
char* LoadCompleteFile(const char* filename, long* length);

#include <EGL/egl.h>
#include <GLES/gl.h>
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <android/sensor.h>
#include <android/log.h>
#include <memory>

class Framework
{
protected:
	int m_CurrentWindowWidth;
	int m_CurrentWindowHeight;

public:
	Framework();

    void Init(int width, int height);

    unsigned int GetWindowWidth() { return m_CurrentWindowWidth; }
    unsigned int GetWindowHeight() { return m_CurrentWindowHeight; }
};

#endif //__FrameworkAndroid_H__
