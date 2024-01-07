#include <iostream>
#include <chrono>
#include <math.h>

#include "settings.hpp"
#include "body.hpp"
#include "utils.hpp"


int main(int argc, char *argv[]) {
	parseArgs(argc, argv);
	srand(time(0));

	SDL_Window* window = SDL_CreateWindow(
		"nBodies",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		W, H,
		SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_Log("SDL_CreateWindow creation failed: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

    SDL_Renderer* renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_Log("SDL_CreateRenderer creation failed: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(SDL_Init(SDL_INIT_EVERYTHING)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

   SDL_Surface *surface = SDL_CreateRGBSurface(0, W, H, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (!surface) {
        std::cerr << "Surface creation failed: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

	SDL_Texture *surfTexture;


	const float fac = .4f;
	Body *balls = new Body[N_BALLS];

	for (int i=0; i<N_BALLS; i++) {
		balls[i] = Body(Vec(lerp(-SCALE*fac, SCALE*fac, randF), lerp(-SCALE*fac, SCALE*fac, randF)), lerp(MIN_MASS, MAX_MASS, randF));
		
		if (balls[i].pos.y > 0){
			balls[i].vel = glm::normalize(Vec(lerp(0, 1, randF), lerp(-.2, 0, randF)) ) * BALL_VEL;
		}else{
			balls[i].vel = glm::normalize(Vec(lerp(-1, 0, randF), lerp(0, .2, randF))) * BALL_VEL;
		}
	}

	auto bkgCol = ColToU32(Color(.05f));

	Vec foA;
	Body *ball1, *ball2;
	float dist;

	uint64_t frames = 0;
	float idealFrameTimeMS = 1000.f/FPS, realFrameTimeMS, waitFrameTimeMS;
	float delta_time = 0.f;

	SDL_Event event;
	bool isRunning = true;

	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = t1;
	float timeSinceLastLog = 0.f;

	while (isRunning) {
		t2 = std::chrono::high_resolution_clock::now();
		delta_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		t1 = std::chrono::high_resolution_clock::now();
		
		handleEvents(&event, &isRunning);

		// Physics
		// Gravitation
		for (int i=0; i<N_BALLS; i++) {
			ball1 = &balls[i];
				for (int j=0; j<N_BALLS; j++) {
				ball2 = &balls[j];
				
				if (i!=j) {

					dist = (ball2->pos - ball1->pos).length();
					foA = glm::normalize(ball2->pos - ball1->pos) * ( (G_CONST *ball1->mass *ball2->mass)/(dist*dist) );

					ball1->applyForce(foA);
				}
			}
		}

		for (int i=0; i<N_BALLS; i++) {
			balls[i].update( delta_time/1E6F );
		}
		


		// Rendering
		// SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
		// SDL_RenderClear(renderer);
        SDL_FillRect(surface, nullptr, bkgCol);

		if (DRAW_TRAILS) {
			for (int i=0; i<N_BALLS; i++) {
				balls[i].renderTrails(surface);
			}
		}

		for (int i=0; i<N_BALLS; i++) {
			balls[i].show(surface);
		}

		surfTexture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_RenderCopy(renderer, surfTexture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_DestroyTexture(surfTexture);
		frames++;


		realFrameTimeMS = delta_time / 1000.f;
		waitFrameTimeMS = 0.f;

		if (realFrameTimeMS < idealFrameTimeMS) {
			waitFrameTimeMS = idealFrameTimeMS - realFrameTimeMS;
			SDL_Delay( waitFrameTimeMS );
		}

		timeSinceLastLog += realFrameTimeMS;
		if (timeSinceLastLog > (UPDATE_TIME*1000.f) ) {
			timeSinceLastLog = 0.f;
			printf("FPS: %3.2f \t dt: %3.6f ms\n", (1000 / (realFrameTimeMS+waitFrameTimeMS)), realFrameTimeMS);
		}

	}

	std::cout << '\n';

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
