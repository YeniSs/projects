cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")

set (-Wall -Wpedantic -Wextra)


project(Project)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

#Source files here
set(SOURCE_FILES
        src/main.cpp src/model/Client.cpp library/model/Client.h src/model/ClientType.cpp library/model/ClientType.h src/model/Student.cpp library/model/Student.h src/model/Senior.cpp library/model/Senior.h src/model/Normal.cpp library/model/Normal.h src/model/Ticket.cpp library/model/Ticket.h
        src/model/Movie.cpp library/model/Movie.h src/model/Seats.cpp library/model/Seats.h src/Managers/ClientManager.cpp library/Managers/ClientManager.h src/Managers/TicketManager.cpp library/Managers/TicketManager.h src/Managers/MovieManager.cpp library/Managers/MovieManager.h src/Managers/SeatsManager.cpp
        library/Managers/SeatsManager.h
        library/Exceptions/MovieException.h library/Exceptions/ClientException.h library/Exceptions/TicketExceptions.h library/Repositories/Repository.h library/Exceptions/SeatsException.h)

add_executable(Project ${SOURCE_FILES})

target_include_directories(Project PUBLIC include)


enable_testing()

find_package (Boost 1.65 COMPONENTS "unit_test_framework" "date_time" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/library
        ${CMAKE_CURRENT_SOURCE_DIR}/library/model
        ${CMAKE_CURRENT_SOURCE_DIR}/library/Exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/library/Managers
        ${CMAKE_CURRENT_SOURCE_DIR}/library/Repositories
        ${Boost_INCLUDE_DIRS}
)

#Test source files here
set(SOURCE_TEST_FILES
        library/model/typedefs.h
        src/model/Client.cpp
        library/model/Client.h
        src/model/ClientType.cpp
        library/model/ClientType.h
        src/model/Senior.cpp
        library/model/Senior.h
        src/model/Normal.cpp
        library/model/Normal.h
        src/model/Student.cpp
        library/model/Student.h
        src/model/Movie.cpp
        library/model/Movie.h
        src/model/Seats.cpp
        library/model/Seats.h
        src/model/Ticket.cpp
        library/model/Ticket.h
        src/Managers/ClientManager.cpp
        library/Managers/ClientManager.h
        src/Managers/SeatsManager.cpp
        library/Managers/SeatsManager.h
        src/Managers/MovieManager.cpp
        library/Managers/MovieManager.h
        src/Managers/TicketManager.cpp
        library/Managers/TicketManager.h
        library/Repositories/Repository.h
        library/Exceptions/ClientException.h
        library/Exceptions/MovieException.h
        library/Exceptions/SeatsException.h
        library/Exceptions/TicketExceptions.h
        test/master.cpp
        test/ClientTest.cpp
        test/TicketTest.cpp
        test/MovieTest.cpp
        test/SeatsTest.cpp
        test/TicketManagerTest.cpp
        test/SeatsManagerTest.cpp
        test/ClientManagerTest.cpp
        test/MovieManagerTest.cpp
)

add_executable(TestProject ${SOURCE_TEST_FILES})

target_include_directories(TestProject PUBLIC include)

target_link_libraries(TestProject
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        Boost::date_time
        )



add_test(NAME Test COMMAND TestProject
        --report_level=detailed
        --log_level=all
        --color_output=yes)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

