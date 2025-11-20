#include "Background.h"

// === Constructor ===
Background::Background(SDL_Renderer* r, float& s, float& depth) : 
    renderer(r, 0, 0, 1920, 1080, s, depth) {}

// === Update ===
void Background::update(int screenW, int screenH, State gameState) {
    renderer.new_position(0, 0, 1920, 1080, 0);
    if (newState != gameState) {
        newState = gameState;
        switch (newState) {
        case State::MENU:
            break;
        case State::GAME:
            break;
        case State::PAUSE:
            break;
        case State::SUICIDE:

            switch (currentPersona) {
            case (Persona::PROTAG):
                renderer.destroy_texture();
                renderer.load_texture("suicideNone.png");

                break;

            case (Persona::CUP):
                renderer.destroy_texture();
                renderer.load_texture("suicidePistol.png");

                break;

            case (Persona::SWORD):
                renderer.destroy_texture();
                renderer.load_texture("suicideNone.png");

                break;

            case (Persona::WAND):
                renderer.destroy_texture();
                renderer.load_texture("suicideShotgun.png");

                break;

            case (Persona::PENTACLE):
                renderer.destroy_texture();
                renderer.load_texture("suicideHammer.png");

                break;

            default:
                std::cout << "Can't select correct Persona Background\n";
            }
            break;
        case State::REWIND:
            break;

        case State::SELECTION:
            break;
        case State::TAROTREADING:
            renderer.destroy_texture();
            renderer.load_texture("tarotBasic.png");
            break;
        case State::TAROTCARDS:
            renderer.destroy_texture();
            renderer.load_texture("tarotSelect.png");
            break;
        default:
            std::cout << "SOMETHING WENT WRONG, BACKGROUND UPDATE\n";
            break;
        }
    }
}

// === Render ===
void Background::render() {
    switch (newState) {
    case State::MENU:
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);

        break;

    case State::GAME:
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);

        break;

    case State::PAUSE:
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);

        break;

    case State::SUICIDE:
        renderer.render_texture();

        break;

    case State::REWIND:
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);

        break;

    case State::SELECTION:
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);

        break;

    case State::TAROTREADING:
        renderer.render_texture();

        break;

    case State::TAROTCARDS:
        renderer.render_texture();

        break;

    default:
        std::cout << "SOMETHING WENT WRONG, BACKGROUND RENDER\n";

        break;
    }

}

void Background::change_persona(Persona newPersona) {
    currentPersona = newPersona;
}
