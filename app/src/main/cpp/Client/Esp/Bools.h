#ifndef BOOLS_H
#define BOOLS_H

#include <jni.h>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <android/log.h>

bool isESP = false;

bool Eskeleton = false;
std::string indetifiq;
bool isPlayerName = false;

bool espIndetificar = false;

bool isPlayerHealth = false;

bool isTeamMateShow = false;

bool color = false;
bool isPlayer360 = false;

bool isPlayerDistance = false;

bool isCrosshair = false;

bool isDrawCircle = false;

bool isPlayerCount = false;

Color LineColorBranco = Color::White();

Color LineColorPreto = Color::Black();

Color CrossColor = Color::White();

Color CircleColor = Color::White();
Color skeletoncolor;
Color boxcolor;
Color linecolor;
Color distancecolor;
Color mococolor;
int LineColor = 0;
Color botcolor;
float CrossSize = 42;

float playerTextSize = 12;

float CircleSize = 22;

float Linesize = 1;

#endif
