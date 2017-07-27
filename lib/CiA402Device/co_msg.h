#ifndef CO_MSG_H
#define CO_MSG_H

/* Estrura del mensaje en CanOpen */
struct co_msg
{
    union{
    uint16_t id_co;
#ifdef HICO_LE
    struct {
        /* Remote transmission request flag */
        uint16_t rtr:1;

        /* Node ID */
        uint16_t nodeID:7;

        /* Function Code */
        uint16_t fun_code:4;
    };
#elif defined(HICO_BE)
    struct {
        uint16_t fun_code:4;
        uint16_t nodeID:7;
        uint16_t rtr:1;
    };
#endif
    };
    /* Timestamp in microseconds */
    uint32_t ts;

    uint16_t dlc_co;

    /* CAN message data */
    uint8_t data_co[8];

};

#endif // CO_MSG_H
