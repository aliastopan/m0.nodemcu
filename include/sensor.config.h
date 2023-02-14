#ifndef SENSOR
#define SENSOR

// HARDWARE
#define MQ_PIN A0
#define RL_VALUE (2) // load resistor
#define RO_CLEAN_AIR_FACTOR (9.83)

// SOFTWARE
#define CALIBRATION_SAMPLE_TIMES (50)
#define CALIBRATION_SAMPLE_INTERVAL (500) // in ms
#define READ_SAMPLE_INTERVAL (50)
#define READ_SAMPLE_TIMES (5)

// MACRO
#define GAS_LPG 0;

float LPGCurve[3] = { 2.3, 0.21, 0.47 };
float Ro = 10;
float PPM = 0;

class MQ
{
    private:
    static float CalibrateResistance(int raw_adc)
    {
        return abs( (((float)RL_VALUE*(1023-raw_adc)/raw_adc)) );
    }

    static int Calculate(float sample_ro_ratio)
    {
        return Percentage(sample_ro_ratio, LPGCurve);
    }

    static int Percentage(float sample_ro_ratio, float *curve)
    {
        return (pow(10,( ((log(sample_ro_ratio)-curve[1])/curve[2]) + curve[0])));
    }

    public:
    static void Calibrate()
    {
        int i;
        float ro = 0;
        for(i=0;i<CALIBRATION_SAMPLE_TIMES;i++)
        {
            ro += CalibrateResistance(analogRead(MQ_PIN));
            delay(CALIBRATION_SAMPLE_INTERVAL);

        }
        ro = ro/CALIBRATION_SAMPLE_TIMES;
        ro = ro/RO_CLEAN_AIR_FACTOR;
        Ro = ro;
    }

    static float Read(int mq_pin)
    {
        int i;
        float rs = 0;
        for (i=0; i<READ_SAMPLE_TIMES; i++)
        {
            rs += CalibrateResistance(analogRead(mq_pin));
            delay(READ_SAMPLE_INTERVAL);
        }
        rs = rs/READ_SAMPLE_TIMES;
        return abs(rs);
    }

    static void Loop()
    {
        float value = 10-Read(MQ_PIN)/Ro;
        value = value < 0 ? 0 : value;
        PPM = pow(value, 2.478);
        Serial.print(PPM);
	    Serial.print(" ppm");
        Serial.print(" \t");
    }
};

#endif