#include <xc.h>
#include <avr/io.h>

char audio_str[] = "audio-sense";
char illuminence_str[] = "light-sense";
char single_digit[2];
char double_digit[3];
char tripple_digit[4];

char* PercentageToString(unsigned char p) {
//    if (p >= 10 && p < 100) {
//        double_digit[0] = '0' + ((p / 10) % 10);
//        double_digit[1] = '0' + (p % 10);
//        double_digit[2] = '\0';
//        return double_digit;
//    } else if (p < 10) {
//        single_digit[0] = '0' + p;
//        single_digit[1] = '\0';
//        return single_digit;
//    } else {
        tripple_digit[0] = '0' + (p / 100);
        tripple_digit[1] = '0' + ((p / 10) % 10);
        tripple_digit[2] = '0' + (p % 10);
        tripple_digit[3] = '\0';
        return tripple_digit;
//    }
}

char* getCurrentMode() {
    if (!(ADMUX & (1 << MUX0))) { // photo-resistor active
        return audio_str;
    } else {
        return illuminence_str;
    }
}
