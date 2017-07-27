#ifndef CIA402DEVICEICANBUS_H
#define CIA402DEVICEICANBUS_H

#include "hico_api.h"
#include "co_msg.h"
#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
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
    long Init(unsigned int canIndex, string canPort);
    int SendMessage(co_msg input, unsigned int canIndex);
    vector<int> canPorts;
    int ret;
    can_msg SetCanMsg();


private:

    long co2c(const co_msg & input, can_msg & output);
    can_msg send_msg;
    long prueba;
};

#endif // CIA402DEVICEICANBUS_H
