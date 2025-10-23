#include "Collisions.h"

/*Collisions::CollisionType Collisions::character_collide_with_tiles(Character& character, std::vector<Tile*>& collidedTiles)
{

    for (Tile* tile : collidedTiles) {
        int responseType = tile->get_type();
        if (responseType == 0) continue;

        switch (responseType) {
            // === TERRAIN ===
        case 1: // Dirt Light
        case 2: // Dirt Dark
        case 3: // Grass Light
        case 4: // Grass Dark
            solid_Y_collision(*tile);
            break;
            // === CHARACTER SWAPPER ===
        case 5: // PROTAG
            if (currentPersona != PROTAG) {
                change_persona(PROTAG);
            }
            break;
        case 6: // CUP
            if (currentPersona != CUP) {
                change_persona(CUP);
            }
            break;
        case 7: // SWORD
            if (currentPersona != SWORD) {
                change_persona(SWORD);
            }
            break;
        case 8: // WAND
            if (currentPersona != WAND) {
                change_persona(WAND);
            }
            break;
        case 9: // PENTACLE
            if (currentPersona != PENTACLE) {
                change_persona(PENTACLE);
            }
            break;
        default:
            break;
        }
    }
	// return CollisionType();
}*/

Collisions::CollisionType Collisions::collide_with_tarot(Hitbox& hitbox1, Hitbox& hitbox2, TarotCard::CardNumber cardNumber)
{
	// return CollisionType();
}
