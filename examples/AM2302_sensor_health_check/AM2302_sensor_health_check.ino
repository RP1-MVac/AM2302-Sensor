/*
*	AM2302-Sensor_Example.ino
*
*	Author: Frank Häfele
*	Date:	24.11.2023
*
*	Object: Health check of AM2302-Sensor with Arduino IDE
*/

#include <AM2302-Sensor.h>

AM2302::AM2302_Sensor am2302{7};

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    yield();
  }
  Serial.print(F("\n >>> AM2302-sensor Health Check <<<\n\n"));

  // put your setup code here, to run once:
  //set Pin
  am2302.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  static int checksum_err{0}, timeout_err {0};
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  auto status = am2302.read();
  if (status == AM2302::AM2302_ERROR_CHECKSUM) {
      ++checksum_err;
  }
  if (status == AM2302::AM2302_ERROR_TIMEOUT) {
    ++timeout_err;
  }
  Serial.print("\n\n");
  Serial.print("status of sensor read(): ");
  Serial.println(status);

  Serial.print("Number checksum erros:   ");
  Serial.println(checksum_err);

  Serial.print("Number timout erros:     ");
  Serial.println(timeout_err);

  Serial.print("\nTemperature: ");
  Serial.println(am2302.get_Temperature());

  Serial.print("Humidity:    ");
  Serial.println(am2302.get_Hunidity());
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
}
