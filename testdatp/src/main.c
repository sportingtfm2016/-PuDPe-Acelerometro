#include <pebble.h>

//Ventana
static Window *s_main_window;
//Texto
static TextLayer *duracion;
static TextLayer *km;

static TextLayer *ex;
static TextLayer *ey;
static TextLayer *ez;

static char duration[8];

static char ax[8];
static char ay[8];
static char az[8];

int i = 0;
static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  snprintf(duration, sizeof(duration), "%d", i);
  snprintf(ax, sizeof(ax), "%d", i);
  snprintf(ay, sizeof(ay), "%d", i);
  snprintf(az, sizeof(az), "%d", i);
  // Create the TextLayer with specific bounds
  duracion = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
    km = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(80, 80), bounds.size.w, 50));
  ex = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(90, 90), bounds.size.w, 50));
  ey = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(100, 100), bounds.size.w, 50));
  ez = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(110, 110), bounds.size.w, 50));
  
  // Improve the layout to be more like a watchface
  text_layer_set_background_color(duracion, GColorClear);
  text_layer_set_text_color(duracion, GColorBlack);
  text_layer_set_text(duracion, duration);
  text_layer_set_font(duracion, fonts_get_system_font(FONT_KEY_GOTHIC_09));
  text_layer_set_text_alignment(duracion, GTextAlignmentCenter);
    
  // Improve the layout to be more like a watchface
  text_layer_set_background_color(km, GColorClear);
  text_layer_set_text_color(km, GColorBlack);
  text_layer_set_text(km, duration);
  text_layer_set_font(km, fonts_get_system_font(FONT_KEY_GOTHIC_09));
  text_layer_set_text_alignment(km, GTextAlignmentLeft);
  
  // Improve the layout to be more like a watchface
  text_layer_set_background_color(ex, GColorClear);
  text_layer_set_text_color(ex, GColorBlack);
  text_layer_set_text(ex, duration);
  text_layer_set_font(ex, fonts_get_system_font(FONT_KEY_GOTHIC_09));
  text_layer_set_text_alignment(ex, GTextAlignmentCenter);
    // Improve the layout to be more like a watchface
  text_layer_set_background_color(ey, GColorClear);
  text_layer_set_text_color(ey, GColorBlack);
  text_layer_set_text(ey, duration);
  text_layer_set_font(ey, fonts_get_system_font(FONT_KEY_GOTHIC_09));
  text_layer_set_text_alignment(ey, GTextAlignmentLeft);
    // Improve the layout to be more like a watchface
  text_layer_set_background_color(ez, GColorClear);
  text_layer_set_text_color(ez, GColorBlack);
  text_layer_set_text(ez, duration);
  text_layer_set_font(ez, fonts_get_system_font(FONT_KEY_GOTHIC_09));
  text_layer_set_text_alignment(ez, GTextAlignmentCenter);
  

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(duracion));
  layer_add_child(window_layer, text_layer_get_layer(km));
  layer_add_child(window_layer, text_layer_get_layer(ex));
  layer_add_child(window_layer, text_layer_get_layer(ey));
  layer_add_child(window_layer, text_layer_get_layer(ez));
}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(duracion);
  text_layer_destroy(km);
  text_layer_destroy(ex);
  text_layer_destroy(ey);
  text_layer_destroy(ez);
}

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(duracion, s_buffer);
}

static void test1() {
  // Get a tm structure
  static char s_buffer[8];
  i++;
  snprintf(s_buffer, sizeof(s_buffer), "%d", i);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Loop index now %s", s_buffer);
    text_layer_set_text(duracion, s_buffer);
  
  snprintf(s_buffer, sizeof(s_buffer), "%d", i+100);
  text_layer_set_text(km, s_buffer);
  
  // Display this time on the TextLayer
}

static void accel_data_handler(AccelData *data, uint32_t num_samples) {
  // Read sample 0's x, y, and z values
  int16_t x = data[0].x;
  int16_t y = data[0].y;
  int16_t z = data[0].z;

  // Determine if the sample occured during vibration, and when it occured
  bool did_vibrate = data[0].did_vibrate;
  long unsigned timestamp = data[0].timestamp;

  if(!did_vibrate) {
    // Print it out
    APP_LOG(APP_LOG_LEVEL_INFO, "t: %lu , x: %d, y: %d, z: %d",timestamp, x, y, z);
     snprintf(ax, sizeof(ax), "%d", x);
      text_layer_set_text(ex, ax);
         snprintf(ay, sizeof(ay), "%d", y);
      text_layer_set_text(ey, ay);
         snprintf(az, sizeof(az), "%d", z);
      text_layer_set_text(ez, az);
  } else {
    // Discard with a warning
    APP_LOG(APP_LOG_LEVEL_WARNING, "Vibration occured during collection");
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
test1();
}


static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  // Make sure the time is displayed from the start
test1();
  
  accel_data_service_subscribe(3, accel_data_handler);
  // Register with TickTimerService
tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}