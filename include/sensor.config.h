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

class MQ
{
    private:
    static float CalibrateResistance(int raw_adc)
    {
        return abs( (((float)RL_VALUE*(1023-raw_adc)/raw_adc)) );
        // return (((float)RL_VALUE*(raw_adc-1023)/raw_adc)) * 100;
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
	    Serial.print("adc: ");
	    Serial.print(analogRead(MQ_PIN));
	    Serial.print("\t");
	    Serial.print("rs/ro: ");
	    Serial.print(Read(MQ_PIN));
	    Serial.print("/");
	    Serial.print(Ro);
	    Serial.print("\t");
        Serial.print(Read(MQ_PIN)/Ro);
	    Serial.print(" ppm");
	    Serial.println("");
    }
};

#endif