class StationBtn {
  private:
    void setLED(bool state);
    //void readHandRest()
    void setCh(bool state);

  public:
    bool Active;
    bool Watch;

    int btnPin;
    int handrestPin;
    int chPin;
    int LEDPin;

    StationBtn(int btnPin, int LEDPin, int hrPin, int chPin);
    bool Similar(StationBtn *other);
    void Activate();
    void Deactivate();
    void MonitorHandRest();
};

