cmake_minimum_required(VERSION 3.00)
project(project_name C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -lm")

file(GLOB MAIN
        "source_files/*.c"
        "header_files/*.h"
	"Library/HashMap/*.h"
	"Library/HashMap/*.c"
	"Library/PriorityQueue/*.c"
	"Library/PriorityQueue/*.h"
	"Library/Queue/*.h"
	"Library/Queue/*.c"
	"Security/*.h"
	"Security/*.c"
    )
    add_executable(final ${MAIN})
