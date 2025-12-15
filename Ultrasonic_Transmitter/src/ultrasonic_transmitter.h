#ifndef ULTRASONIC_TRANSMITTER
#define ULTRASONIC_TRANSMITTER

#define ULTRASONIC_TX_PIN 25

class Ultrasonic_Transmitter
{
private:
    int tx_pin; // ULTRASONIC_TX_PIN
public:
    Ultrasonic_Transmitter();
    void transmit();
};


#endif
