#include <iostream>

using namespace std;

#include "CiA402DeviceICanbus.h"

int main(int argc, char *argv[])
{
    CiA402DeviceICanbus com;
    co_msg msg;
    uint8_t msg_start[]={0};
    msg=com.SetCanOpenMsg(0,0,msg_start);
    if (com.SendMessage(msg,0)<0){
        cout<<"error al enviar el mensaje"<<endl;
    }
    else{
        if (com.WaitForReadMessage(msg,0)<0){
            cout<<"error al recibir el mensaje"<<endl;
        }
    }
    return 0;
}
