#include <Arduino.h>  // Arduino-specific library

// Pin Definitions
const int pulsePin = A0;  // Analog pin where the pulse sensor is connected
const int threshold = 500; // Threshold to detect a pulse (adjust based on sensor)
unsigned long lastBeatTime = 0; // Time of the last detected beat

// Variables for BPM calculation
int BPM = 0;                // Beats Per Minute
int beatCount = 0;          // Number of beats detected
unsigned long startTime = 0; // Start time for BPM calculation
const int sampleWindow = 10000; // 10-second window for BPM calculation

void setup() {
    Serial.begin(9600);  // Initialize serial communication
    pinMode(pulsePin, INPUT);  // Set pulsePin as an input
    Serial.println("Pulse Sensor BPM Monitor");
}

void loop() {
    // Read the analog value from the pulse sensor
    int pulseValue = analogRead(pulsePin);
    
    // Detect a pulse
    if (pulseValue > threshold) {
        unsigned long currentTime = millis();  // Current time in milliseconds
        
        // Ensure it's not a false positive (debouncing)
        if (currentTime - lastBeatTime > 300) {  // Minimum 300ms between beats (~200 BPM max)
            lastBeatTime = currentTime;
            beatCount++;
        }
    }
    
    // Calculate BPM every 10 seconds
    if (millis() - startTime >= sampleWindow) {
        // Calculate BPM: (beats / sample time in seconds) * 60
        BPM = (beatCount / (sampleWindow / 1000.0)) * 60;
        
        // Print BPM to Serial Monitor
        Serial.print("BPM: ");
        Serial.println(BPM);
        
        // Reset variables for next window
        beatCount = 0;
        startTime = millis();
    }

    delay(10);  // Small delay for stability
}

