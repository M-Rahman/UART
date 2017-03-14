ET, RT;

struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t V_id;
  int16_t Start;
};

struct SEND_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t moduleState;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;
SEND_DATA_STRUCTURE tx_mydata;
int UID = 12589;
void setup() {
  Serial.begin(250000);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Serial);
  RT.begin(details(tx_mydata), &Serial);
}

bool verifyID()
{
  if (ET.receiveData()) {
    if (mydata.V_id == UID)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

void TxData()
{
  tx_mydata.moduleState=1;
  RT.sendData();
}

void loop() {
  //check and see if a data packet has come in.
  if (ET.receiveData()) {

    if (verifyID())
    {
      Serial.print("Module Identified, Module UID:");
      Serial.println(mydata.V_id);
      TxData();
    }
    else
    {
      Serial.print("ERROR: Module not identified, inserted Module UID:");
      Serial.println(mydata.V_id);
    }

  }

}


