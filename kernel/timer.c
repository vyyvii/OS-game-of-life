// OS-Game-Of-Life
// TIMER FILE

#include "kernel.h"

/**
 * @brief Busy-wait delay based on timer ticks.
 *
 * Suspends execution until a specified number of timer ticks has elapsed.
 * This function relies on a global tick counter (typically incremented
 * by the PIT IRQ0 handler).
 *
 * The function performs a busy-wait loop:
 * it continuously checks the difference between the current tick count
 * and the starting tick until the desired delay is reached.
 *
 * @param ms Number of ticks to wait (not real milliseconds unless
 *           the timer frequency is configured accordingly).
 *
 * @note The actual time represented by one tick depends on the PIT frequency.
 *       For example:
 *       - At 100 Hz → 1 tick = 10 ms
 *       - At 1000 Hz → 1 tick = 1 ms
 *
 * @warning This is a blocking busy-wait:
 * - CPU is fully occupied during the delay.
 * - Not suitable for multitasking or power-efficient systems.
 *
 * @warning The global variable `ticks` must be declared as `volatile`
 *          and updated in the timer interrupt handler.
 */
void sleep(uint32_t ms)
{
    uint32_t start = ticks;
    uint32_t wait = ms;

    while (ticks - start < wait);
}

/**
 * @brief Increase ticks by one
 */
void timer_handler(void)
{
    ticks++;
}

/**
 * @brief Initialize the Programmable Interval Timer (PIT).
 *
 * Configures the PIT (channel 0) to generate periodic hardware
 * interrupts (IRQ0) at the specified frequency. This is commonly
 * used to implement timing features such as delays, scheduling,
 * or animation updates in the kernel.
 *
 * The PIT runs at a base frequency of 1,193,180 Hz. A divisor is
 * computed to scale this frequency down to the desired rate:
 *
 *     divisor = 1193180 / freq
 *
 * The divisor is then sent to the PIT through I/O ports to define
 * the interrupt frequency.
 *
 * @param freq Desired frequency in Hertz (interrupts per second).
 *
 * @note Requires:
 * - PIC to be properly remapped.
 * - IRQ0 handler to be installed in the IDT.
 * - Interrupts enabled (sti).
 *
 * @warning A frequency too high may cause performance issues,
 * while a frequency too low reduces timing precision.
 */
void init_timer(uint32_t freq)
{
    uint32_t divisor = BASE_PIT_FREQ / freq;        // How many ticks to trigger a interruption of IRQ0

    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}

// DEFAUCHY | 2026
