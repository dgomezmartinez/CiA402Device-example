#ifndef CIA402DEVICEICANBUS_H
#define CIA402DEVICEICANBUS_H

#include "co_msg.h"
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <errno.h>
#include <err.h>
#include <assert.h>
#include <bitset>
#include <vector>
#include "hico_api.h"

using namespace std;

class CiA402DeviceICanbus
{
public:

    CiA402DeviceICanbus();
   // CiA402DeviceICanbus(string canPort);
    CiA402DeviceICanbus(long number, string canPort);
    long Init(const vector<int> &new_canPorts, string canPort);
    int SendMessage(co_msg input, unsigned int canIndex);
    vector<int> canPorts;
    int ret;
    can_msg SetCanMsg();


    co_msg SetCanOpenMsg();

    int WaitForReadMessage(co_msg &output, unsigned int canIndex);
    long c2co(const can_msg &input, co_msg &output);
    int SetCanOpenMsg(co_msg &msg_co);
    int SetCanOpenMsg(co_msg &msg_co, uint8_t msg_start[]);
    can_msg SetCanMsg(can_msg &msg, uint8_t msg_start[]);
    co_msg SetCanOpenMsg(unsigned short nodeID, unsigned short fund_code, uint8_t msg_start[]);
private:
    int read_timeout(int fd, can_msg *buf, unsigned int timeout);
    long co2c(const co_msg & input, can_msg & output);
    can_msg send_msg;
    long prueba;
};

#endif // CIA402DEVICEICANBUS_H
