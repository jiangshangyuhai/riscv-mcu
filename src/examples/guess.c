#include "guess.h"
#include "iic.h"
#include "uart.h"
#include "timer.h"
#include "common.h"

void run_guess_game() {
    while(1){
        iic_write(DEV_ADDRESS, MIN_REG_ADDR, MIN_NUMBER);
        iic_write(DEV_ADDRESS, MAX_REG_ADDR, MAX_NUMBER);
        uint8_t fact_num = iic_read(DEV_ADDRESS, 0);
        // uint8_t numstrs[4] = {' ', ' ', ' ', '\0'};
        // int i = 2;
        // do {
        //     int digit = 0;
        //     while (fact_num >= 10) {
        //         fact_num -= 10;
        //         digit++;
        //     }
        //     numstrs[i--] = fact_num + '0';
        //     fact_num = digit;
        // } while (fact_num > 0 && i >= 0);
        while(1) {
            send_string("Guess one number between [1,100]: ");
            uint8_t guess_num[4] = {0,0,0,0};
            int i = 0;
            while(1) {
                uint8_t c = getchar();
                if (c == 0xa) {
                    break;
                }
                send_char('h');
                send_char(c);
                guess_num[i++] = c;
            }
            send_string("\n");
            uint8_t guess = atoi((char*)guess_num);
            if (guess == fact_num) {
                send_string("You win!\n");
            } else if( guess > fact_num) {
                send_string("Too large!\n");
            } else {
                send_string("Too small!\n");
            }
        }
        sleep(500);
   }
}