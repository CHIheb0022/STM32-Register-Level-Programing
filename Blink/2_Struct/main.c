// STM32L476RG Bare-metal LED Blinking

// In order to use uint32_t, uint16_t, uint8_t
#include <stdint.h>

#define __IO volatile 

// Memory-mapped addresses
#define RCC_BASE    0x40021000UL
#define GPIOA_BASE  0x48000000UL


typedef struct 
{
    __IO uint32_t MODER; /*!< GPIO port mode register,      Address offset: 0x00   */
    __IO uint32_t Dummy[4]; 
    __IO uint32_t ODR;  /*!< GPIO port output data register,       Address offset: 0x14  */

} GPIO_TypeDef;

typedef struct
{
  __IO uint32_t Dummy[19];                              
  __IO uint32_t AHB2ENR; /*!< RCC AHB2 peripheral clocks enable register,    Address offset: 0x4C */
  
  // (Decimal) Register_Index = Regiter_OFFSET (Hexa) / 4 (Cuase every registers consumes 4 bytes) :
  // Example (0x4C / 4) = 19 
} RCC_TypeDef;

// Define pointers to Peripheral structs 
#define RCC ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)   
// equivalent: RCC_TypeDef* RCC = (RCC_TypeDef*)RCC_BASE; // Type caste ensure allocating memory for struct members starting from RCC_BASE address 

#define GPIOAEN (1U<<0)
#define PIN5    (1U<<5)
#define MODER10 (1U<<10)
#define MODER11 (1U<<11)

// Function prototypes
// #define SET_BIT(REG, BIT)   ((REG) |=  (1U << (BIT)))
// #define CLEAR_BIT(REG, BIT) ((REG) &= ~(1U << (BIT)))
// #define TOGGLE_BIT(REG,BIT) ((REG) ^=  (1U << (BIT)))
void delay(int iterations);

int main(void) {
    // Enable clock for GPIOA
    RCC->AHB2ENR|= GPIOAEN;     // or SET_BIT(RCC->AHB1ENR,0);


    // Set PA5 as output
    GPIOA->MODER&= ~MODER11;  // or CLEAR_BIT(GPIOA->MODER, 11);
    GPIOA->MODER|= MODER10;  // or  SET_BIT(GPIOA->MODER, 10);

    while (1) {
        // Toggle the LED on PA5
        GPIOA->ODR|= PIN5;  // or SET_BIT(GPIOA->ODR, 5);
        delay(1000000);
        GPIOA->ODR&= ~PIN5; // or CLEAR_BIT(GPIOA->ODR, 5);
        delay(1000000);
    }

    return 0;
}

// Simple delay function
void delay(int iterations) {
    for (int i = 0; i < iterations; i++) {
        asm("nop"); // Execute a no-operation assembly instruction: consuming 1 CPU cycle 
    }
}