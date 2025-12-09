#include "Renderer.h"

Renderer::Renderer(SDL_Renderer* r, float X, float Y, float W, float H, float& s, float& depth) :
	renderer(r), viewport( { X, Y, W, H } ), scale(s), cameraDepth(depth) {
}



void Renderer::load_texture(const std::string &path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface) {
		std::cout << "UNABLE TO LOAD IMAGE! " << SDL_GetError() << std::endl;
		return;
	}

	texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (!texture) {
		std::cout << "UNABLE TO CREATE TEXTURE FROM: " << SDL_GetError() << std::endl;
	}
	else {
		scaledTexture = texture;
		SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
		SDL_SetTextureScaleMode(scaledTexture, SDL_SCALEMODE_NEAREST);
	}



	SDL_DestroySurface(loadedSurface);
}

void Renderer::new_position(float newX, float newY, float newW, float newH, float xOff, float yOff) {
	xOffset = xOff;
	yOffset = yOff;

	viewport.x = cameraDepth.scale_value((newX - xOffset) * scale);
	viewport.y = cameraDepth.scale_value((newY - yOffset) * scale);
	viewport.w = cameraDepth.scale_value(newW * scale);
	viewport.h = cameraDepth.scale_value(newH * scale);
}
void Renderer::rescale() {



	SDL_Surface* originalSurface = nullptr;
	void* pixels = nullptr;
	int pitch = 0;

	if (SDL_LockTextureToSurface(texture, nullptr, &originalSurface) < 0) {
		std::cout << "Failed to lock texture to surface: " << SDL_GetError() << "\n";
		return;
	}

	// 2. Create the scaled surface

	SDL_Surface* scaledSurface = SDL_CreateSurface(1920 * scale, 1080 * scale, SDL_PIXELFORMAT_RGBA32);

	if (!scaledSurface) {
		SDL_UnlockTexture(texture);
		std::cout << "Failed to create scaled surface: " << SDL_GetError() << "\n";
		return;
	}

	std::cout << "3\n";
	// 3. Blit (copy + scale) originalSurface to scaledSurface

	SDL_Rect source{ 0, 0, originalSurface->w, originalSurface->h };
	SDL_Rect scaled{ 0, 0, 1920 * scale, 1080 * scale };

	if (SDL_BlitSurfaceScaled(originalSurface, &source, scaledSurface, &scaled, SDL_SCALEMODE_LINEAR) < 0) {
		std::cout << "Scaled blit failed: " << SDL_GetError() << "\n";
		SDL_UnlockTexture(texture);
		SDL_DestroySurface(scaledSurface);
		return;
	}

	std::cout << "4\n";
	// 4. Unlock the original texture

	SDL_UnlockTexture(texture);

	std::cout << "5\n";
	// 5. Convert scaled surface to new GPU texture

	scaledTexture = nullptr;
	scaledTexture = SDL_CreateTextureFromSurface(renderer, scaledSurface);
}
void Renderer::set_x_offset(float xOff) {
	xOffset = xOff;
}
void Renderer::set_y_offset(float yOff) {
	yOffset = yOff;
}

void Renderer::render_colour(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
	if (cameraDepth.get_depth() <= 0) return;

	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderFillRect(renderer, &viewport);
}
void Renderer::render_texture() {
	if (cameraDepth.get_depth() <= 0) return;


	SDL_RenderTexture(renderer, scaledTexture, NULL, &viewport);
}
void Renderer::render_sprite(float x, float y, float w, float h) {
	if (cameraDepth.get_depth() <= 0) return;


	SDL_FRect sprite = { x, y, w, h };

	SDL_RenderTexture(renderer, texture, &sprite, &viewport);
}
void Renderer::render_hitbox(float xa, float ya, float xb, float yb, Uint8 green) {
	if (cameraDepth.get_depth() <= 0) return;



	float width = xb - xa;
	float height = yb - ya;
	SDL_FRect bounding = {
		cameraDepth.scale_value((xa - xOffset) * scale),
		cameraDepth.scale_value((ya - yOffset) * scale),
		cameraDepth.scale_value(width * scale),
		cameraDepth.scale_value(height * scale)
	};

	SDL_SetRenderDrawColor(renderer, 255, green, 0, 255);
	SDL_RenderRect(renderer, &bounding);
}
void Renderer::render_clickbox(float x, float y, float w, float h, Uint8 green) {
	if (cameraDepth.get_depth() <= 0) return;


	SDL_FRect bounding = {
		(x - xOffset) * scale,
		y * scale,
		w * scale,
		h * scale
	};


	SDL_SetRenderDrawColor(renderer, 0, green, 255, 255);
	SDL_RenderRect(renderer, &bounding);
}

bool Renderer::test_frame(std::vector<float> camera) const {
	if (viewport.x > -viewport.w && viewport.x < camera[0]) {
		if (viewport.y > -viewport.h && viewport.y < camera[1]) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Renderer::destroy_texture() {
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

bool Renderer::has_texture() {
	// return texture == nullptr ? false : true;
	return true;
}
