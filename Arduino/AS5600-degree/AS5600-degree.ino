#include <Wire.h>
#define AS5600_addr 0x36

// Function Prototype Declaration
byte read_AS5600(byte);
void write_AS5600(byte, byte);

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1);
  }

  delay(1000);
  byte offSetAngle1 = read_AS5600(0x0C);
  byte offSetAngle2 = read_AS5600(0x0D);

  write_AS5600(0x01, offSetAngle1);
  write_AS5600(0x02, offSetAngle2);
}

void loop()
{
  // check status
  byte AS5600Status = read_AS5600(0x0B);
  AS5600Status = AS5600Status & 0B00111000;

  // read RAW angle
  uint16_t rawAngle1 = read_AS5600(0x0C);
  uint16_t rawAngle2 = read_AS5600(0x0D);
  uint16_t rawAngle = ((0x0F & rawAngle1) << 8) | rawAngle2;

  // read angle
  uint16_t angle1 = read_AS5600(0x0E);
  uint16_t angle2 = read_AS5600(0x0F);
  uint16_t angle = ((0x0F & angle1) << 8) | angle2;

  // read ZPOS
  uint16_t zpos1 = read_AS5600(0x01);
  uint16_t zpos2 = read_AS5600(0x02);
  uint16_t zpos = ((0x0F & zpos1) << 8) | zpos2;

  // read MPOS
  uint16_t mpos1 = read_AS5600(0x03);
  uint16_t mpos2 = read_AS5600(0x04);
  uint16_t mpos = ((0x0F & mpos1) << 8) | mpos2;

  float angledeg = angle * (360.0 / 4096.0);

  Serial.print("Status:");
  Serial.println(AS5600Status);
  Serial.print("RAWAngel:");
  Serial.println(rawAngle);
  Serial.print("Angle:");
  Serial.println(angle);
  Serial.print("AngleDeg:");
  Serial.println(angledeg);
  Serial.print("ZPOS:");
  Serial.println(zpos);
  Serial.print("MPOS:");
  Serial.println(mpos);
  Serial.println("-----------------");

  delay(20);
}

byte read_AS5600(byte addr)
{
  Wire.beginTransmission(AS5600_addr);
  Wire.write(addr);
  Wire.endTransmission(false);
  Wire.requestFrom(AS5600_addr, 1, true);
  byte data = Wire.read();
  return data;
}

void write_AS5600(byte addr, byte data)
{
  Wire.beginTransmission(AS5600_addr);
  Wire.write(addr); // addressing
  Wire.write(data); // write data
  Wire.endTransmission();
}
