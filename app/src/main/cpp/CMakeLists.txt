cmake_minimum_required( VERSION 3.4.1 )
set( CMAKE_CXX_STANDARD 11 )


add_executable( libinject.so
        Inject/inject.cpp
        Inject/inject_main.cpp)

target_link_libraries( libinject.so log dl )
target_compile_definitions( libinject.so PRIVATE DEBUG )

add_library(Client SHARED
        Client/Client.cpp
        Socket/SocketClient.cpp)

target_link_libraries(Client log m )
target_compile_definitions(Client PRIVATE DEBUG )

add_library(Server SHARED
        Server/Server.cpp
        Server/Substrate/hde64.c
        Server/Substrate/SubstrateDebug.cpp
        Server/Substrate/SubstrateHook.cpp
        Server/Substrate/SubstratePosixMemory.cpp
        Server/Unity/Vector2.hpp
        Server/Unity/Vector3.hpp
        Server/Unity/Quaternion.hpp
        Socket/SocketServer.cpp)

target_link_libraries(Server log m )
target_compile_definitions(Server PRIVATE DEBUG )
