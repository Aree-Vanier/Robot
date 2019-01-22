#ifndef Controller_h
#define Controller_h

class Controller{
    public:
        //Constuctor, requires an analog pin and a digital pin
        Controller(int speedPin, int directionPin);
        //Called to set the targe speed
        void set(float percent);
        //Get the current speed, returns current speed
        double getSpeed();
        //Stop the controller instantly
        void stop();
        //Called regulaly to smooth acceleration
        void drive();
    private:
        int speedPin; //Forward pin
        int directionPin; //Reverse pin
        float speed;   //Current speed
        int targetSpeed; //Target speed
        float accel = 20; //Acceleration

};

#endif
