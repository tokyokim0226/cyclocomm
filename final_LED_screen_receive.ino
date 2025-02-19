#include <FastLED.h>
#include <SoftwareSerial.h>
#define NUM_LEDS 128
#define LED_PIN 7
#define COMMANDS 7
#define RED 16711680
#define GREEN 65280 
#define YELLOW 16776960
#define BLUE 255
#define WHITE 255
const unsigned long wait_time = 1500;

// Create a SoftwareSerial connection for HC-05
SoftwareSerial BTSerial(2, 3); // RX | TX
CRGB leds[NUM_LEDS];
typedef struct{
    long kanji_color;
    const char* kanji;
    long emoji_color[3];
    const char* emoji;
}command;
//16711680, 
const char stop_kanji[] = {
    9, 22, 37, 41, 42, 43, 44, 54, 58, 69, 73, 86, 90, 101,
    105, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124,
    125, 126, -1
};
//16711680, 
const char stop_emoji[] = {
  3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 
  33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 48, 49, 50, 61, 62, 63, 64, 65,
  66, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 98, 99, 100,
  101, 102, 103, 104, 105, 106, 107, 108, 109, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, -1, 
  51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, -1
};
//65280, 
const char right_kanji[] = {
    9, 23, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
    57, 69, 70, 71, 72, 73, 74, 75, 76, 83, 89, 91, 99, 102, 108, 115,
    116, 117, 118, 119, 120, 121, -1
};
//65280, 
const char right_emoji[] = {
    9, 10, 20, 21, 22, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
    43, 44, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 65, 66,
    67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 84, 85, 86, 105, 106, -1
};
//65280, 
const char left_kanji[] = {
    9, 23, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 57,
    69, 70, 71, 72, 73, 74, 87, 91, 99, 104, 115, 116, 117, 118, 119,
    120, 121, 122, 123, -1
};
//65280, 
const char left_emoji[] = {
    5, 6, 25, 26, 27, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
    45, 46, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 67,
    68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 89, 90, 91, 101, 102,
    -1
};
//16711680, 
const char thanks_kanji[] = {
    3, 8, 23, 27, 34, 35, 36, 37, 38, 40, 55, 58, 68, 69, 72,
    83, 87, 89, 90, 92, 101, 104, 108, 116, 117, 118, 122, -1
};
//16776960, 
//0xFFFFFF
const char thanks_emoji[] = {
    4, 5, 6, 7, 8, 9, 10, 11,
    19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    33, 34, 35, 36, 38, 39, 40, 42, 43, 44, 45,
    50, 51, 52, 53, 55, 56, 57, 59, 60, 61, 62,
    65, 67, 68, 69, 70, 71, 72, 73, 74, 75, 77,
    82, 83, 85, 86, 87, 88, 89, 90, 91, 93, 94,
    98, 99, 107, 108, 116, 117, 118, 119, 120, 
    121, 122, 123, 124, -1,
    //37, 42, 53, 58, 66, 77, 83, 92, 100, 101, 102, 103, 104, 105, 106, 107, -1
    41, 54, 84, 76, 106, 37, 58, 105, 104, 103, 102, 101, 100, 92, 66, -1
};
//16711680
//255, 
const char sorry_kanji[] = {
    36, 42, 69, 70, 71, 72, 73, 85, 91, 99, 107, -1
};
//16711680
//255, 
const char sorry_emoji[] = {
    36, 42, 69, 70, 71, 72, 73, 85, 91, 99, 107, -1,
    13, 17, 18, 44, 45, 46, 49, 50, 51, 76, -1
};
//red background
//16711680
const char warning_kanji[] = {
    7, 23, 24, 25, 37, 38, 40, 41, 53, 54, 55, 57,
    58, 59, 67, 68, 69, 70, 72, 73, 74, 75, 83, 84, 85, 86,
    87, 88, 89, 90, 91, 92, 93, 97, 98, 99, 100, 101, 102,
    104, 105, 106, 107, 108, 109, 113, 114, 115, 116, 117,
    118, 119, 120, 121, 122, 123, 124, 125, 126, 127, -1,
    39, 56, 71, 103, -1
};
//yellow background
//16776960
//0xFFFFFF
const char warning_emoji[] = {
    7, 23, 24, 25, 37, 38, 40, 41, 53, 54, 55, 57,
    58, 59, 67, 68, 69, 70, 72, 73, 74, 75, 83, 84, 85, 86,
    87, 88, 89, 90, 91, 92, 93, 97, 98, 99, 100, 101, 102,
    104, 105, 106, 107, 108, 109, 113, 114, 115, 116, 117,
    118, 119, 120, 121, 122, 123, 124, 125, 126, 127, -1,
    39, 56, 71, 103, -1
};

const char heart_kanji[] = {
  3, 4, 5, 10, 11, 12, 18, 19, 20, 21, 22, 25, 26, 27, 28, 
  29, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 51, 
  52, 53, 54, 55, 56, 57, 58, 59, 60, 68, 69, 70, 71, 72, 
  73, 74, 75, 85, 86, 87, 88, 89, 90, 102, 103, 104, 105,
  119, 120, -1
};

const char heart_emoji[] = {102, 103, 104, 86, 87, 88, 89, 90,
 68, 60, 3, 4, 34, 29, 35, 59, 69, 58, 70, 71, 38, 26, 27, 36, 28, 37,
  57, 39, 56, 40, 55, 72, 10, 54, 73, 74, 53, 42, 52, 44, 119, 105, 85,
 75, 25, 18, 12, 5, 51, 45, 120, 20, 43, 19, 11, -1,
108, 109, 110, 82, 114, 62, 65, 64, 94, 66, 21, 41, 23, 22, 9,-1};

const char* serial[COMMANDS] = {"S", "R", "L", "t", "s", "d", "l"};

command stop;
command right;
command left;
command thanks;
command sorry;
command warning;
command heart;

command commands[COMMANDS];

void setup() {
    //initiate commands
    stop.kanji_color = RED;
    stop.kanji = &stop_kanji[0];
    stop.emoji_color[0] = 2;
    stop.emoji_color[1] = RED;
    stop.emoji_color[2] = WHITE;
    stop.emoji = &stop_emoji[0];
    right.kanji_color = GREEN;
    right.kanji = &right_kanji[0];
    right.emoji_color[0] = 1;
    right.emoji_color[1] = GREEN;
    right.emoji = &right_emoji[0];
    left.kanji_color = GREEN;
    left.kanji = &left_kanji[0];
    left.emoji_color[0] = 1;
    left.emoji_color[1] = GREEN;
    left.emoji = &left_emoji[0];
    thanks.kanji_color = RED;
    thanks.kanji = &thanks_kanji[0];
    thanks.emoji_color[0] = 2;
    thanks.emoji_color[1] = YELLOW;
    thanks.emoji_color[2] = WHITE;
    thanks.emoji = &thanks_emoji[0];

    sorry.kanji_color = RED;
    sorry.kanji = &sorry_kanji[0];
    sorry.emoji_color[0] = 2;
    sorry.emoji_color[1] = RED;
    sorry.emoji_color[2] = BLUE;
    sorry.emoji = &sorry_emoji[0];

    warning.kanji_color = YELLOW;
    warning.kanji = &warning_kanji[0];
    warning.emoji_color[0] = 2;
    warning.emoji_color[1] = RED;
    warning.emoji_color[2] = WHITE;
    warning.emoji = &warning_emoji[0];

    heart.kanji_color = RED;
    heart.kanji = &heart_kanji[0];
    heart.emoji_color[0] = 2;
    heart.emoji_color[1] = RED;
    heart.emoji_color[2] = YELLOW;
    heart.emoji = &heart_emoji[0];

    commands[0] = stop;
    commands[1] = right;
    commands[2] = left;
    commands[3] = thanks;
    commands[4] = sorry;
    commands[5] = warning;
    commands[6] = heart;
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
    Serial.begin(9600);
    BTSerial.begin(9600); // Bluetooth module baud rate
    Serial.println("Starting Bluetooth communication...");
    delay(2000);
}
void loop() {
  if (BTSerial.available()){  
      int data = BTSerial.read();

      int i;
      for(i = 0; i < COMMANDS; i++){
          if(*(serial[i]) == data){
            LED_ON(i);
            break;
          }
      }
      FastLED.clear(true);
      
  }   
}

void LED_ON(int command){
  FastLED.clear(true);
  for(int k = 0; k < 2; k++){
    if(commands[command].kanji_color != 0){
      int i = 0;
      for(; (commands[command]).kanji[i] != -1; i++){
        leds[(commands[command]).kanji[i]] = commands[command].kanji_color;
      }
      Serial.print("command = ");
      Serial.println(*(serial[command]));
      if(*(serial[command]) == 'd'){
        Serial.print("hello im here");
        for(i = i + 1; (commands[command]).kanji[i] != -1; i++){
          leds[(commands[command]).kanji[i]] = WHITE;
        }
      }
    FastLED.show();
  unsigned long start_time = millis();
  while(millis()-start_time < wait_time){
    if(BTSerial.available()){
      int data = BTSerial.read();
      for(int i = 0; i < COMMANDS; i++){
          if(*(serial[i]) == data){
            LED_ON(i);
            return;
          }
      }
    }
  }
  FastLED.clear(true); 
  }
    int last = 0;
    int i;
    for(int j = 0; j < (commands[command]).emoji_color[0]; j++){
      for(i = last; (commands[command]).emoji[i] != -1; i++){
        leds[(commands[command]).emoji[i]] = commands[command].emoji_color[j+1];
      }
      last = i + 1;
    }
    FastLED.show();
  unsigned long start_time = millis();
  while(millis()-start_time < wait_time){
    if(BTSerial.available()){
      int data = BTSerial.read();
      int i;
      for(i = 0; i < COMMANDS; i++){
          if(*(serial[i]) == data){
            LED_ON(i);
            return;
          }
      }
    }
  }
    FastLED.clear(true);
  }
}