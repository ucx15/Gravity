#pragma once

#include <iostream>

#include "glm.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "SDL.h"
#include "settings.hpp"


#define Vec glm::vec2
#define Color glm::vec3

#define randF ( (float)rand()/RAND_MAX )
#define LogVec(v) std::cout << "X: " << v.x << "  Y: " << v.y << '\n'


#define drawPoint(buffer, pos, color) ( buffer[std::min((uint32_t)SIZE, uint32_t((pos).y)*W + uint32_t((pos).x))] = color )

#define SStoNS(v, w, h, s) ( Vec((2.f * (v).x/(w) - 1.f) *(s), (1.f - 2.f * (v).y/(h)) *(s)) )
#define NStoSS(v, w, h, s) ( Vec((w) * (1.f + (v).x/(s)) / 2.f, (h) * (1.f - (v).y/(s)) / 2.f) )

#define ColToU32(c) ( ( uint32_t((c).r*0xFF) <<24) | (uint32_t((c).g*0XFF)<<16) | (uint32_t((c).b*0XFF)<<8) | 0xFF )



void drawCircle(SDL_Surface *surf, Vec pos, int rad, uint32_t color);
void drawStarPoint(SDL_Surface *surf, Vec pos, uint32_t color);

void parseArgs(int nArgs, char *args[]);
void handleEvents(SDL_Event *event, bool *isRunning);
