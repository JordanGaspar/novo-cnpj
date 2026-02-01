cmake_minimum_required(VERSION 3.31)

project(CNPJ LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED source/CNPJ.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

target_include_directories(${PROJECT_NAME}
	PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

enable_testing()

add_subdirectory(test)