#include <stdio.h>


uint8_t MCP_init();
uint8_t MCP_reads(uint8_t address);
void MCP_writes(uint8_t address, uint8_t data);
void MCP_requestToSend(uint8_t select);
void MCP_bitModify(uint8_t address, uint8_t mask, uint8_t data);
uint8_t MCP_readStatus();
