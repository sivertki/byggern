#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>
#include "SRAMDriver.h"

#include <util/delay.h>

void SRAM_test(void) {
  volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
  uint16_t ext_ram_size = 0x800;
  uint16_t write_errors = 0;
  uint16_t retrieval_errors = 0;
  printf("Starting SRAM test...\n\r");
  // rand() stores some internal state, so calling this function in a loop will
  // yield different seeds each time (unless srand() is called before this function)
  uint16_t seed = rand();
  // Write phase: Immediately check that the correct value was stored
  srand(seed);
  for (uint16_t i = 0; i < ext_ram_size; i++) {
    uint8_t some_value = rand();
    ext_ram[i] = some_value;
    uint8_t retreived_value = ext_ram[i];
    if (retreived_value != some_value) {
      printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
      write_errors++;
    }
  }
  // Retrieval phase: Check that no values were changed during or after the write phase
  srand(seed); // reset the PRNG to the state it had before the write phase
  for (uint16_t i = 0; i < ext_ram_size; i++) {
    uint8_t some_value = rand();
    uint8_t retreived_value = ext_ram[i];
    if (retreived_value != some_value) {
      printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
      retrieval_errors++;
    }
  }
  printf("SRAM test completed with \n\r%4d errors in write phase and \n\r%4d errors in retrieval phase\n\r\n\r", write_errors, retrieval_errors);
}

void SRAM_init(void) {
    MCUCR = (1 << SRE); //XMEM enable
    SFIOR = (1 << XMM2); //masking unused bits

    /* HIGHSCORE RESET
    for(int i = 0; i < 5; i++) {
      SRAM_highscoreW(5 - i, i);
    }
    */
}

void SRAM_highscoreW(uint8_t score, uint8_t position) {
  volatile char *hs_ram_start = (char *) 0x1FF0;
  hs_ram_start[position] = score;
  if(SRAM_highscoreR(position) != score) {
    SRAM_highscoreW(score, position);
  }
  //printf("Writing score %u to position %u in SRAM", score, position);
}

uint8_t SRAM_highscoreR(uint8_t position) {
  volatile char *hs_ram_start = (char *) 0x1FF0;
  //printf("Reading score %u from position %u in SRAM", hs_ram_start[position], position);
  return hs_ram_start[position];
}
