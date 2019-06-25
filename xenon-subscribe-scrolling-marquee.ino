
/// This #include statement was automatically added by the Particle IDE.
#include <ledmatrix-max7219-max7221.h>

LEDMatrix *led;

String message = "";
int speakerPin = D3;
int bitmapWidth = 32;
int webcount = 60001;
int iterationCount = 2;
int textX = bitmapWidth;
int fontWidth = 5, space = 1;

/*
 * drawText
 * Draw each char to LED
 */
void drawText(String s, int x)
{
    int y = 0;
    for(int i = 0; i < s.length(); i++) {
        Serial.println(s[i]);  
        led->drawChar(x + i*(fontWidth+space), y, s[i], true, false, 1);
    }
}

/*
 * createDisplay
 * Create the LED
 */
void createDisplay() {
    led = new LEDMatrix(4, 1, D0, D1, D2);
    led->addMatrix(3, 0, 0, false, false);
    led->addMatrix(2, 0, 0, false, false);
    led->addMatrix(1, 0, 0, false, false);
    led->addMatrix(0, 0, 0, false, false);
    textX = bitmapWidth;
}

/*
 * killDisplay
 * Tear down the LED
 */
void killDisplay() {
    led->shutdown(true);
    delete led;
    led = NULL;
    iterationCount = 2;
}

/*
 * displayMessage
 * take a String param, kill any existing display, sound peizo and reset iterationCount
 */
void displayMessage(const char *event, const char *data) {
    killDisplay();
    createDisplay();
    tone(speakerPin, 301, 1000);
    message = data;
    Serial.println(message);
    iterationCount = 0;
}

/*
 * setup
 * enable serial logging + create LED
 * Listen for 'matrix_display_message' and fire off to displayMessage
 */
void setup() {
    Serial.begin(9600);
    createDisplay();
    // on 'matrix_display_message' call display_message
    Mesh.subscribe("matrix_display_message", displayMessage);
}

void loop() {
    if(iterationCount < 2 && message != "") {
        drawText(message, textX--);
        
        int length = message.length();
        if(textX < length*(fontWidth+space)*(-1) ) {
            textX = bitmapWidth;
            led->flush();
            delay(333);
            led->fillScreen(false);
            iterationCount++;
        }
    
        led->flush();
        delay(50);
    } else {
        iterationCount = 2;
        message = "";
    }
}