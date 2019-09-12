/*
struct DualChannel {
    uint8_t chan1;
    uint8_t chan2;
};
*/
struct QuadChannel {
    uint8_t chan1;
    uint8_t chan2;
    uint8_t chan3;
    uint8_t chan4;
};

//struct DualChannel get_slider_inputs(void);

struct QuadChannel get_adc_values(void);
