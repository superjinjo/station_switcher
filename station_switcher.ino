#include "StationBtn.h"
//11 buttons
//each button needs a state

//Invalid button combinations:
//only one button on on the same row
//buttons on the same column are okay

//3 rows "channels"
//row coorilates with thingydoo
//last button press is true, cancels last one out

//at least 3 columns "hand rests"
//columns must also be unique

//rows
#define CH_1 50 //d51 
#define CH_2 49
#define CH_3 51

//columns
#define REST_A 44
#define REST_B 45
#define REST_C 46
#define REST_D 47
#define REST_E 48

int channels[3] = {CH_1, CH_2, CH_3};
//int handRests[5] = {REST_A, REST_B, REST_C, REST_D, REST_F};

StationBtn *btns[11];
StationBtn *activeBtns[3];

void setup() {
  Serial.begin(115200);
 
  //Button 1A
  btns[0] = new StationBtn(23, 22, REST_A, CH_1);

  //Button 1B
  btns[1] = new StationBtn(25, 24, REST_B, CH_1);

  //Button 1C
  btns[2] = new StationBtn(27, 26, REST_C, CH_1);
  

  //Button 2A
  btns[3] = new StationBtn(29, 28, REST_A, CH_2);

  //Button 2B
  btns[4] = new StationBtn(31, 30, REST_B, CH_2);

  //Button 2C
  btns[5] = new StationBtn(33, 32, REST_C, CH_2);

  //Button 2D
  btns[6] = new StationBtn(35, 34, REST_D, CH_2);
  

  //Button 3A
  btns[7] = new StationBtn(37, 36, REST_A, CH_3);

  //Button 3B
  btns[8] = new StationBtn(39, 38, REST_B, CH_3);

  //Button 3C
  btns[9] = new StationBtn(41, 40, REST_C, CH_3);

  //Button 3E (No D)
  btns[10] = new StationBtn(43, 42, REST_E, CH_3);

}

void loop() {

  StationBtn *current;

  for(int i = 0; i < 11; i++) {
    current = btns[i];

    if(digitalRead(current->btnPin)) {
      current->Watch = true;
    } else if(current->Watch) {
      if(current->Active) {
        deactivateBtn(current);
      } else {
        activateBtn(current);
      }
      current->Watch = false;
    }
  }

  monitorActive();

}

void monitorActive() {
  StationBtn *nextBtn;
  
  for(int i = 0; i < 3; i++) {
    nextBtn = activeBtns[i];
    if(nextBtn != NULL) {
      (activeBtns[i])->MonitorHandRest();
    }
  }
}

void deactivateBtn(StationBtn *btn) {
  StationBtn *nextBtn;
  
  for(int i = 0; i < 3; i++) {
    nextBtn = activeBtns[i];
    
    if(channels[i] == btn->chPin && btn == nextBtn ) {
      activeBtns[i] = NULL;
      break;
    }
  }

  btn->Deactivate();
}

void activateBtn(StationBtn *btn) {
  StationBtn *nextBtn;
  
  for(int i = 0; i < 3; i++) {
    nextBtn = activeBtns[i];
    if(nextBtn != NULL && btn->Similar(nextBtn)) {
      nextBtn->Deactivate();
      activeBtns[i] = NULL;
    }

    if(channels[i] == btn->chPin) {
      activeBtns[i] = btn;
    }
  }

  btn->Activate();
}

