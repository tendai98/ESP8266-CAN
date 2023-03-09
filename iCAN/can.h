#include <SPI.h>
#include <mcp2515.h>

#define MAX_FRAME_LEN 13
#define CHIP_SELECT D8
#define TARGET_BITRATE CAN_500KBPS
#define TARGET_CLOCK   MCP_8MHZ

MCP2515 canDevice(CHIP_SELECT);
struct can_frame canMsg;

void initNormalCAN(){
  canDevice.reset();
  canDevice.setBitrate(TARGET_BITRATE, TARGET_CLOCK);
  canDevice.setNormalMode();
}

void initLoopbackCAN(){
  canDevice.reset();
  canDevice.setBitrate(TARGET_BITRATE);
  canDevice.setLoopbackMode();
}

void canSend(uint8_t * data) {

    canMsg.can_id = *((canid_t *) data);
    canMsg.can_dlc = CAN_MAX_DLC;

    canMsg.data[0] = *((char*) data+0x5);
    canMsg.data[1] = *((char*) data+0x6);
    canMsg.data[2] = *((char*) data+0x7);
    canMsg.data[3] = *((char*) data+0x8);
    canMsg.data[4] = *((char*) data+0x9);
    canMsg.data[5] = *((char*) data+0xA);
    canMsg.data[6] = *((char*) data+0xB);
    canMsg.data[7] = *((char*) data+0xC);

    canDevice.sendMessage(&canMsg);
}

int canRecv(){
  return (canDevice.readMessage(&canMsg) == MCP2515::ERROR_OK) ? 1 : 0;
}
