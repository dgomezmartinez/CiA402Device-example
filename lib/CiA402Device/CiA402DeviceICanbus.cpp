#include "CiA402DeviceICanbus.h"

//Constructor vacío (inicializa el can0)
CiA402DeviceICanbus::CiA402DeviceICanbus()
{
    Init( vector<int>(1) , "/dev/can" );
    //canPorts={0};
}

//Inicializa todos los puertos que introduzcas
CiA402DeviceICanbus::CiA402DeviceICanbus(long number, string canPort)
{

    canPorts.resize(number);
    for (int i=0; number; i++)
    {
        canPorts[i]=i;
    }
    Init(canPorts,canPort);

}

//Función para inicializar los puertos
long CiA402DeviceICanbus::Init(const vector<int> & new_canPorts, string canPort)
{
    int val;
    string portName;
    stringstream index;

    canPorts=new_canPorts;


    for(int canIndex=0;canIndex<canPorts.size();canIndex++)
    {
        index<<canIndex;
        portName=canPort+index.str();
        canPorts[canIndex] = open(portName.c_str(), O_RDWR);

        /* Reset the board. Which node is used for this doesn't matter */
        if(ioctl(canPorts[canIndex],IOC_RESET_BOARD)!=0){
        err(1, "could not reset board");
        }

        /* Set baudrate for both nodes */
        val=BITRATE_1000k;
        if(ioctl(canPorts[canIndex],IOC_SET_BITRATE,&val)!=0){
        err(1, "could not set bitrate");
        }

        /* Start both CAN nodes */
        if(ioctl(canPorts[canIndex],IOC_START)!=0){
        err(1, "IOC_START");
        }
    }

    return 0;
}

//Funcion para construir mensaje en CanBus
can_msg CiA402DeviceICanbus::SetCanMsg()
{
    can_msg msg;
    uint8_t msg_start[] = {0x81,0x01};// en amensajes de red primer byte el comando y segundo el ID
    //uint8_t msg_stop[] = {0x81,0x00};//Ver que mandar
    /* Compose a CAN message with some dummy data */
    msg.ff = FF_NORMAL;
    msg.id = 0x00;//x0B; 00 mensaje de red
    //tx_msg.id = 0x08;
    msg.dlc = 2;
    memcpy(msg.data, msg_start, 2*sizeof(uint8_t));
    for(int i=0;i<msg.dlc;i++){
    msg.data[i]=msg_start[i];
    }
    return msg;
}

co_msg CiA402DeviceICanbus::SetCanOpenMsg(){

    co_msg msg_co;
    uint8_t msg_start[] = {0x81,0x01};
    memcpy(msg_co.data_co, msg_start, 2*sizeof(uint8_t));
    msg_co.id_co=0;
//    msg_co.nodeID=0;
//    msg_co.rtr=0;


}

/* Transforma mensaje de canopen a can y lo envía a can0 */
int CiA402DeviceICanbus::SendMessage(co_msg input, unsigned int canIndex)
{
    send_msg=SetCanMsg();
    if (co2c(input,send_msg) < 0){
        cout<<"Error al transformar el mensaje"<<endl;
    }

    else{

        /* Write the message to the Can0 */
        if(write(canPorts[canIndex],&send_msg,sizeof(struct can_msg))!=sizeof(send_msg)){
        err(1, "Failed to send message");
        }
    }
    return 0;
}

long CiA402DeviceICanbus::co2c(const co_msg & input, can_msg & output)
{
    output.id=input.id_co>>1;
    output.fi=input.id_co;
    output.fi<<=4;
    output.fi+=input.dlc_co;
    output.ts=input.ts;

    for( int i=0; i < 8; i++)
    {
        output.data[i] = input.data_co[i];
    }
    return 0;
}
