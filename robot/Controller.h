#ifndef Controller_h
#define Controller_h

class Controller{
    public:
        Controller(int speedPin, int directionPin);
        void set(float percent); // Called to set target speed
        double getSpeed();
        void stop();  //E-Stop, will stop all motor functions immediately
        void drive(); //Called repetiviely to smooth acceleration
    private:
        int speedPin; //Forward pin
        int directionPin; //Reverse pin
        float speed;   //Current speed
        int targetSpeed; //Target speed
        float accel = 20; //Acceleration

};

#endif
