cmake_minimum_required(VERSION 3.25)

project(
	Cor
	VERSION 1.0.0
	LANGUAGES CXX
)

option(COR_BUILD_EXAMPLES ON)

add_library(Cor STATIC
	src/Allocator.cc
	src/Allocators/InternalAllocator.hh
	src/Allocators/SystemAllocator.cc
	src/Allocators/LinearAllocator.cc 
)

target_include_directories(Cor PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(Cor PUBLIC cxx_std_17)

if(WIN32)
	# Target windows version: 11/10
	target_compile_definitions(Cor PRIVATE
		_WIN32_WINNT=0x0A00
	)
else()
	message(FATAL_ERROR "Platform unsupported!")
endif()

if (MSVC)
	target_compile_options(Cor PRIVATE
		/WX
		/wd4324	
		/GT 
	)
	target_compile_options(Cor INTERFACE /GT)
else()
	message(FATAL_ERROR "Compiler unsupported!")
endif()


set_target_properties(Cor PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    UNITY_BUILD ON)

if (COR_BUILD_EXAMPLES)
add_executable(CorTests tests/AllocatorTest.cc)
target_compile_options(CorTests PRIVATE /WX)
target_link_libraries(CorTests PUBLIC Cor)
endif()
