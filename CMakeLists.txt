cmake_minimum_required(VERSION 3.26.4)

project(Taxi_Time
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD             14)
set(CMAKE_CXX_STANDARD_REQUIRED    ON)
set(CMAKE_CXX_EXTENSIONS          OFF)


include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_DECLARE(
	${SFML_LIB_NAME}
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG 2.5.1
	GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

set(TAXI_TARGET_NAME Taxi_Time)

add_executable(${TAXI_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Object.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Object.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Taxi.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Taxi.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/include/Car.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Car.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Collisions.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Collisions.cpp

  )

target_include_directories(${TAXI_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(TAXI_SPRITE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sprites/taxi.png")
set(BACKGROUND_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sprites/background.png")
set(CAR_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sprites/car.png")

# Pass sprite paths to the C++ code
target_compile_definitions(${TAXI_TARGET_NAME} PRIVATE 
    TAXI_SPRITE_PATH="${TAXI_SPRITE_PATH}"
    BACKGROUND_PATH="${BACKGROUND_PATH}"
    CAR_PATH="${CAR_PATH}"
)

target_link_libraries(${TAXI_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${TAXI_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${TAXI_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${TAXI_TARGET_NAME} PUBLIC sfml-audio)


function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibToTarget(sfml-graphics ${TAXI_TARGET_NAME})
CopyLibToTarget(sfml-window ${TAXI_TARGET_NAME})
CopyLibToTarget(sfml-system ${TAXI_TARGET_NAME})
CopyLibToTarget(sfml-audio ${TAXI_TARGET_NAME})