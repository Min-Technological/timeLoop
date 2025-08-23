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
            create_tile(pixelColor, static_cast<float>(x), static_cast<float>(y), index);
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

    enum ObjectType {
        OBJECT_TILE,
        OBJECT_TAROT
    };
    ObjectType objectType;
    Tile::TileType type;
    int tarotType;

    // === Air ===
    if (R == 0xff && G == 0xff && B == 0xff) {
        // White = no tile
        return;
    }

    // === Terrain ===
    else if (G == 0 && B == 0) {
        if (R == 0xCF && G == 0x00 && B == 0x00) {
            objectType = OBJECT_TILE;
            type = Tile::TileType::DIRT_DARK;
        }
        else if (R == 0xDF && G == 0x00 && B == 0x00) {
            objectType = OBJECT_TILE;
            type = Tile::TileType::DIRT_LIGHT;
        }
        else if (R == 0xEF && G == 0x00 && B == 0x00) {
            objectType = OBJECT_TILE;
            type = Tile::TileType::GRASS_DARK;
        }
        else if (R == 0xFF && G == 0x00 && B == 0x00) {
            objectType = OBJECT_TILE;
            type = Tile::TileType::GRASS_LIGHT;
        }
    }

    // === Tarot Cards ===
    else if (R == B) {
        objectType = OBJECT_TAROT;
        if (R == 0xFF && G == 0x00 && B == 0xFF) {
            tarotType = 0; // FOOL
            // std::cout << "FOOL!\n";
        }
        else if (R == 0xF4 && G == 0x00 && B == 0xF4) {
            tarotType = 1; // MAGICIAN
            // std::cout << "MAGICIAN!\n";
        }
        else if (R == 0xE9 && G == 0x00 && B == 0xE9) {
            tarotType = 2; // HIGH PRIESTESS
            // std::cout << "HIGH PRIESTESS!\n";
        }
        else if (R == 0xDE && G == 0x00 && B == 0xDE) {
            tarotType = 3; // EMPRESS
            // std::cout << "EMPRESS!\n";
        }
        else if (R == 0xD3 && G == 0x00 && B == 0xD3) {
            tarotType = 4; // EMPEROR
            // std::cout << "EMPEROR!\n";
        }
        else if (R == 0xC8 && G == 0x00 && B == 0xC8) {
            tarotType = 5; // HIGH PRIEST
            // std::cout << "HIGH PRIEST!\n";
        }
        else if (R == 0xBD && G == 0x00 && B == 0xBD) {
            tarotType = 6; // LOVERS
            // std::cout << "LOVERS!\n";
        }
        else if (R == 0xB2 && G == 0x00 && B == 0xB2) {
            tarotType = 7; // CHARIOT
            // std::cout << "CHARIOT!\n";
        }
        else if (R == 0xA7 && G == 0x00 && B == 0xA7) {
            tarotType = 8; // STRENGTH
            // std::cout << "STRENGTH!\n";
        }
        else if (R == 0x9C && G == 0x00 && B == 0x9C) {
            tarotType = 9; // HERMIT
            // std::cout << "HERMIT!\n";
        }
        else if (R == 0x91 && G == 0x00 && B == 0x91) {
            tarotType = 10; // WHEEL OF FORTUNE
            // std::cout << "WHEEL OF FORTUNE!\n";
        }
        else if (R == 0x86 && G == 0x00 && B == 0x86) {
            tarotType = 11; // JUSTICE
            // std::cout << "JUSTICE!\n";
        }
        else if (R == 0x7B && G == 0x00 && B == 0x7B) {
            tarotType = 12; // HANGED MAN
            // std::cout << "HANGED MAN!\n";
        }
        else if (R == 0x70 && G == 0x00 && B == 0x70) {
            tarotType = 13; // DEATH
            // std::cout << "DEATH!\n";
        }
        else if (R == 0x65 && G == 0x00 && B == 0x65) {
            tarotType = 14; // TEMPERANCE
            // std::cout << "TEMPERANCE!\n";
        }
        else if (R == 0x5A && G == 0x00 && B == 0x5A) {
            tarotType = 15; // DEVIL
            // std::cout << "DEVIL!\n";
        }
        else if (R == 0x4F && G == 0x00 && B == 0x4F) {
            tarotType = 16; // TOWER
            // std::cout << "TOWER!\n";
        }
        else if (R == 0x44 && G == 0x00 && B == 0x44) {
            tarotType = 17; // STAR
            // std::cout << "STAR!\n";
        }
        else if (R == 0x39 && G == 0x00 && B == 0x39) {
            tarotType = 18; // MOON
            // std::cout << "MOON!\n";
        }
        else if (R == 0x2E && G == 0x00 && B == 0x2E) {
            tarotType = 19; // SUN
            // std::cout << "SUN!\n";
        }
        else if (R == 0x23 && G == 0x00 && B == 0x23) {
            tarotType = 20; // JUDGEMENT
            // std::cout << "JUDGEMENT!\n";
        }
        else if (R == 0x18 && G == 0x00 && B == 0x18) {
            tarotType = 21; // WORLD
            // std::cout << "WORLD!\n";
        }

    }

    // === Worst Case Scenario ===
    else {
        objectType = OBJECT_TILE;
        type = Tile::TileType::NILL;
    }

    switch (objectType) {
    case OBJECT_TILE:
        map[mapIndex].append(type, x * tileSize, y * tileSize, appWindow.get_renderer());
        break;
    case OBJECT_TAROT:
        map[mapIndex].add_cards(tarotType, x * tileSize, y * tileSize, appWindow);
        break;
    default:
        break;


    }
}
