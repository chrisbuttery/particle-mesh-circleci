int displayMessage(String command) {
    Mesh.publish("matrix_display_message", command);
    digitalWrite(D7, HIGH);
    delay(1000);
    digitalWrite(D7, LOW);
}

void setup() {
    pinMode(D7, OUTPUT);
    Particle.function("display_broken_build", displayMessage);
}

void loop() {}