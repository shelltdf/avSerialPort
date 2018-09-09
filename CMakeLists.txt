
PROJECT(avSerialPort)
SET(PROJECT_NAME avSerialPort)


add_executable(${PROJECT_NAME}Test
    SerialPort.h 
    SerialPort.cpp 
    main.cpp
    )

add_library(${PROJECT_NAME}Wrapper SHARED
    SerialPort.h 
    SerialPort.cpp 
    SerialPortWrapper.h
    SerialPortWrapper.cpp
    SerialPortWrapper.def
    )

add_executable(${PROJECT_NAME}WrapperTest
    SerialPortWrapperTest.cpp
    )
target_link_libraries(${PROJECT_NAME}WrapperTest
    ${PROJECT_NAME}Wrapper
    )
    
    