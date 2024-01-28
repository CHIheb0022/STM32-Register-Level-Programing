// STM32L476RG Bare-metal LED Blinking


// Peripheral Memory-mapped addresses
#define RCC_BASE    0x40021000UL
#define GPIOA_BASE  0x48000000UL

// RCC registers
#define RCC_AHB2ENR_OFFSET 0x4C 
#define RCC_AHB2ENR  (*((volatile unsigned int *)(RCC_BASE + RCC_AHB2ENR_OFFSET)))

// Equivalent using a pointer variable:
// volatile unsigned int * RCC_AHB2ENR_Ptr = (volatile unsigned int *)(RCC_BASE + RCC_AHB2ENR_OFFSET);

// GPIOA registers OFFSET
#define GPIOA_MODER_OFFSET 0x00
#define GPIOA_ODR_OFFSET 0x14

// GPIOA registers
#define GPIOA_MODER (*((volatile unsigned int *)(GPIOA_BASE + GPIOA_MODER_OFFSET)))
#define GPIOA_ODR   (*((volatile unsigned int *)(GPIOA_BASE + GPIOA_ODR_OFFSET)))



//Set up:
int main(void) {
    // Enable clock for GPIOA
    RCC_AHB2ENR|= (1U<<0);

    // Set PA5 as output : "01" output
    GPIOA_MODER&= ~(1U<<11);  // we are using the U symble to typcase the 1 to unsigned int to prevent negative values while bitwising 
    GPIOA_MODER|=  (1U<<10); 

    
    // Infinite Loop
    while (1) {

        // Toggle the LED on PA5
        
        GPIOA_ODR|= (1U<<5);
        for (int i = 0; i < 1000000; i++) {asm("nop");}// Execute a no-operation assembly instruction each iteration: consuming 1 CPU cycle
        GPIOA_ODR&= ~(1U<<5);
        for (int i = 0; i < 1000000; i++) {asm("nop");}
        
       
        /*Using the Toggle operator*/
        
        /*
        GPIOA_ODR ^= (1U << 5);  //First Set BIT 5 in the GPIOA_ODR then toggle it's state each time we pass by this line.
        for (int i = 0; i < 1000000; i++) {asm("nop");}
        */
    }

    return 0;
}



/* Friendly programming */

// GPIOA_ODR = (1U<<5);  // GPIOA_ODR = 0b0000 0000 0010 0000
// GPIOA_ODR = ~(1<<5);  // GPIOA_ODR = 0b1111 1111 1101 1111

// When you directly assign this value to GPIOA_ODR, you may unintentionally modify other bits 
  


//This ensures that only BIT 5 is toggled without affecting other bits in GPIOA_ODR. 

//        GPIOA_ODR|= (1<<5);
//        delay(1000000);
//        GPIOA_ODR&= ~(1<<5);
//        delay(1000000);