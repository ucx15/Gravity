#pragma once

#include "utils.hpp"
#include "settings.hpp"

class Body {
	public:
		Vec pos;      // Position

		float mass;   // Mass
		int rad;      // Radius

		Vec *trail;
		int trailCtr, trailFull;

		Vec vel, acc; // Velocity + Acceleration
		Color color;  // Color of Body
		uint32_t colU32, colTrailU32;  // Color of Body

	public:
		Body();
		Body(Vec pos_, float mass_);

		void edges();
		void applyForce(Vec force);
		void update(float dt);
		void show(SDL_Surface *renderSurf);
		void renderTrails(SDL_Surface *surf);
 
};
