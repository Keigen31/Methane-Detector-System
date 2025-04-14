const int MQ4_Pin = A0;       // Analog pin connected to MQ-4 sensor
const float V_supply = 5.0;   // Supply voltage in volts
const float R_load = 10.0;    // Load resistance in kilo-ohms
const int numReadings = 10;   // Number of readings to average

float calculate_Rs(float V_out) {
    return ((V_supply - V_out) * R_load) / V_out;
}

void setup() {
    Serial.begin(9600);
    delay(1000); // Allow Serial Monitor to initialize
    Serial.println("Starting readings...");
}

void loop() {
    float total_Rs = 0;

    for (int i = 0; i < numReadings; i++) {
        int analogValue = analogRead(MQ4_Pin);
        float V_out = (analogValue / 1023.0) * V_supply;
        float Rs = calculate_Rs(V_out);
        total_Rs += Rs;
        delay(100);  // Small delay between readings
    }

    float avg_Rs = total_Rs / numReadings;
    Serial.print("Averaged Sensor Resistance (Rs): ");
    Serial.print(avg_Rs);
    Serial.println(" kOhms");

    delay(1000);  // Delay before next averaged reading
}
