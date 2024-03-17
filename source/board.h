//adapted from C:\ChibiStudio\chibios2111\os\hal\boards\ST_NUCLEO64_F410RB\board.h
#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for STMicroelectronics STM32 Nucleo64-F410RB board.
 */

/*
 * Board identifier.
 */
#define BOARD_MICROCNTR
#define BOARD_NAME                  "MICROCNTR F410RB"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

#define STM32_HSE_BYPASS

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F410Rx

/*
 * IO pins assignments.
 */
#define GPIOA_CNT_IN              0U
#define GPIOA_PIN1                1U
#define GPIOA_USART2_TX           2U
#define GPIOA_USART2_RX           3U
#define GPIOA_PIN4                4U
#define GPIOA_PIN5                5U
#define GPIOA_PIN6                6U
#define GPIOA_ADC_CURRENT                7U
#define GPIOA_PIN8                8U
#define GPIOA_USART1_TX                9U
#define GPIOA_USART1_RX               10U
#define GPIOA_PIN11               11U
#define GPIOA_heater_enable               12U
#define GPIOA_SWDIO               13U
#define GPIOA_SWCLK               14U
#define GPIOA_PIN15               15U

#define GPIOB_REF_INT_SEL          0U
#define GPIOB_PIN1                 1U
#define GPIOB_PIN2                 2U
#define GPIOB_SWO                  3U
#define GPIOB_CAL_SOUR_SEL                 4U
#define GPIOB_REF_INT_EN           5U
#define GPIOB_PIN6                 6U
#define GPIOB_PIN7                 7U
#define GPIOB_PIN8                 8U
#define GPIOB_PIN9                 9U
#define GPIOB_PIN10               10U
#define GPIOB_PIN11               11U
#define GPIOB_ADF_LE               12U
#define GPIOB_ADF_CLK               13U
#define GPIOB_LED1               14U
#define GPIOB_ADF_DATA               15U

#define GPIOC_PIN0                 0U
#define GPIOC_PIN1                 1U
#define GPIOC_ADC_HEAT                 2U
#define GPIOC_PIN3                 3U
#define GPIOC_PIN4                 4U
#define GPIOC_CNT_IN                 5U
#define GPIOC_PIN6                 6U
#define GPIOC_PIN7                 7U
#define GPIOC_PIN8                 8U
#define GPIOC_PIN9                 9U
#define GPIOC_PIEZO_A               10U
#define GPIOC_PIEZO_B               11U
#define GPIOC_PIN12               12U
#define GPIOC_PIN13               13U
#define GPIOC_LED2               14U
#define GPIOC_PIN15               15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.
 */
/*
#define LINE_ARD_A0                 PAL_LINE(GPIOA, 0U)
#define LINE_ADC1_IN0               PAL_LINE(GPIOA, 0U)
#define LINE_ARD_A1                 PAL_LINE(GPIOA, 1U)
#define LINE_ADC1_IN1               PAL_LINE(GPIOA, 1U)
#define LINE_ARD_D1                 PAL_LINE(GPIOA, 2U)
...
*/
/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 *
 * All pins default input, pulldown
 *
 * GPIOA setup:
 *
 * PA2  - ARD_D1 USART2_TX          (alternate 7).
 * PA3  - ARD_D0 USART2_RX          (alternate 7).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_CNT_IN) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_USART2_TX) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_USART2_RX) |     \
                                     PIN_MODE_INPUT(GPIOA_PIN4) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN5) |     \
                                     PIN_MODE_INPUT(GPIOA_PIN6) |        \
                                     PIN_MODE_ANALOG(GPIOA_ADC_CURRENT) |        \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_TX) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_RX) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |  \
                                     PIN_MODE_OUTPUT(GPIOA_heater_enable) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_PIN15))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_CNT_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART2_TX) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART2_RX) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN5) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN6) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ADC_CURRENT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART1_TX) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART1_RX) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_heater_enable) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_LOW(GPIOA_CNT_IN) |        \
                                     PIN_OSPEED_LOW(GPIOA_PIN1) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_USART2_TX) |      \
                                     PIN_OSPEED_MEDIUM(GPIOA_USART2_RX) |      \
                                     PIN_OSPEED_LOW(GPIOA_PIN4) |        \
                                     PIN_OSPEED_LOW(GPIOA_PIN5) |   \
                                     PIN_OSPEED_LOW(GPIOA_PIN6) |       \
                                     PIN_OSPEED_LOW(GPIOA_ADC_CURRENT) |       \
                                     PIN_OSPEED_LOW(GPIOA_PIN8) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_USART1_TX) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_USART1_RX) |        \
                                     PIN_OSPEED_LOW(GPIOA_PIN11) |     \
                                     PIN_OSPEED_LOW(GPIOA_heater_enable) |     \
                                     PIN_OSPEED_LOW(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_LOW(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_LOW(GPIOA_PIN15))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOA_CNT_IN) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_USART2_TX) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_USART2_RX) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN4) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN5) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN6) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_ADC_CURRENT) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_USART1_TX) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_USART1_RX) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN11) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_heater_enable) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN15))
#define VAL_GPIOA_ODR               (PIN_ODR_LOW(GPIOA_CNT_IN) |           \
                                     PIN_ODR_LOW(GPIOA_PIN1) |           \
                                     PIN_ODR_LOW(GPIOA_USART2_TX) |           \
                                     PIN_ODR_LOW(GPIOA_USART2_RX) |           \
                                     PIN_ODR_LOW(GPIOA_PIN4) |           \
                                     PIN_ODR_LOW(GPIOA_PIN5) |         \
                                     PIN_ODR_LOW(GPIOA_PIN6) |          \
                                     PIN_ODR_LOW(GPIOA_ADC_CURRENT) |          \
                                     PIN_ODR_LOW(GPIOA_PIN8) |           \
                                     PIN_ODR_LOW(GPIOA_USART1_TX) |           \
                                     PIN_ODR_LOW(GPIOA_USART1_RX) |           \
                                     PIN_ODR_LOW(GPIOA_PIN11) |        \
                                     PIN_ODR_LOW(GPIOA_heater_enable) |        \
                                     PIN_ODR_LOW(GPIOA_SWDIO) |            \
                                     PIN_ODR_LOW(GPIOA_SWCLK) |            \
                                     PIN_ODR_LOW(GPIOA_PIN15))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_CNT_IN, 2U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN1, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_USART2_TX, 7U) |        \
                                     PIN_AFIO_AF(GPIOA_USART2_RX, 7U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN4, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN5, 0U) |     \
                                     PIN_AFIO_AF(GPIOA_PIN6, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_ADC_CURRENT, 0U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_USART1_TX, 7U) |        \
                                     PIN_AFIO_AF(GPIOA_USART1_RX, 7U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN11, 0U) |    \
                                     PIN_AFIO_AF(GPIOA_heater_enable, 0U) |    \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_PIN15, 0U))

/*
 * GPIOB setup:
 * PB3  - SWO ARD_D3                (alternate 0).
 * PB14 - GPIOB_LED1
 */
#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_REF_INT_SEL) |         \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_OUTPUT(GPIOB_CAL_SOUR_SEL) |         \
                                     PIN_MODE_OUTPUT(GPIOB_REF_INT_EN) |         \
                                     PIN_MODE_INPUT(GPIOB_PIN6) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN9) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN10) |         \
                                     PIN_MODE_INPUT(GPIOB_PIN11) |          \
                                     PIN_MODE_OUTPUT(GPIOB_ADF_LE) |          \
                                     PIN_MODE_OUTPUT(GPIOB_ADF_CLK) |          \
                                     PIN_MODE_OUTPUT(GPIOB_LED1) |          \
                                     PIN_MODE_OUTPUT(GPIOB_ADF_DATA))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_REF_INT_SEL) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAL_SOUR_SEL) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_REF_INT_EN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN6) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN9) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN10) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ADF_LE) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ADF_CLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ADF_DATA))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_LOW(GPIOB_REF_INT_SEL) |        \
                                     PIN_OSPEED_LOW(GPIOB_PIN1) |          \
                                     PIN_OSPEED_LOW(GPIOB_PIN2) |          \
                                     PIN_OSPEED_LOW(GPIOB_SWO) |           \
                                     PIN_OSPEED_LOW(GPIOB_CAL_SOUR_SEL) |        \
                                     PIN_OSPEED_LOW(GPIOB_REF_INT_EN) |        \
                                     PIN_OSPEED_LOW(GPIOB_PIN6) |       \
                                     PIN_OSPEED_LOW(GPIOB_PIN7) |          \
                                     PIN_OSPEED_LOW(GPIOB_PIN8) |       \
                                     PIN_OSPEED_LOW(GPIOB_PIN9) |       \
                                     PIN_OSPEED_LOW(GPIOB_PIN10) |        \
                                     PIN_OSPEED_LOW(GPIOB_PIN11) |         \
                                     PIN_OSPEED_MEDIUM(GPIOB_ADF_LE) |         \
                                     PIN_OSPEED_MEDIUM(GPIOB_ADF_CLK) |         \
                                     PIN_OSPEED_LOW(GPIOB_LED1) |         \
                                     PIN_OSPEED_MEDIUM(GPIOB_ADF_DATA))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_REF_INT_SEL) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_SWO) |          \
                                     PIN_PUPDR_FLOATING(GPIOB_CAL_SOUR_SEL) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_REF_INT_EN) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN6) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN7) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN8) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN9) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN10) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_ADF_LE) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_ADF_CLK) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_LED1) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_ADF_DATA))
#define VAL_GPIOB_ODR               (PIN_ODR_LOW(GPIOB_REF_INT_SEL) |           \
                                     PIN_ODR_LOW(GPIOB_PIN1) |             \
                                     PIN_ODR_LOW(GPIOB_PIN2) |             \
                                     PIN_ODR_LOW(GPIOB_SWO) |              \
                                     PIN_ODR_LOW(GPIOB_CAL_SOUR_SEL) |           \
                                     PIN_ODR_LOW(GPIOB_REF_INT_EN) |           \
                                     PIN_ODR_LOW(GPIOB_PIN6) |          \
                                     PIN_ODR_LOW(GPIOB_PIN7) |             \
                                     PIN_ODR_LOW(GPIOB_PIN8) |          \
                                     PIN_ODR_LOW(GPIOB_PIN9) |          \
                                     PIN_ODR_LOW(GPIOB_PIN10) |           \
                                     PIN_ODR_LOW(GPIOB_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOB_ADF_LE) |            \
                                     PIN_ODR_LOW(GPIOB_ADF_CLK) |            \
                                     PIN_ODR_LOW(GPIOB_LED1) |            \
                                     PIN_ODR_LOW(GPIOB_ADF_DATA))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_REF_INT_SEL, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_SWO, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_CAL_SOUR_SEL, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_REF_INT_EN, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN6, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN9, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN10, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_ADF_LE, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_ADF_CLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_LED1, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_ADF_DATA, 0U))

/*
 * GPIOC setup:
 * PC14 - LED1                      (output, lowspeed).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_PIN0) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |         \
                                     PIN_MODE_ANALOG(GPIOC_ADC_HEAT) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOC_CNT_IN) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                     PIN_MODE_OUTPUT(GPIOC_PIEZO_A) |          \
                                     PIN_MODE_OUTPUT(GPIOC_PIEZO_B) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |         \
                                     PIN_MODE_OUTPUT(GPIOC_LED2) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC_HEAT) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_CNT_IN) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIEZO_A) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIEZO_B) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_LOW(GPIOC_PIN0) |        \
                                     PIN_OSPEED_LOW(GPIOC_PIN1) |        \
                                     PIN_OSPEED_LOW(GPIOC_ADC_HEAT) |          \
                                     PIN_OSPEED_LOW(GPIOC_PIN3) |          \
                                     PIN_OSPEED_LOW(GPIOC_PIN4) |          \
                                     PIN_OSPEED_LOW(GPIOC_CNT_IN) |          \
                                     PIN_OSPEED_LOW(GPIOC_PIN6) |          \
                                     PIN_OSPEED_LOW(GPIOC_PIN7) |        \
                                     PIN_OSPEED_LOW(GPIOC_PIN8) |          \
                                     PIN_OSPEED_LOW(GPIOC_PIN9) |          \
                                     PIN_OSPEED_LOW(GPIOC_PIEZO_A) |         \
                                     PIN_OSPEED_LOW(GPIOC_PIEZO_B) |         \
                                     PIN_OSPEED_LOW(GPIOC_PIN12) |         \
                                     PIN_OSPEED_LOW(GPIOC_PIN13) |        \
                                     PIN_OSPEED_LOW(GPIOC_LED2) |      \
                                     PIN_OSPEED_LOW(GPIOC_PIN15))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOC_PIN0) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC_HEAT) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_CNT_IN) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIEZO_A) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_PIEZO_B) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN12) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN13) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_LED2) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN15))
#define VAL_GPIOC_ODR               (PIN_ODR_LOW(GPIOC_PIN0) |           \
                                     PIN_ODR_LOW(GPIOC_PIN1) |           \
                                     PIN_ODR_LOW(GPIOC_ADC_HEAT) |             \
                                     PIN_ODR_LOW(GPIOC_PIN3) |             \
                                     PIN_ODR_LOW(GPIOC_PIN4) |             \
                                     PIN_ODR_LOW(GPIOC_CNT_IN) |             \
                                     PIN_ODR_LOW(GPIOC_PIN6) |             \
                                     PIN_ODR_LOW(GPIOC_PIN7) |           \
                                     PIN_ODR_LOW(GPIOC_PIN8) |             \
                                     PIN_ODR_LOW(GPIOC_PIN9) |             \
                                     PIN_ODR_LOW(GPIOC_PIEZO_A) |            \
                                     PIN_ODR_HIGH(GPIOC_PIEZO_B) |            \
                                     PIN_ODR_LOW(GPIOC_PIN12) |            \
                                     PIN_ODR_LOW(GPIOC_PIN13) |           \
                                     PIN_ODR_LOW(GPIOC_LED2) |         \
                                     PIN_ODR_LOW(GPIOC_PIN15))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_ADC_HEAT, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_CNT_IN, 3U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIEZO_A, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIEZO_B, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_LED2, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0U))

/*
 * GPIOD setup:
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_LOW(GPIOD_PIN0) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN1) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN2) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN3) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN4) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN5) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN6) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN7) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN8) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN9) |          \
                                     PIN_OSPEED_LOW(GPIOD_PIN10) |         \
                                     PIN_OSPEED_LOW(GPIOD_PIN11) |         \
                                     PIN_OSPEED_LOW(GPIOD_PIN12) |         \
                                     PIN_OSPEED_LOW(GPIOD_PIN13) |         \
                                     PIN_OSPEED_LOW(GPIOD_PIN14) |         \
                                     PIN_OSPEED_LOW(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN5) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN12) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN13) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_LOW(GPIOD_PIN0) |             \
                                     PIN_ODR_LOW(GPIOD_PIN1) |             \
                                     PIN_ODR_LOW(GPIOD_PIN2) |             \
                                     PIN_ODR_LOW(GPIOD_PIN3) |             \
                                     PIN_ODR_LOW(GPIOD_PIN4) |             \
                                     PIN_ODR_LOW(GPIOD_PIN5) |             \
                                     PIN_ODR_LOW(GPIOD_PIN6) |             \
                                     PIN_ODR_LOW(GPIOD_PIN7) |             \
                                     PIN_ODR_LOW(GPIOD_PIN8) |             \
                                     PIN_ODR_LOW(GPIOD_PIN9) |             \
                                     PIN_ODR_LOW(GPIOD_PIN10) |            \
                                     PIN_ODR_LOW(GPIOD_PIN11) |            \
                                     PIN_ODR_LOW(GPIOD_PIN12) |            \
                                     PIN_ODR_LOW(GPIOD_PIN13) |            \
                                     PIN_ODR_LOW(GPIOD_PIN14) |            \
                                     PIN_ODR_LOW(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))

/*
 * GPIOE setup:
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_LOW(GPIOE_PIN0) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN1) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN2) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN3) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN4) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN5) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN6) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN7) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN8) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN9) |          \
                                     PIN_OSPEED_LOW(GPIOE_PIN10) |         \
                                     PIN_OSPEED_LOW(GPIOE_PIN11) |         \
                                     PIN_OSPEED_LOW(GPIOE_PIN12) |         \
                                     PIN_OSPEED_LOW(GPIOE_PIN13) |         \
                                     PIN_OSPEED_LOW(GPIOE_PIN14) |         \
                                     PIN_OSPEED_LOW(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOE_PIN0) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN5) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN7) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN9) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN10) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN11) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN12) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN13) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_LOW(GPIOE_PIN0) |             \
                                     PIN_ODR_LOW(GPIOE_PIN1) |             \
                                     PIN_ODR_LOW(GPIOE_PIN2) |             \
                                     PIN_ODR_LOW(GPIOE_PIN3) |             \
                                     PIN_ODR_LOW(GPIOE_PIN4) |             \
                                     PIN_ODR_LOW(GPIOE_PIN5) |             \
                                     PIN_ODR_LOW(GPIOE_PIN6) |             \
                                     PIN_ODR_LOW(GPIOE_PIN7) |             \
                                     PIN_ODR_LOW(GPIOE_PIN8) |             \
                                     PIN_ODR_LOW(GPIOE_PIN9) |             \
                                     PIN_ODR_LOW(GPIOE_PIN10) |            \
                                     PIN_ODR_LOW(GPIOE_PIN11) |            \
                                     PIN_ODR_LOW(GPIOE_PIN12) |            \
                                     PIN_ODR_LOW(GPIOE_PIN13) |            \
                                     PIN_ODR_LOW(GPIOE_PIN14) |            \
                                     PIN_ODR_LOW(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0U))

/*
 * GPIOF setup:
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_LOW(GPIOF_PIN0) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN1) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN2) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN3) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN4) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN5) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN6) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN7) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN8) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN9) |          \
                                     PIN_OSPEED_LOW(GPIOF_PIN10) |         \
                                     PIN_OSPEED_LOW(GPIOF_PIN11) |         \
                                     PIN_OSPEED_LOW(GPIOF_PIN12) |         \
                                     PIN_OSPEED_LOW(GPIOF_PIN13) |         \
                                     PIN_OSPEED_LOW(GPIOF_PIN14) |         \
                                     PIN_OSPEED_LOW(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOF_PIN0) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN5) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN7) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN9) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN10) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN11) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN12) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN13) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_LOW(GPIOF_PIN0) |             \
                                     PIN_ODR_LOW(GPIOF_PIN1) |             \
                                     PIN_ODR_LOW(GPIOF_PIN2) |             \
                                     PIN_ODR_LOW(GPIOF_PIN3) |             \
                                     PIN_ODR_LOW(GPIOF_PIN4) |             \
                                     PIN_ODR_LOW(GPIOF_PIN5) |             \
                                     PIN_ODR_LOW(GPIOF_PIN6) |             \
                                     PIN_ODR_LOW(GPIOF_PIN7) |             \
                                     PIN_ODR_LOW(GPIOF_PIN8) |             \
                                     PIN_ODR_LOW(GPIOF_PIN9) |             \
                                     PIN_ODR_LOW(GPIOF_PIN10) |            \
                                     PIN_ODR_LOW(GPIOF_PIN11) |            \
                                     PIN_ODR_LOW(GPIOF_PIN12) |            \
                                     PIN_ODR_LOW(GPIOF_PIN13) |            \
                                     PIN_ODR_LOW(GPIOF_PIN14) |            \
                                     PIN_ODR_LOW(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0U))

/*
 * GPIOG setup:
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_LOW(GPIOG_PIN0) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN1) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN2) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN3) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN4) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN5) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN6) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN7) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN8) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN9) |          \
                                     PIN_OSPEED_LOW(GPIOG_PIN10) |         \
                                     PIN_OSPEED_LOW(GPIOG_PIN11) |         \
                                     PIN_OSPEED_LOW(GPIOG_PIN12) |         \
                                     PIN_OSPEED_LOW(GPIOG_PIN13) |         \
                                     PIN_OSPEED_LOW(GPIOG_PIN14) |         \
                                     PIN_OSPEED_LOW(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOG_PIN0) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN5) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN7) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN9) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN10) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN11) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN12) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN13) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_LOW(GPIOG_PIN0) |             \
                                     PIN_ODR_LOW(GPIOG_PIN1) |             \
                                     PIN_ODR_LOW(GPIOG_PIN2) |             \
                                     PIN_ODR_LOW(GPIOG_PIN3) |             \
                                     PIN_ODR_LOW(GPIOG_PIN4) |             \
                                     PIN_ODR_LOW(GPIOG_PIN5) |             \
                                     PIN_ODR_LOW(GPIOG_PIN6) |             \
                                     PIN_ODR_LOW(GPIOG_PIN7) |             \
                                     PIN_ODR_LOW(GPIOG_PIN8) |             \
                                     PIN_ODR_LOW(GPIOG_PIN9) |             \
                                     PIN_ODR_LOW(GPIOG_PIN10) |            \
                                     PIN_ODR_LOW(GPIOG_PIN11) |            \
                                     PIN_ODR_LOW(GPIOG_PIN12) |            \
                                     PIN_ODR_LOW(GPIOG_PIN13) |            \
                                     PIN_ODR_LOW(GPIOG_PIN14) |            \
                                     PIN_ODR_LOW(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_LOW(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_LOW(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_LOW(GPIOH_PIN2) |          \
                                     PIN_OSPEED_LOW(GPIOH_PIN3) |          \
                                     PIN_OSPEED_LOW(GPIOH_PIN4) |          \
                                     PIN_OSPEED_LOW(GPIOH_PIN5) |          \
                                     PIN_OSPEED_LOW(GPIOH_PIN6) |          \
                                     PIN_OSPEED_LOW(GPIOH_PIN7) |          \
                                     PIN_OSPEED_LOW(GPIOH_PIN8) |          \
                                     PIN_OSPEED_LOW(GPIOH_PIN9) |          \
                                     PIN_OSPEED_LOW(GPIOH_PIN10) |         \
                                     PIN_OSPEED_LOW(GPIOH_PIN11) |         \
                                     PIN_OSPEED_LOW(GPIOH_PIN12) |         \
                                     PIN_OSPEED_LOW(GPIOH_PIN13) |         \
                                     PIN_OSPEED_LOW(GPIOH_PIN14) |         \
                                     PIN_OSPEED_LOW(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN5) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN7) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN9) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN10) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN11) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN12) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN13) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_LOW(GPIOH_OSC_IN) |           \
                                     PIN_ODR_LOW(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_LOW(GPIOH_PIN2) |             \
                                     PIN_ODR_LOW(GPIOH_PIN3) |             \
                                     PIN_ODR_LOW(GPIOH_PIN4) |             \
                                     PIN_ODR_LOW(GPIOH_PIN5) |             \
                                     PIN_ODR_LOW(GPIOH_PIN6) |             \
                                     PIN_ODR_LOW(GPIOH_PIN7) |             \
                                     PIN_ODR_LOW(GPIOH_PIN8) |             \
                                     PIN_ODR_LOW(GPIOH_PIN9) |             \
                                     PIN_ODR_LOW(GPIOH_PIN10) |            \
                                     PIN_ODR_LOW(GPIOH_PIN11) |            \
                                     PIN_ODR_LOW(GPIOH_PIN12) |            \
                                     PIN_ODR_LOW(GPIOH_PIN13) |            \
                                     PIN_ODR_LOW(GPIOH_PIN14) |            \
                                     PIN_ODR_LOW(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input pullup).
 * PI1  - PIN1                      (input pullup).
 * PI2  - PIN2                      (input pullup).
 * PI3  - PIN3                      (input pullup).
 * PI4  - PIN4                      (input pullup).
 * PI5  - PIN5                      (input pullup).
 * PI6  - PIN6                      (input pullup).
 * PI7  - PIN7                      (input pullup).
 * PI8  - PIN8                      (input pullup).
 * PI9  - PIN9                      (input pullup).
 * PI10 - PIN10                     (input pullup).
 * PI11 - PIN11                     (input pullup).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_LOW(GPIOI_PIN0) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN1) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN2) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN3) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN4) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN5) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN6) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN7) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN8) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN9) |          \
                                     PIN_OSPEED_LOW(GPIOI_PIN10) |         \
                                     PIN_OSPEED_LOW(GPIOI_PIN11) |         \
                                     PIN_OSPEED_LOW(GPIOI_PIN12) |         \
                                     PIN_OSPEED_LOW(GPIOI_PIN13) |         \
                                     PIN_OSPEED_LOW(GPIOI_PIN14) |         \
                                     PIN_OSPEED_LOW(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOI_PIN0) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN9) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN11) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_LOW(GPIOI_PIN0) |             \
                                     PIN_ODR_LOW(GPIOI_PIN1) |             \
                                     PIN_ODR_LOW(GPIOI_PIN2) |             \
                                     PIN_ODR_LOW(GPIOI_PIN3) |             \
                                     PIN_ODR_LOW(GPIOI_PIN4) |             \
                                     PIN_ODR_LOW(GPIOI_PIN5) |             \
                                     PIN_ODR_LOW(GPIOI_PIN6) |             \
                                     PIN_ODR_LOW(GPIOI_PIN7) |             \
                                     PIN_ODR_LOW(GPIOI_PIN8) |             \
                                     PIN_ODR_LOW(GPIOI_PIN9) |             \
                                     PIN_ODR_LOW(GPIOI_PIN10) |            \
                                     PIN_ODR_LOW(GPIOI_PIN11) |            \
                                     PIN_ODR_LOW(GPIOI_PIN12) |            \
                                     PIN_ODR_LOW(GPIOI_PIN13) |            \
                                     PIN_ODR_LOW(GPIOI_PIN14) |            \
                                     PIN_ODR_LOW(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
