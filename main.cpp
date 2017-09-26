#include <iostream>

using namespace std;

#include "CiA402DeviceICanbus.h"

int main(int argc, char *argv[])
{
    CiA402DeviceICanbus com;
    can_msg can;
    co_msg input;
    co_msg output;
    uint8_t msg_start[]={0x81,0x00};
    com.SetCanMsg(can,msg_start);
    com.c2co(can,input);
    if (com.SendMessage(input,0)<0){
        cout<<"error al enviar el mensaje"<<endl;
    }
    else{
        if (com.WaitForReadMessage(output,0)<0){
            cout<<"error al recibir el mensaje"<<endl;
        }
    }
    cout << "hello";
    return 0;
}
