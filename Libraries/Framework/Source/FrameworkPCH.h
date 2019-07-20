#ifndef __FrameworkPCH_H__
#define __FrameworkPCH_H__

#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
#else
#define nullptr 0
#include "../Source-Android/FrameworkAndroid.h"
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>

#include <string>
#include <map>
#include <vector>
#include <queue>

#include "../Libraries/imgui/imgui.h"
#include "../Libraries/cJSON/cJSON.h"
#include "../Libraries/Bullet3/src/btBulletDynamicsCommon.h"

#if WIN32 && _DEBUG
#include "Memory/MyMemory.h"
#endif

#if WIN32
#include <GL/GL.h>
#include "../Source-Win32/GL/glext.h"
#include "../Source-Win32/GL/wglext.h"
#endif

#if WIN32
#include "../Source-Win32/Utility/WindowsHelpers.h"
#endif
#include "Utility/Helpers.h"
#include "Utility/ShaderProgram.h"

#include "Math/MathHelpers.h"
#include "Math/Vector.h"
#include "Math/MyMatrix.h"

#include "GL/GLHelpers.h"
#if WIN32
#include "../Source-Win32/GL/GLExtensions.h"
#include "../Source-Win32/GL/WGLExtensions.h"
#endif

typedef Vector2 vec2;
typedef Vector3 vec3;
typedef Vector4 vec4;
typedef Vector2Int ivec2;
typedef Vector3Int ivec3;
typedef Vector4Int ivec4;
typedef MyMatrix mat4;

#include "GameCore/GameCore.h"
#include "Events/Event.h"
#include "Events/InputEvent.h"
#include "Events/EventManager.h"

#if WIN32
#include "../Source-Win32/FrameworkMain.h"
#else
#include "../Source-Android/FrameworkAndroid.h"
#endif

#endif //__FrameworkPCH_H__
