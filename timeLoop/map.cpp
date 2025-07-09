#include "Map.h"

// === Constructor ===
Map::Map(const std::string& path, int tileWidth, AppWindow window, Camera& windowCamera) :
    mapPath(path), tileSize(tileWidth), appWindow(window), r(window.get_renderer()), camera(windowCamera) {
    s = load_surface();
}

// === Load surface from image file ===
SDL_Surface* Map::load_surface() {
    SDL_Surface* surface = IMG_Load(mapPath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image! " << SDL_GetError() << "\n";
        return nullptr;
    }
    return surface;
}

// === Generate chunks and tiles from surface pixels ===
std::vector<Chunk> Map::generate_map() {
    if (SDL_MUSTLOCK(s)) {
        SDL_LockSurface(s);
    }

    int index = -1;
    Uint32* pixels = (Uint32*)s->pixels;

    for (int x = 0; x < s->w; x++) {
        if (x % 16 == 0) {
            index += 1;
            map.emplace_back(40.0f * x, appWindow);
        }

        for (int y = 0; y < s->h; y++) {
            Uint32 pixelColor = pixels[y * s->w + x];
            create_tile(pixelColor, float(x), float(y), index);
        }
    }

    if (SDL_MUSTLOCK(s)) {
        SDL_UnlockSurface(s);
    }
    SDL_DestroySurface(s);
    s = nullptr;

    return map;
}

// === Create tile based on pixel color and add to map ===
void Map::create_tile(Uint32 color, float x, float y, int mapIndex) {
    const SDL_PixelFormatDetails* fd = SDL_GetPixelFormatDetails(s->format);

    Uint8 R, G, B, A;
    SDL_GetRGBA(color, fd, nullptr, &R, &G, &B, &A);

    Tile::TileType type;

    if (R == 0xff && G == 0xff && B == 0xff) {
        // White = no tile
        return;
    }
    else if (R == 0xff && G == 0x00 && B == 0x00) {
        type = Tile::TileType::DIRT_DARK;
    }
    else if (R == 0xff && G == 0xff && B == 0x00) {
        type = Tile::TileType::DIRT_LIGHT;
    }
    else if (R == 0x00 && G == 0xff && B == 0x00) {
        type = Tile::TileType::GRASS_DARK;
    }
    else if (R == 0x00 && G == 0xff && B == 0xff) {
        type = Tile::TileType::GRASS_LIGHT;
    }
    else {
        type = Tile::TileType::NILL;
    }

    map[mapIndex].append(type, x * tileSize, y * tileSize, appWindow);
}
