
#define START_BYTE 64
#define CONNECT_MID 43
#define COMMAND_SIZE 7
#define MESSAGE_SIZE 7


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(0);
  digitalWrite(LED_BUILTIN, LOW);
}


int servo = 0;
uint16_t command = 0;
uint16_t value = 0;
int checksum = 0;


char calcCheckSum(char byte1, char byte2, char byte3, char byte4) {
    return (byte1+byte2+byte3+byte4) / 8;
}


void setData(uint8_t DXL_ID, uint8_t command=0, uint16_t value=0) {
    /*if (DXL_ID ==0 || DXL_ID > 4) {
        return;
    }
    if (value > 1023) {
        value = 1023;
    }*/
    if (DXL_ID == 0) {
        DXL_ID = 43;
    }
    Serial.print(char(START_BYTE));
    Serial.print(char(START_BYTE));
    Serial.print(char(DXL_ID));
    Serial.print(char(command));
    Serial.print(char(value / 100));
    Serial.print(char(value % 100));
    Serial.print(char(calcCheckSum(servo, command, value/100, value%100)));
    //Serial.println((int)calcCheckSum(servo, command, value/100, value%100));
}


void getData() {
  byte b1 = 0;
  byte b2 = 0;
  if (Serial.available() >= 7) {
      b1 = Serial.read();
      b2 = Serial.read();
      if (b1 + b2 == 128) {
          servo = Serial.read();
          command = Serial.read();
          value = Serial.read() * 100;
          value += Serial.read();
          checksum = Serial.read();
      
      if (checksum == calcCheckSum(servo, command, value/100, value%100) && servo == 0 && command == 0) {
          setData(0, CONNECT_MID, CONNECT_MID * 100 + CONNECT_MID);
      }
      if (calcCheckSum(servo, command, value/100, value%100) == checksum && servo != 0) { // 
          setData(36, 33, 9442);
      }
    }
  }
}


void loop() {
    getData();
}
