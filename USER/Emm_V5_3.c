#include "Emm_V5.h"

void Emm_V5_Vel_Control3(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF)
{
  __IO static uint8_t cmd[16] = {0};

  cmd[0] =  addr;
  cmd[1] =  0xF6;
  cmd[2] =  dir;
  cmd[3] =  (uint8_t)(vel >> 8);
  cmd[4] =  (uint8_t)(vel >> 0);
  cmd[5] =  acc;
  cmd[6] =  snF;
  cmd[7] =  0x6B;
  
  usart_SendCmd3(cmd, 8);
}

void Emm_V5_Pos_Control3(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF)
{
  __IO static uint8_t cmd[16] = {0};

  cmd[0]  =  addr;
  cmd[1]  =  0xFD;
  cmd[2]  =  dir;
  cmd[3]  =  (uint8_t)(vel >> 8);
  cmd[4]  =  (uint8_t)(vel >> 0);
  cmd[5]  =  acc;
  cmd[6]  =  (uint8_t)(clk >> 24);
  cmd[7]  =  (uint8_t)(clk >> 16);
  cmd[8]  =  (uint8_t)(clk >> 8);
  cmd[9]  =  (uint8_t)(clk >> 0);
  cmd[10] =  raF;
  cmd[11] =  snF;
  cmd[12] =  0x6B;
  
  usart_SendCmd3(cmd, 13);
}

void Emm_V5_En_Control3(uint8_t addr, bool state, bool snF)
{
  __IO static uint8_t cmd[16] = {0};

  cmd[0] =  addr;
  cmd[1] =  0xF0;
  cmd[2] =  state;
  cmd[3] =  snF;
  cmd[4] =  0x6B;
  
  usart_SendCmd3(cmd, 5);
}

void Emm_V5_Stop_Now3(uint8_t addr, bool snF)
{
  __IO static uint8_t cmd[16] = {0};

  cmd[0] =  addr;
  cmd[1] =  0xFE;
  cmd[2] =  0x98;
  cmd[3] =  snF;
  cmd[4] =  0x6B;
  
  usart_SendCmd3(cmd, 5);
}

void Emm_V5_Synchronous_motion3(uint8_t addr)
{
  __IO static uint8_t cmd[16] = {0};

  cmd[0] =  addr;
  cmd[1] =  0xFF;
  cmd[2] =  0x66;
  cmd[3] =  0x6B;
  
  usart_SendCmd3(cmd, 4);
}
