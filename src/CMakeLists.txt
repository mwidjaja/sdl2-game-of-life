
add_library(unwindLib SHARED IMPORTED)
set_target_properties(unwindLib PROPERTIES
    IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libunwind.so
		)

set(SOURCES 
	main.cpp
	GofLApp.cpp
	GameWindow.cpp
	Backtrace.cpp
	GameState.cpp
	Cell.cpp
)

add_executable(gofl ${SOURCES})

set_target_properties(gofl PROPERTIES
	CXX_STANDARD 17)

target_include_directories(gofl PRIVATE
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(gofl
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	unwindLib)

