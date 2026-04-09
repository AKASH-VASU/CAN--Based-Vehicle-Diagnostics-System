#include <SPI.h>
#include <mcp_can.h>

#define CS_PIN 10

MCP_CAN CAN(CS_PIN);

// CAN Data Buffers
unsigned char frame1[8];
unsigned char frame2[8];

// Mode control
bool abnormalMode = false;
unsigned long lastSwitch = 0;

// Parameters
int rpm, speed, temp, load, fuel, throttle;
int fuelcons, distance = 0, airtemp, o2, dtc;
float batt;

void setup() {
  Serial.begin(9600);

  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN Init OK");
  } else {
    Serial.println("CAN Init Failed");
    while (1);
  }

  CAN.setMode(MCP_NORMAL);
}

void loop() {

  // 🔁 Toggle every 15 seconds
  if (millis() - lastSwitch > 60000) {
    abnormalMode = !abnormalMode;
    lastSwitch = millis();
  }

  // 🟢 NORMAL MODE
  if (!abnormalMode) {
    rpm = random(800, 2500);
    speed = random(40, 80);
    temp = random(70, 90);
    load = random(20, 60);
    fuel = random(30, 80);
    throttle = random(20, 50);
    batt = random(120, 130) / 10.0;
    fuelcons = random(15, 22);
    airtemp = random(25, 35);
    o2 = random(2, 6);
    dtc = 0;
  }

  // 🔴 ABNORMAL MODE
  else {
    rpm = random(3500, 4500);
    speed = random(90, 120);
    temp = random(100, 110);
    load = random(80, 100);
    fuel = random(5, 15);
    throttle = random(80, 100);
    batt = random(105, 115) / 10.0;
    fuelcons = random(5, 10);
    airtemp = random(40, 50);
    o2 = random(7, 10);
    dtc = 1;
  }

  // Distance simulation
  distance += speed * 0.05;

  // 🔹 CAN FRAME 1
  frame1[0] = highByte(rpm);
  frame1[1] = lowByte(rpm);
  frame1[2] = speed;
  frame1[3] = temp;
  frame1[4] = load;
  frame1[5] = fuel;
  frame1[6] = throttle;
  frame1[7] = batt * 10;

  CAN.sendMsgBuf(0x100, 0, 8, frame1);

  // 🔹 CAN FRAME 2
  frame2[0] = fuelcons;
  frame2[1] = highByte(distance);
  frame2[2] = lowByte(distance);
  frame2[3] = airtemp;
  frame2[4] = o2;
  frame2[5] = dtc;
  frame2[6] = 0;
  frame2[7] = 0;

  CAN.sendMsgBuf(0x101, 0, 8, frame2);

  // 🖥 SERIAL MONITOR OUTPUT
  Serial.println("====================================");
  Serial.print("Mode: ");
  Serial.println(abnormalMode ? "ABNORMAL" : "NORMAL");

  Serial.print("RPM: "); Serial.println(rpm);
  Serial.print("Speed: "); Serial.println(speed);
  Serial.print("Temperature: "); Serial.println(temp);
  Serial.print("Engine Load: "); Serial.println(load);

  Serial.print("Fuel Level: "); Serial.println(fuel);
  Serial.print("Fuel Consumption: "); Serial.println(fuelcons);
  Serial.print("Battery Voltage: "); Serial.println(batt);

  Serial.print("Throttle Position: "); Serial.println(throttle);

  Serial.print("Air Temp: "); Serial.println(airtemp);
  Serial.print("O2 Sensor: "); Serial.println(o2);

  Serial.print("Distance: "); Serial.println(distance);
  Serial.print("DTC Code: "); Serial.println(dtc);

  Serial.println("====================================");

  delay(1000);
}