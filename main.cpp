#include <iostream>

using namespace std;

#include "CiA402DeviceICanbus.h"

int main(int argc, char *argv[])
{
    CiA402DeviceICanbus com;
    can_msg can_in,can;
    co_msg input, output;
    uint8_t msg_start[]={0x06,0x00};//={0x81,0x00};
    vector<uint8_t> co_data_frame(2,msg_start[0]);
    //com.SetCanMsg(can,msg_start);
    cout<<"main-----" << sizeof(msg_start)/sizeof(msg_start[0])<<endl;
    input=com.SetCanOpenMsg(0x206,0,co_data_frame);
    //com.SetCanMsg(can,msg_start);
    //com.c2co(can,input);
    if (com.SendMessage(input,0)<0){
        cout<<"error al enviar el mensaje"<<endl;
    }
    else{
        //for(int i=0; i<10; i++){
            if (com.WaitForReadMessage(output,0)<0){
                cout<<"error al recibir el mensaje"<<endl;
            }
        //}
    }

    return 0;
}
