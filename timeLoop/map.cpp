#include "Map.h"

// === Constructor ===
Map::Map(const std::string& path, int tileWidth, AppWindow window, Camera& windowCamera, float& scale, float& depth) :
    mapPath(path), 
    tileSize(tileWidth), 
    appWindow(window), 
    r(window.get_renderer()), 
    camera(windowCamera), 
    tempScale(scale), 
    depthValue(depth) {
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
            map.emplace_back(40.0f * x, appWindow, tempScale, depthValue);
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
        OBJECT_TAROT,
        TAROT_STATION
    };
    ObjectType objectType = OBJECT_TAROT;
    Tile::TileType type = Tile::TileType::NILL;
    int tarotType = 0;
    int xPos = static_cast<int>(x);
    int yPos = static_cast<int>(y);

    // === Air ===
    if (R == 0xff && G == 0xff && B == 0xff) {
        // White = no tile
        return;
    }

    // === Terrain ===
    else if (G == 0 && B == 0) {
        if (R == 0xFF && G == 0x00 && B == 0x00) {
            objectType = OBJECT_TILE;
            if (xPos % 2 == yPos % 2) {
                type = Tile::TileType::GRASS_LIGHT;
            }
            else {
                type = Tile::TileType::GRASS_DARK;
            }
        }
        else if (R == 0xEF && G == 0x00 && B == 0x00) {
            objectType = OBJECT_TILE;
            if (xPos % 2 == yPos % 2) {
                type = Tile::TileType::DIRT_LIGHT;
            }
            else {
                type = Tile::TileType::DIRT_DARK;
            }
        }
    }

    // === ORANGE ===
    else if (G == R / 2) {
        objectType = OBJECT_TILE;
        // === Character Swapper (Discontinued) ===
        if (R == 255) {
            type = Tile::TileType::CHARACTERSWAP_PROTAG;
        }
        else if (R == 245) {
            type = Tile::TileType::CHARACTERSWAP_WAND;
        }
        else if (R == 235) {
            type = Tile::TileType::CHARACTERSWAP_CUP;
        }
        else if (R == 225) {
            type = Tile::TileType::CHARACTERSWAP_SWORD;
        }
        else if (R == 215) {
            type = Tile::TileType::CHARACTERSWAP_PENTACLE;
        }
    }

    // === Tarot Cards ===
    else if (R == B) {
        if (G == 0x00 && R >= 0xEA) {
            objectType = OBJECT_TAROT;
            if (R == 0xFF) {
                tarotType = 0; // FOOL
                // std::cout << "FOOL!\n";
            }
            else if (R == 0xFE) {
                tarotType = 1; // MAGICIAN
                // std::cout << "MAGICIAN!\n";
            }
            else if (R == 0xFD) {
                tarotType = 2; // HIGH PRIESTESS
                // std::cout << "HIGH PRIESTESS!\n";
            }
            else if (R == 0xFC) {
                tarotType = 3; // EMPRESS
                // std::cout << "EMPRESS!\n";
            }
            else if (R == 0xFB) {
                tarotType = 4; // EMPEROR
                // std::cout << "EMPEROR!\n";
            }
            else if (R == 0xFA) {
                tarotType = 5; // HIGH PRIEST
                // std::cout << "HIGH PRIEST!\n";
            }
            else if (R == 0xF9) {
                tarotType = 6; // LOVERS
                // std::cout << "LOVERS!\n";
            }
            else if (R == 0xF8) {
                tarotType = 7; // CHARIOT
                // std::cout << "CHARIOT!\n";
            }
            else if (R == 0xF7) {
                tarotType = 8; // STRENGTH
                // std::cout << "STRENGTH!\n";
            }
            else if (R == 0xF6) {
                tarotType = 9; // HERMIT
                // std::cout << "HERMIT!\n";
            }
            else if (R == 0xF5) {
                tarotType = 10; // WHEEL OF FORTUNE
                // std::cout << "WHEEL OF FORTUNE!\n";
            }
            else if (R == 0xF4) {
                tarotType = 11; // JUSTICE
                // std::cout << "JUSTICE!\n";
            }
            else if (R == 0xF3) {
                tarotType = 12; // HANGED MAN
                // std::cout << "HANGED MAN!\n";
            }
            else if (R == 0xF2) {
                tarotType = 13; // DEATH
                // std::cout << "DEATH!\n";
            }
            else if (R == 0xF1) {
                tarotType = 14; // TEMPERANCE
                // std::cout << "TEMPERANCE!\n";
            }
            else if (R == 0xF0) {
                tarotType = 15; // DEVIL
                // std::cout << "DEVIL!\n";
            }
            else if (R == 0xEF) {
                tarotType = 16; // TOWER
                // std::cout << "TOWER!\n";
            }
            else if (R == 0xEE) {
                tarotType = 17; // STAR
                // std::cout << "STAR!\n";
            }
            else if (R == 0xED) {
                tarotType = 18; // MOON
                // std::cout << "MOON!\n";
            }
            else if (R == 0xEC) {
                tarotType = 19; // SUN
                // std::cout << "SUN!\n";
            }
            else if (R == 0xEB) {
                tarotType = 20; // JUDGEMENT
                // std::cout << "JUDGEMENT!\n";
            }
            else if (R == 0xEA) {
                tarotType = 21; // WORLD
                // std::cout << "WORLD!\n";
            }
        }
        else if (R == 0xE9) {
            objectType = TAROT_STATION;

        }

    }

    // === Worst Case Scenario ===
    else {
        objectType = OBJECT_TILE;
        type = Tile::TileType::NILL;
    }

    switch (objectType) {
    case OBJECT_TILE:
        map[mapIndex].append(type, x * tileSize, y * tileSize, appWindow.get_renderer(), tempScale);
        break;
    case OBJECT_TAROT:
        map[mapIndex].add_cards(tarotType, x * tileSize, y * tileSize, appWindow, tempScale);
        break;
    case TAROT_STATION:
        std::cout << "NOT DEVELOPED YET!\n";
        break;
    default:
        break;


    }
}
