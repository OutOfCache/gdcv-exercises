include("../buildutils/CreateSourceGroups.cmake")
include("../buildutils/CreateApp.cmake")
include("../buildutils/BuildOptions.cmake")
project(cogra)

file(GLOB_RECURSE PROJECT_SOURCE *.cpp *.h)
CreateSourceGroups(${PROJECT_SOURCE})
set(COGRA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/interface" CACHE STRING "")

set(COGRA_LIBRARIES debug    	${PROJECT_BINARY_DIR}/Debug/libcogra.lib 
                    optimized 	${PROJECT_BINARY_DIR}/Release/libcogra.lib)

	
					
include_directories(${COGRA_INCLUDE_DIR})
AddGLFWIncludes()
AddGLEWIncludes()
AddGLM()
AddGLI()
AddClipIncludes()
AddIMGUIIncludes()
AddSPDLOGIncludes()
AddTINYFDIncludes()
AddStbImage()
AddEigenIncludes()

SetCompilerLinkerFlags()

add_library(cogra STATIC ${PROJECT_SOURCE})

set_target_properties (cogra PROPERTIES FOLDER cogra)
