cmake_minimum_required(VERSION 2.8) #проверка версии cmake

set(PROJECT led_control) #присваиваем переменной PROJECT значение AwesomeLibrary
project(${PROJECT} CXX)

if ( NOT DEFINED GTEST_INCLUDE)
	set(GTEST_INCLUDE "/usr/include")
endif()

if ( NOT DEFINED GTEST_LIB)
	set(GTEST_LIB "/usr/lib")
endif()

if ( NOT DEFINED TEST)
	set(TEST "NO")
endif()

macro(add_app_executable BUILD_TYPE) #макрос, выполняющий сборку с необходимыми параметрами в зависимости от значения входной переменной
	if (${BUILD_TYPE} STREQUAL "release")#если значение входной переменной равно Debug, то
		add_subdirectory(./CommandSetState/ ../CommandSetState/build/)
		add_subdirectory(./CommandGetState/ ../CommandGetState/build/)
		add_subdirectory(./CommandSetColor/ ../CommandSetColor/build/)
		add_subdirectory(./CommandGetColor/ ../CommandGetColor/build/)
		add_subdirectory(./CommandSetRate/ ../CommandSetRate/build/)
		add_subdirectory(./CommandGetRate/ ../CommandGetRate/build/)
		add_subdirectory(./BadLib/ ../BadLib/build/)
		aux_source_directory("./sources" SOURCES)#задаем папки в которых хранятся исходники
		add_executable(${PROJECT} ${SOURCES}) #создаем динамическую библиотеку
		target_link_libraries(${PROJECT} pthread ${CMAKE_DL_LIBS})
		set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS "-O2 -std=c++11 -pedantic -Wall -Wextra -DNDEBUG")#задаем ключи компилятора и макросы для цели ${PROJECT}
		add_custom_command(TARGET ${PROJECT} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E make_directory ../${BUILD_TYPE}
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT}> ../${BUILD_TYPE}
			COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${PROJECT}>)
	endif ()

	if (${BUILD_TYPE} STREQUAL "debug")#если значение входной переменной равно Debug, то
		add_subdirectory(./CommandSetState/ ../CommandSetState/build/)
		add_subdirectory(./CommandGetState/ ../CommandGetState/build/)
		add_subdirectory(./CommandSetColor/ ../CommandSetColor/build/)
		add_subdirectory(./CommandGetColor/ ../CommandGetColor/build/)
		add_subdirectory(./CommandSetRate/ ../CommandSetRate/build/)
		add_subdirectory(./CommandGetRate/ ../CommandGetRate/build/)
		add_subdirectory(./BadLib/ ../BadLib/build/)
		aux_source_directory("./sources" SOURCES)#задаем папки в которых хранятся исходники
		add_executable(${PROJECT}_debug ${SOURCES}) #создаем динамическую библиотеку
		target_link_libraries(${PROJECT}_debug pthread ${CMAKE_DL_LIBS})
		set_target_properties(${PROJECT}_debug PROPERTIES COMPILE_FLAGS "-O0 -g3 -std=c++11 -pedantic -Wall -Wextra -D__LED_CONTROL_DEBUG__")#задаем ключи компилятора и макросы для цели ${PROJECT}
		add_custom_command(TARGET ${PROJECT}_debug POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E make_directory ../${BUILD_TYPE}
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT}_debug> ../${BUILD_TYPE}
			COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${PROJECT}_debug>)
	endif ()

	if (${BUILD_TYPE} STREQUAL "release_test")#если значение входной переменной равно Debug, то
		add_subdirectory(./CommandSetState/ ../CommandSetState/build/)
		add_subdirectory(./CommandGetState/ ../CommandGetState/build/)
		add_subdirectory(./CommandSetColor/ ../CommandSetColor/build/)
		add_subdirectory(./CommandGetColor/ ../CommandGetColor/build/)
		add_subdirectory(./CommandSetRate/ ../CommandSetRate/build/)
		add_subdirectory(./CommandGetRate/ ../CommandGetRate/build/)
		add_subdirectory(./BadLib/ ../BadLib/build/)
		include_directories(${GTEST_INCLUDE})
		link_directories(${GTEST_LIB})
		aux_source_directory("./sources" SOURCES_TEST)#задаем папки в которых хранятся исходники
		aux_source_directory("./tests" SOURCES_TEST)#задаем папки в которых хранятся исходники
		link_directories("/usr/lib")
		add_executable(${PROJECT}_test ${SOURCES_TEST}) #создаем динамическую библиотеку
		set_target_properties(${PROJECT}_test PROPERTIES COMPILE_FLAGS "-O2 -std=c++11 -pedantic -Wall -Wextra -D__LED_CONTROL_TEST__")#задаем ключи компилятора и макросы для цели ${PROJECT}
		target_link_libraries(${PROJECT}_test gtest gtest_main pthread ${CMAKE_DL_LIBS})
		add_custom_command(TARGET ${PROJECT}_test POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E make_directory ../${BUILD_TYPE}
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT}_test> ../${BUILD_TYPE}
			COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${PROJECT}_test>)
		run_test(${PROJECT}_test)
	endif ()

	if (${BUILD_TYPE} STREQUAL "debug_test")#если значение входной переменной равно Debug, то
		add_subdirectory(./CommandSetState/ ../CommandSetState/build/)
		add_subdirectory(./CommandGetState/ ../CommandGetState/build/)
		add_subdirectory(./CommandSetColor/ ../CommandSetColor/build/)
		add_subdirectory(./CommandGetColor/ ../CommandGetColor/build/)
		add_subdirectory(./CommandSetRate/ ../CommandSetRate/build/)
		add_subdirectory(./CommandGetRate/ ../CommandGetRate/build/)
		add_subdirectory(./BadLib/ ../BadLib/build/)
		include_directories(${GTEST_INCLUDE})
		link_directories(${GTEST_LIB})
		aux_source_directory("./sources" SOURCES_TEST)#задаем папки в которых хранятся исходники
		aux_source_directory("./tests" SOURCES_TEST)#задаем папки в которых хранятся исходники
		link_directories("/usr/lib")
		add_executable(${PROJECT}_debug_test ${SOURCES_TEST}) #создаем динамическую библиотеку
		set_target_properties(${PROJECT}_debug_test PROPERTIES COMPILE_FLAGS "-O0 -g3 -std=c++11 -pedantic -Wall -Wextra -D__LED_CONTROL_DEBUG__ -D__LED_CONTROL_TEST__")#задаем ключи компилятора и макросы для цели ${PROJECT}
		target_link_libraries(${PROJECT}_debug_test gtest gtest_main pthread ${CMAKE_DL_LIBS}) 
		add_custom_command(TARGET ${PROJECT}_debug_test POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E make_directory ../${BUILD_TYPE}
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT}_debug_test> ../${BUILD_TYPE}
			COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${PROJECT}_debug_test>)
		run_test(${PROJECT}_debug_test)
	endif ()
endmacro()

add_custom_target(test)
macro(run_test TEST_TARGET)
	add_custom_target(${TEST_TARGET}_run_test
		COMMAND ${TEST_TARGET}
		DEPENDS ${TEST_TARGET}
		WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
	add_dependencies(test ${TEST_TARGET}_run_test)
endmacro()

if ( ${TEST} STREQUAL "YES")
	add_app_executable("release_test")
endif()

if ( ${TEST} STREQUAL "NO")
	add_app_executable("release")
endif()
