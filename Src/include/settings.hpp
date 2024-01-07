# pragma once

// Engine
const int W = 800;
const int H = 600;
const int SIZE = W*H;
const int FPS = 240;

const float UPDATE_TIME = 2.f;   // in seconds

// Physics
const float SCALE = 50'000.f;  // 50,000 m = width/2
// const float G_CONST = 6.674E1F;
const float G_CONST = 3.f;

const int N_BALLS = 50;

const float MIN_MASS = 10;
const float MAX_MASS = 1000;

const int MIN_RAD = 2;
const int MAX_RAD = 8;

const float BALL_VEL = 2000.f;  // m/s

const bool DRAW_TRAILS = false;
const int TRAIL_LEN = FPS*10;
const float TRIAL_DARKEN = .1f;
