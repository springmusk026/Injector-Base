#include <pthread.h>
#include <jni.h>
#include <stdio.h>
#include <wchar.h>
#include "Substrate/SubstrateHook.h"
#include "../Socket/SocketServer.h"
#include "Unity/Quaternion.hpp"
#include "Unity/Color.hpp"
#include "Unity/Vector3.hpp"
#include "Unity/Unity.h"


typedef unsigned long DWORD;
static uintptr_t libBase;


DWORD findLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    DWORD address = 0;

    sprintf(filename, "/proc/self/maps");

    fp = fopen(filename,"rt");
    if (fp == NULL) {
        perror("fopen");
        goto done;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, library)) {
            address = (DWORD) strtoul(buffer, NULL, 16);
            goto done;
        }
    }

    done:

    if (fp) {
        fclose(fp);
    }

    return address;
}

DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr) {
    libBase = findLibrary(libraryName);
    if (libBase == 0)
        return 0;
    return (reinterpret_cast<DWORD>(libBase + relativeAddr));
}
using namespace std;

SocketServer server;

enum Mode {
    InitMode = 1,
    HackMode = 2,
    StopMode = 3,
	ESPMode = 4,///esp will come soon
};

enum m_Features {
    ///takes function as int
    //you can use values directly also ::1,2,3,
	yourfunction = 5,// Mode has 4 values already

};

struct Request {
    int Mode;///feature
    bool m_IsOn;///on off
};

struct Response {
    bool Success;
};


bool myfeature = false;

int InitServer() {
    if (!server.Create()) {
        return -1;
    }
    setsockopt(server.listenfd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const void *>(1), sizeof(int));
    if (!server.Bind()) {
        return -1;
    }
    if (!server.Listen()) {
       return -1;
    }
    return 0;
}

void *CreateServer(void *) {
    if (InitServer() == 0) {
        if (server.Accept()) {
            Request request{};
            while (server.receive((void*)&request) > 0) {
                Response response{};
                if (request.Mode == Mode::InitMode) {
                    response.Success = true;
					
                } else if (request.Mode == Mode::StopMode) {
                    response.Success = true;
                    server.send((void *) &response, sizeof(response));
                    server.Close();
                    pthread_exit(nullptr);
					
                } else if (request.Mode == Mode::HackMode) {
					response.Success = true;
                }else if (request.Mode == m_Features::yourfunction) {
                    myfeature = request.m_IsOn;//onoff boolean
                    /*Usage: if(myfeature){
                     /////your stuffs here
                     }
                     TODO::put this on your thread
                     */
                    LOGI("SUCESS");
                    response.Success = true;

                }
                server.send((void*)& response, sizeof(response));
            }
        }
    }
    return nullptr;
}


///////FOR HOOKING AND PATCHING EXAMPLES LOOK THE LGL MOD MENU TEMPLATE
void *hack_thread(void *) {
    while (true) {
        if (getAbsoluteAddress("libname.so",0) != 0) {/////use it to prevent some random freezing on startup

        pthread_exit(NULL);
       }
    }
  return NULL;
}


extern "C"
void __attribute__ ((constructor)) OnLoad() {
	pthread_t ptid;
	pthread_create(&ptid, nullptr, CreateServer, nullptr);
	
	pthread_t ptid2;
    pthread_create(&ptid2, NULL, hack_thread, NULL);

}
