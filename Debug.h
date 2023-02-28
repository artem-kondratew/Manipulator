
void debugPrint() {
    Serial.print("\nПотенциометр 1: ");
    Serial.println(analogRead(ANALOG_PIN1));
    Serial.print("Потенциометр 2: ");
    Serial.println(analogRead(ANALOG_PIN2));
    Serial.print("Потенциометр 3: ");
    Serial.println(analogRead(ANALOG_PIN3));
    Serial.print("Потенциометр 4: ");
    Serial.println(analogRead(ANALOG_PIN4));
}
