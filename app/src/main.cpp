// ####################################################################################                                                             
// This is the basic example to use the GoPiGo.
// http://www.dexterindustries.com/GoPiGo/
// History
// ------------------------------------------------
// Date                 Comments
// 30 Aug 15            Initial Authoring
// 02 Feb 16            Support Encoders

// ## License
//
// GoPiGo for the Raspberry Pi: an open source robotics platform for the Raspberry Pi.
// Copyright (C) 2017  Dexter Industries

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/gpl-3.0.txt>.

// ####################################################################################
#include <stdlib.h>
#include <stdio.h>
#include "gopigo-wrapper.h"

using namespace gopigo;

int main(void)
{
    // Buffer for data being read/ written on the i2c bus
    if(init()==-1)
        exit(1);
    led_on(1);

    while(1)
    {
       char input[2];    /* Store 2 input characters */

       printf("Enter cmd: ");
       scanf(" %s", &input);

       switch (input[0])
       {
            case 'w':
                fwd();
                break;

            case 'a':
                left();
                break;

            case 'd':
                right();
                break;

            case 's':
                bwd();
                break;

            case 'e':
                increase_speed();
                break;

            case 'g':
                decrease_speed();
                break;

            case 'z':
                exit(0);
                break;

            case 'x':
                stop();
                break;

            case 'i':
                motor_fwd();
                break;

            case 'k':
                motor_bwd();
                break;

            case 'n':
                left_rot();
                break;

            case 'm':
                right_rot();
                break;

            case 'l':
                switch(input[1])
                {
                    case 'o':
                        int led_val;
                        printf("Enter 1 for left led and 0 for right led:\n");
                        scanf(" %d", &led_val);
                        led_on(led_val);
                        break;
                    case 'f':
                        int led_val2;
                        printf("Enter 1 for left led and 0 for right led:\n");
                        scanf(" %d", &led_val2);
                        led_off(led_val2);
                        break;
                    default:
                        printf("invalid led command... (o for ON, f for OFF)\n");
                        break;
                }
                break;

            case 'r':
                int servo_val;
                printf("Enter servo position:\n");
                scanf(" %d", &servo_val);
                servo(servo_val);
                break;

            case 'v':
                printf("Firmware Version: %d\n",fw_ver());
                break; 
                
            case 'u':
                printf("Ultrasonic Dist: %d\n",us_dist(15));
                break;
                    
            case 't':
                switch(input[1])
                {
                    case 'r':
                        {
                            int val = trim_read();
                            if(val == -3){
                            printf("-3, Trim Value Not set\n");
                            }
                            else{
                            printf("%d\n", val-100);
                            }
                            break;
                        }
                    case 'w':
                        {
                            int val2;
                            printf("Enter trim value to write to EEPROM(-100 to 100):\n");
                            scanf(" %d", &val2);
                            trim_write(val2);
                            pi_sleep(100);
                            printf("Value in EEPROM: %d\n", trim_read()-100);
                            break;
                        }
                    case 't':
                        {
                            int val3;
                            printf("Enter trim value to test(-100 to 100):\n");
                            scanf(" %d", &val3);
                            trim_test(val3);
                            pi_sleep(100);
                            printf("Value in EEPROM: %d\n", trim_read()-100);
                            break;
                        }
                    default:
                        printf("invalid trim command...\n");
                        break;
                   }
                break;

            case 'c':
                printf("Motor 0 (left) travelled %i cm\n", enc_read(0));
                printf("Motor 1 (right) travelled %i cm\n", enc_read(1));
                break;

            default:
                printf("invalid command...\n");
                break;
       }

    }
    return 0;
}