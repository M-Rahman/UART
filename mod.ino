ET, RT;

struct SEND_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t Uid;
  int16_t Start;
};
struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t moduleState;
};
//give a name to the group of data
SEND_DATA_STRUCTURE mydata;
RECEIVE_DATA_STRUCTURE rx_mydata;
bool m_ready;
void setup() {
  Serial.begin(250000);
  ET.begin(details(mydata), &Serial);
  RT.begin(details(rx_mydata), &Serial);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  sendModuleID();
  readState();
  //  operation();
}

void readState()
{

  if (RT.receiveData()) {
    if (rx_mydata.moduleState == 1)
    {
      Serial.println("Module is ready to operate");
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      operation();  //5. if the module has been cleared by BASE start operation

    }
    else
    {
      Serial.println("Module is not ready");
      digitalWrite(11, HIGH);
    }
  }
  else
      digitalWrite(11, HIGH);
  
}

void operation()
{
  Serial.println("Air purifier starts now for 5 second");
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(5000);
  Serial.println("Air purifier stops for next 3 seconds");
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(3000);
  // operation();
}


void sendModuleID()
{
  mydata.Uid = 12589;
  mydata.Start = 1;
  //send the data
  ET.sendData();

}

