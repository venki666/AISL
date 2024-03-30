#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#define MOTO_GPIO1  16
#define MOTO_GPIO2  17
// Step one ： choice mcpwm_unit
#define MOTOR_MCPWM_UNIT MCPWM_UNIT_0

// Four required for initialization gpio mouth 

void setup(){
// Step two ： Use the selected mcpwm_unit To initialize the gpio mouth 
    mcpwm_gpio_init(MOTOR_MCPWM_UNIT, MCPWM0A, MOTO_GPIO1);
    mcpwm_gpio_init(MOTOR_MCPWM_UNIT, MCPWM0B, MOTO_GPIO2);  
// Step three ： use mcpwm_init() This function is this mcpwm_unit Select a timer ,
#define MOTO_TIMER MCPWM_TIMER_0
    mcpwm_config_t pwm_config;
// Step four ： adopt mcpwm_config_t The structure sets the frequency and initial value for the timer 
    pwm_config.frequency = 500;    //frequency = 500Hz,
    pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;    //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    
// Step five ： call mcpwm_init() Function to make the configuration effective 
    mcpwm_init(MOTOR_MCPWM_UNIT, MOTO_TIMER, &pwm_config);    //Configure PWM0A & PWM0B with above settings

    
}

void loop(){
  
     mcpwm_set_signal_low(MOTOR_MCPWM_UNIT, MOTO_TIMER, MCPWM_OPR_A);
     mcpwm_set_duty(MOTOR_MCPWM_UNIT, MOTO_TIMER, MCPWM_OPR_B, 100);
     mcpwm_set_duty_type(MOTOR_MCPWM_UNIT, MOTO_TIMER, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state 
}
