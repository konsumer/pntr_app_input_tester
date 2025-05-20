#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_VARGS
#define PNTR_ENABLE_TTF
#define PNTR_ENABLE_UTF8
#define PNTR_ENABLE_MATH
#define PNTR_ENABLE_JPEG
#define PNTR_PIXELFORMAT_RGBA

#include "pntr_app.h"

// these are approximations of cart functions

pntr_image* images[16];
pntr_image* bg;

bool buttons[] = {
  false,
  false, // GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
  false, // GAMEPAD_BUTTON_RIGHT,           // Gamepad left DPAD right button
  false, // GAMEPAD_BUTTON_DOWN,            // Gamepad left DPAD down button
  false, // GAMEPAD_BUTTON_LEFT,            // Gamepad left DPAD left button
  false, // GAMEPAD_BUTTON_Y,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  false, // GAMEPAD_BUTTON_B,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
  false, // GAMEPAD_BUTTON_A,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  false, // GAMEPAD_BUTTON_X,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
  false, // GAMEPAD_BUTTON_LEFT_SHOULDER,   // Gamepad top/back trigger left (first), it could be a trailing button
  false, // GAMEPAD_BUTTON_LEFT_TRIGGER,    // Gamepad top/back trigger left (second), it could be a trailing button
  false, // GAMEPAD_BUTTON_RIGHT_SHOULDER,  // Gamepad top/back trigger right (one), it could be a trailing button
  false, // GAMEPAD_BUTTON_RIGHT_TRIGGER,   // Gamepad top/back trigger right (second), it could be a trailing button
  false, // GAMEPAD_BUTTON_SELECT,          // Gamepad center buttons, left one (i.e. PS3: Select)
  false, // GAMEPAD_BUTTON_MENU,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  false, // GAMEPAD_BUTTON_START,           // Gamepad center buttons, right one (i.e. PS3: Start)
  false, // GAMEPAD_BUTTON_LEFT_THUMB,      // Gamepad joystick pressed button left
  false, // GAMEPAD_BUTTON_RIGHT_THUMB,     // Gamepad joystick pressed button right
};

// called on load, you can also use main()
void cart_load() {
  images[0] = pntr_load_image("assets/bg.png");
  images[1] = pntr_load_image("assets/up.png");
  images[2] = pntr_load_image("assets/right.png");
  images[3] = pntr_load_image("assets/down.png");
  images[4] = pntr_load_image("assets/left.png");
  images[5] = pntr_load_image("assets/y.png");
  images[6] = pntr_load_image("assets/b.png");
  images[7] = pntr_load_image("assets/a.png");
  images[8] = pntr_load_image("assets/x.png");
  images[9] = pntr_load_image("assets/l1.png");
  images[11] = pntr_load_image("assets/r1.png");
  images[13] = pntr_load_image("assets/select.png");
  images[15] = pntr_load_image("assets/start.png");

  bg = pntr_gen_image_gradient(640, 480, PNTR_BLUE, PNTR_BLUE, PNTR_GREEN, PNTR_GREEN);
}

// mapped controller callback
void cart_buttonUp(unsigned int button, unsigned int player) {
  buttons[(int)button] = false;
}

// mapped controller callback
void cart_buttonDown(pntr_app_gamepad_button button, unsigned int player) {
  buttons[(int)button] = true;
}

// called on every frame
void cart_update(pntr_image *screen) {
  pntr_draw_image(screen, bg, 0, 0);
  pntr_draw_image_scaled(screen, images[0], 0, 94, 2, 2, 0, 0, PNTR_FILTER_NEARESTNEIGHBOR);

  for (int i = 1; i < 16; i++) {
    if (buttons[i]) {
      pntr_draw_image_scaled(screen, images[i], 0, 0, 2, 2, 0, 0, PNTR_FILTER_NEARESTNEIGHBOR);
    }
  }
}


// these aren't used in demo

// called when keys are unpressed
void cart_keyUp(pntr_app_key key) {}

// called when keys are pressed
void cart_keyDown(pntr_app_key key) {}

// called when mouse-button is pressed
void cart_mouseDown(unsigned int button) {}

// called when mouse-button is released
void cart_mouseUp(unsigned int button) {}

// called when mouse is moved
void cart_mouseMoved(float x, float y) {}

// called when cart is unloaded
void cart_unload() {}

// HOST.C STUFF - currently in null0's host implementation

// this maps keys to joystick buttons (for non-libretro)
static pntr_app_gamepad_button cart_map_key(pntr_app_key key) {
  switch (key) {
  case PNTR_APP_KEY_UP:
    return PNTR_APP_GAMEPAD_BUTTON_UP;
  case PNTR_APP_KEY_DOWN:
    return PNTR_APP_GAMEPAD_BUTTON_DOWN;
  case PNTR_APP_KEY_LEFT:
    return PNTR_APP_GAMEPAD_BUTTON_LEFT;
  case PNTR_APP_KEY_RIGHT:
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT;
  case PNTR_APP_KEY_Q:
    return PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER;
  case PNTR_APP_KEY_W:
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER;
  case PNTR_APP_KEY_Z:
    return PNTR_APP_GAMEPAD_BUTTON_B;
  case PNTR_APP_KEY_X:
    return PNTR_APP_GAMEPAD_BUTTON_A;
  case PNTR_APP_KEY_A:
    return PNTR_APP_GAMEPAD_BUTTON_Y;
  case PNTR_APP_KEY_S:
    return PNTR_APP_GAMEPAD_BUTTON_X;
  case PNTR_APP_KEY_LEFT_SHIFT:
    return PNTR_APP_GAMEPAD_BUTTON_SELECT;
  case PNTR_APP_KEY_RIGHT_SHIFT:
    return PNTR_APP_GAMEPAD_BUTTON_SELECT;
  case PNTR_APP_KEY_ENTER:
    return PNTR_APP_GAMEPAD_BUTTON_START;
  default:
    return PNTR_APP_GAMEPAD_BUTTON_UNKNOWN;
  }
}

void cart_event(pntr_app_event *event) {
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN) {
    cart_mouseDown(event->mouseButton);
  }
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP) {
    cart_mouseUp(event->mouseButton);
  }
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_MOVE) {
    cart_mouseMoved(event->mouseX, event->mouseY);
  }
  if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN) {
    cart_buttonDown(event->gamepadButton, event->gamepad);
  }
  if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP) {
    cart_buttonUp(event->gamepadButton, event->gamepad);
  }

  // these are fired & also mapped to button-events
  if (event->type == PNTR_APP_EVENTTYPE_KEY_DOWN) {
    cart_keyDown(event->key);
#ifndef PNTR_APP_LIBRETRO
    pntr_app_gamepad_button b = cart_map_key(event->key);
    if (b != PNTR_APP_GAMEPAD_BUTTON_UNKNOWN) {
      cart_buttonDown(b, 9999);
    }
#endif
  }
  if (event->type == PNTR_APP_EVENTTYPE_KEY_UP) {
    cart_keyUp(event->key);
#ifndef PNTR_APP_LIBRETRO
    pntr_app_gamepad_button b = cart_map_key(event->key);
    if (b != PNTR_APP_GAMEPAD_BUTTON_UNKNOWN) {
      cart_buttonUp(b, 9999);
    }
#endif
  }
}


bool Init(pntr_app *app) {
  cart_load();
  return true;
}

bool Update(pntr_app *app, pntr_image *screen) {
  cart_update(screen);
  return true;
}

void Event(pntr_app *app, pntr_app_event *event) {
  cart_event(event);
}

void Close(pntr_app *app) {
  cart_unload();
}

pntr_app Main(int argc, char *argv[]) {
#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_WARNING);
#endif
  return (pntr_app){
    .width = 640,
    .height = 480,
    .title = "pntr_app_input_tester",
    .init = Init,
    .update = Update,
    .event = Event,
    .close = Close,
    .fps = 60};
}
