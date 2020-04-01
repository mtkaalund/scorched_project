cmake_minimum_required( VERSION 3.10 )
project(scorched_project VERSION 0.0.1 LANGUAGES CXX)

#find_package(Threads REQUIRED)
#find_package(X11 REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(PNG REQUIRED)

add_subdirectory(OneLoneCoder)

file(GLOB PROJECT_SRC
	"src/*.cc"
)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

# Specify the C++ Standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}"
	)

target_link_libraries(${PROJECT_NAME}
	olcPixelGameEngine
	)
