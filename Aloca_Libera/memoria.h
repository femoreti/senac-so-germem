#include <stdint.h>

#define SIZE 100

int8_t memoria[SIZE];

void initialize();
void show();
void *Aloca(unsigned int memory);
void Libera(void *index);