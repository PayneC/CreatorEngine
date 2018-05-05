#cmake version 指定cmake版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

#UNIX 在所有的类UNIX平台为TRUE,包括OS X和cygwin
#WIN32 在所有的win32平台为TRUE,包括cygwin

#设置编译器路径
SET(CMAKE_C_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.13.26128/bin/Hostx86/x86/cl.exe")
SET(CMAKE_CXX_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.13.26128/bin/Hostx86/x86/cl.exe")

#项目名称
PROJECT(CreatorEngine)

#工程的根目录
#PROJECT_SOURCE_DIR
#运行cmake命令的目录,通常是${PROJECT_SOURCE_DIR}/build
#PROJECT_BINARY_DIR
#当前处理的CMakeLists.txt所在的路径
#CMAKE_CURRENT_SOURCE_DIR

#设置可执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#设置库文件输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#添加环境变量
#ADD_DEFINITIONS(-DEBUG -DEBUGX)

#头文件目录
INCLUDE_DIRECTORIES(ThirdParty ThirdParty/glew/include/GL ThirdParty/glfw3/include/GLFW Runtime/Core/Public Runtime/IMGUI/Public Runtime/Lua/Public Runtime/UI/Public Runtime)

#源文件目录
AUX_SOURCE_DIRECTORY(Runtime DIR_SRCS)

#查找源文件
FILE(GLOB SOURCE_CORE "Runtime/Core/Private/*.cpp")
FILE(GLOB SOURCE_IMGUI "Runtime/IMGUI/Private/*.cpp")
FILE(GLOB SOURCE_LUA "Runtime/Lua/Private/*.cpp")
FILE(GLOB SOURCE_UI "Runtime/UI/Private/*.cpp")

FILE(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)

SOURCE_GROUP("Include" FILES ${CURRENT_HEADERS})
SOURCE_GROUP("Core" FILES ${SOURCE_CORE})
SOURCE_GROUP("IMGUI" FILES ${SOURCE_IMGUI})
SOURCE_GROUP("Lua" FILES ${SOURCE_LUA})
SOURCE_GROUP("UI" FILES ${SOURCE_UI})

#添加要编译的可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS} ${CURRENT_HEADERS} ${SOURCE_CORE} ${SOURCE_IMGUI} ${SOURCE_LUA} ${SOURCE_UI})

#表示最终编译为一个库
#static表示静态库
#shared表示动态库
#ADD_LIBRARY(Box2D STATIC ${box2d_source_files})

#链接所需的库
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} m)