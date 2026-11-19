/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.


*******************************************************************************/
#define SIMULATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef SIMULATE
#include <pigpio.h>
#endif

#define PIN 17
#define DEFAULT_MIN 68.0
#define DEFAULT_MAX 76.0
#define LOG_FILE "temperatures.csv"

static int set_led(int on) {
#ifdef SIMULATE
(void)on;
return 0;
#else
return gpioWrite(PIN, on ? 1 : 0);
#endif
}

static int read_number(const char *prompt, double *value) {
char line[128], extra;
printf("%s", prompt);
if (!fgets(line, sizeof(line), stdin)) return 0;
if (sscanf(line, " %lf %c", value, &extra) != 1 || !isfinite(*value)) return -1;
return 1;
}

int main(void) {
double min_temp = DEFAULT_MIN, max_temp = DEFAULT_MAX;
double value, total = 0;
int count = 0, rc;
FILE *log = NULL;
#ifndef SIMULATE
if (gpioInitialise() < 0) {
fprintf(stderr, "GPIO initialization failed.\n");
return 1;
}
if (gpioSetMode(PIN, PI_OUTPUT) != 0 || set_led(0) != 0) {
fprintf(stderr, "GPIO setup failed.\n");
gpioTerminate();
return 1;
}
#endif
puts("SMART CLASSROOM COMFORT MONITOR");
while (1) {
rc = read_number("Minimum acceptable temperature (F): ", &value);
if (rc == 0) goto done;
if (rc == 1) { min_temp = value; break; }
puts("Invalid number. Try again.");
}
while (1) {
rc = read_number("Maximum acceptable temperature (F): ", &value);
if (rc == 0) goto done;
if (rc == 1 && value >= min_temp) { max_temp = value; break; }
puts("Invalid maximum: enter a number >= minimum.");
}
log = fopen(LOG_FILE, "a+");
if (!log) { perror("Cannot open log file"); goto done; }
if (fseek(log, 0, SEEK_END) == 0 && ftell(log) == 0)
fprintf(log, "Temperature_F,Status,LED\n");
printf("Acceptable range: %.1fF - %.1fF\n", min_temp, max_temp);
puts("Enter -999 to finish.\n");
while (1) {
rc = read_number("Enter temperature (F): ", &value);
if (rc == 0) break;
if (rc < 0) { puts("Invalid number. Try again."); continue; }
if (value == -999) break;
int warning = (value < min_temp || value > max_temp);
const char *status = warning ? "WARNING" : "NORMAL";
const char *led = warning ? "ON" : "OFF";
if (set_led(warning) != 0) { fprintf(stderr, "LED write failed.\n"); break; }
printf("Temperature: %.1fF | Status: %s | LED: %s\n", value, status, led);
fprintf(log, "%.1f,%s,%s\n", value, status, led);
fflush(log);
total += value;
count++;
}
if (count) printf("Average temperature: %.2fF\n", total / count);
else puts("No temperatures recorded.");
printf("Readings saved to %s\n", LOG_FILE);
done:
if (log) fclose(log);
set_led(0);
#ifndef SIMULATE
gpioTerminate();
#endif

return 0;
}
