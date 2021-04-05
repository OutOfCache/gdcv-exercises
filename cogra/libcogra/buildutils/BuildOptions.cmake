
function (SetCompilerLinkerFlags)
	if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
		add_definitions(-DUNICODE -D_UNICODE)
		add_definitions(-DNOMINMAX)
		set ( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /Zm1000 /GR /W4 /WX /EHsc /wd4201 /wd4127")
		set ( CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1 ")
		set ( CMAKE_CXX_FLAGS_RELEASE  "/MD /D NDEBUG /Ox /GS-" )
		set ( CMAKE_EXE_LINKER_FLAGS "/STACK:10000000 /machine:x64")
		set ( CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL")
		set ( CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG")    
	endif ()

	if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel")		
		add_definitions(-DGLM_FORCE_CXX03)
		add_definitions(-DNOMINMAX)
		set ( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /Zm1000 /GR /W4 /EHsc" )
		set ( CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1 ")
		set ( CMAKE_CXX_FLAGS_RELEASE  "/MD /D NDEBUG /Ox /GS-" )
		set ( CMAKE_EXE_LINKER_FLAGS "/STACK:10000000 /machine:x64")
		set ( CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL")
		set ( CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG")    
	endif ()
endfunction(SetCompilerLinkerFlags)
