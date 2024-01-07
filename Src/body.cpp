#include <iostream>
#include <math.h>

#include "body.hpp"


// Constructors
Body::Body() {}

Body::Body(Vec pos_, float mass_) {
    pos  = pos_;
	mass = mass_;
	rad  = lerp(MIN_RAD, MAX_RAD, mass_/MAX_MASS);

    if (DRAW_TRAILS) {
        trail = new Vec[TRAIL_LEN];
        trailCtr = 0;
        trailFull = 0;
    }

	vel.x = vel.y = acc.x = acc.y = 0.f;

    // Mass Based Coloring
    // color.r =  lerp(0.f, 1.f, mass/MAX_MASS);
    // color.g =  lerp(0.f, 1.f, 1.f - mass/MAX_MASS);
    // color.b =  lerp(1.f, 0.f, mass/MAX_MASS);

    // Random Coloring
    color.r =  lerp(.25f, 1.f, randF);
    color.g =  lerp(.25f, 1.f, randF);
    color.b =  lerp(.25f, 1.f, randF);

    colU32 = ColToU32(color);
    colTrailU32 = ColToU32( color * (1.f-TRIAL_DARKEN) );
}


// Methods
void Body::edges() {
    // Bounce Back  NormalizedSpace
    float rvel = - 0.08f;

    if (pos.x < -SCALE) {
        pos.x = -SCALE;
        vel.x *= rvel;
    }
    else if (pos.x > SCALE) {
        pos.x = SCALE;
        vel.x *= rvel;
    }

    if (pos.y < -SCALE) {
        pos.y = -SCALE;
        vel.y *= rvel;
    }
    else if (pos.y > SCALE) {
        pos.y = SCALE;
        vel.y *= rvel;
    }
}

void Body::applyForce(Vec force) {
    acc += force;
}

void Body::update(float dt) {
    // Check Bounds
    this->edges();

    vel += acc/mass *dt;
	pos += vel *dt;

    // Resetting accelaration
    acc.x = acc.y = 0.f;

    if (DRAW_TRAILS) {
        trail[trailCtr++%TRAIL_LEN] = pos;
        trailFull = glm::min(TRAIL_LEN-1, ++trailFull);
    }
}


void Body::show(SDL_Surface *surf) {
    drawCircle(surf, NStoSS(pos, W, H, SCALE) , rad, colU32);
    // drawStarPoint(surf, NStoSS(pos, W, H, SCALE) , colU32);
    // drawPoint(((uint32_t*)(surf->pixels)), NStoSS(pos, W, H, SCALE) , colU32);
}

void Body::renderTrails(SDL_Surface *surf) {
    uint32_t* Buffer = (uint32_t*)surf->pixels;

    if (DRAW_TRAILS){
        Vec trailPos;
        for(int i=0; i<trailFull; i++) {
            trailPos = NStoSS(trail[i], W, H, SCALE);
            drawPoint(Buffer, trailPos, colTrailU32);
        }
    }

}
