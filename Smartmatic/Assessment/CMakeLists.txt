cmake_minimum_required(VERSION 3.0)
project(AssessmentMain)

add_executable(AssessmentMain
			./src/AssessmentMain.cpp
			./src/Compatibility.cpp
			./src/ProcessInputFile.cpp
			./src/WorkItem.cpp
			./src/Algorithms/SortAlgorithm.cpp
)

SET(projIncludDir	./src/
					./
)

SET(src_files
			./src/AssessmentMain.cpp
			./src/Compatibility.cpp
			./src/ProcessInputFile.cpp
			./src/WorkItem.cpp
			./src/Algorithms/SortAlgorithm.cpp
)

SET(include_files
			./src/Compatibility.h
			./src/ItemConsumer.h
			./src/ItemProducerQueue.h
			./src/ProcessInputFile.h
			./src/WorkItem.h
			./src/Algorithms/HeapSort.h
			./src/Algorithms/ShellSort.h
			./src/Algoirthms/SortAlgorithm.h
)

IF (WIN32)
	SET(option WIN32)
	SET(win32_LIBRARIES comctl32 shlwapi dbghelp)
if ( MSVC )
	#do not use for mingw builds
	SET(CMAKE_CXX_FLAGS "/EHa /MP /W4")
	SET(defs -D_WIN32_WINNT=0x501 -D_USE_64BIT_TIME_T -DTIXML_USE_STL -DTIXMLA_USE_STL -D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -D_CRT_NON_CONFORMING_SWPRINTFS )
else ( MSVC )
	# For possible MinGW compilation
	SET(CMAKE_CXX_FLAGS "-include../gcc/include/various.h -std=c++14 -fpermissive")
	SET(defs -D_USE_64BIT_TIME_T -DTIXML_USE_STL -DTIXMLA_USE_STL )
endif ( MSVC )
ENDIF (WIN32)

ADD_DEFINITIONS(${defs})
