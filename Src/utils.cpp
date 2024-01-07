#include "utils.hpp"

void drawCircle(SDL_Surface *surf, Vec pos, int rad, uint32_t color) {
    uint32_t *Buffer = (uint32_t *)(surf->pixels);

    int xSt = glm::max(0, glm::min(W, int(pos.x-rad) ) );
    int xEn = glm::max(0, glm::min(W, int(pos.x+rad+1) ) );
    int ySt = glm::max(0, glm::min(H, int(pos.y-rad) ) );
    int yEn = glm::max(0, glm::min(H, int(pos.y+rad+1) ) );

    float dist_sq;

    for (int py=ySt; py<yEn; py++){
        for (int px=xSt; px<xEn; px++) {

            dist_sq = (px-pos.x)*(px-pos.x) + (py-pos.y)*(py-pos.y);
            if ( dist_sq <= (rad*rad) ) Buffer[py*W + px] = color;

        }
    }
}


void drawStarPoint(SDL_Surface *surf, Vec pos, uint32_t color) {
    uint32_t *Buffer = (uint32_t *)(surf->pixels);

    uint32_t idx0 = glm::min((uint32_t)W*H, glm::max(0U, uint32_t(pos.y)*W + uint32_t(pos.x)));

    uint32_t idx1 = glm::min((uint32_t)W*H, glm::max(0U, uint32_t(pos.y)*W + uint32_t(pos.x-1)));
    uint32_t idx2 = glm::min((uint32_t)W*H, glm::max(0U, uint32_t(pos.y)*W + uint32_t(pos.x+1)));
    uint32_t idx3 = glm::min((uint32_t)W*H, glm::max(0U, uint32_t(pos.y+1)*W + uint32_t(pos.x)));
    uint32_t idx4 = glm::min((uint32_t)W*H, glm::max(0U, uint32_t(pos.y-1)*W + uint32_t(pos.x)));

    Buffer[idx0] = color;
    Buffer[idx1] = color;
    Buffer[idx2] = color;
    Buffer[idx3] = color;
    Buffer[idx4] = color;
}



void parseArgs(int nArgs, char *args[]) {
	if (nArgs > 1) {
		for (int i=0; i<nArgs; i++) {
			std::cout << args[i] << '\n';
		}
	}
}

void handleEvents(SDL_Event *event, bool *isRunning) {
	while (SDL_PollEvent(event)) {
		if (event->type == SDL_QUIT) {
			*isRunning = false;
		}
	}
}
