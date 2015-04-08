#ifndef __APP_PROTOCOL_H__
#define __APP_PROTOCOL_H__

#ifdef __cplusplus
 extern "C" {
#endif


#define LED_PLC_TOGGLE()        BSP_LED_Toggle(LED_PLC)
#define LED_PLC_OFF()           LED_Off(LED_PLC)
#define LED_PLC_ON()            LED_On(LED_PLC)

//#define PLC_ADDR_SIZE           sizeof(g_send_para_pkg.relayAddr)/sizeof(g_send_para_pkg.relayAddr[0])

//#define PLC_ADDR_SIZE()         LISTVIEW_GetNumRows(RLY_GetListAddr())

#define mPLC_REPLY_ADDR_LEN    sizeof(mPLC_REPLY_ADDR)

#define FREQ_NUM               2

#define FREQ_270KHz            0
#define FREQ_421KHz            1

#define FREQ_INDEX             0
#define FREQ_LEN               1

#define DL645_INDEX           (FREQ_INDEX + FREQ_LEN)  

//启动中继条件下，控制字的附加值
#define DL645_RELAY_ADDED_VAL    0x20

#define RF_SEND_FIX_LEN         37
#define RF_RECV_FIX_LEN          RF_SEND_FIX_LEN + 4

#define RF_PRINT_FIX_LEN       8

#define RF_SEND_BUF         rf_send_buf
#define RF_SEND_LEN         rf_send_len
#define RF_RECV_BUF         g_rf_param.rx.buf
#define RF_RECV_LEN         g_rf_param.rx.rx_len

#define PLC_270_III              0
#define PLC_270_III_5            1
#define PLC_270_II               2
#define PLC_421_50BPS            3
#define PLC_421_100BPS           4
#define PLC_421_600BPS           5
#define PLC_421_1200BPS          6

#define PLC_BPS_SNAIL            15
#define PLC_BSP_100              10
#define PLC_BPS_SLOW             6
#define PLC_BPS_MIDDLE           5         
#define PLC_BPS_FAST             4
//#define PLC_BPS_HIGH             4




#define PLC_RES_SUCC           0
#define PLC_RES_FAIL           1
#define PLC_RES_TIMEOUT        2
#define PLC_RES_ERROR_FRAME    3
#define PLC_RES_NONE           4



#define PLC_MSG_NOINIT              0
#define PLC_MSG_IDLE                1
#define PLC_MSG_SENDING             2
#define PLC_MSG_RECEIVED            3


#define GUI_PLC_MSG_IDLE        0
#define GUI_PLC_MSG_TEST        1    //规约调试
#define GUI_PLC_MSG_READ        2    //抄表
#define GUI_PLC_MSG_SET         3    //载波设置
#define GUI_PLC_MSG_LISTING     4    //状态监控
#define GUI_PLC_MSG_MEMORY      5    //内存管理
#define GUI_PLC_MSG_FREQ        6    //速率设置

typedef struct _plc_prm
{
    u8 send_buf[256]; //DL645发送帧
    u16 send_len; //DL645发送帧长度

    u8 recv_buf[256]; //DL645接收帧
    u16 recv_len; //DL645接收帧长度

    u8 data_buf[30]; //提取数据
    u16 data_len; //提取数据的长度

    u8 sd_buf[512];

    u8 sendStatus;
    u8 result; //PLC通信结果: PLC_RES_SUCC、PLC_RES_FAIL、PLC_RES_TIMEOUT    
} PLC_PRM, *P_PLC_PRM;

extern OS_EVENT *g_sem_plc;
extern OS_EVENT *g_sem_rf;
extern u8 g_cur_freq;
extern PLC_PRM g_plc_prm;

extern const INT8U lBroadcast_Read_Meter[12];//高低温测试用


u16 pc_uart_send(u8 *buf, u16 len);
u16 plc_uart_send(u8 *buf, u16 len);
u16 cplc_read_addr(void);
unsigned int PC_postProcess(pvoid h);
unsigned int RS485_postProcess(pvoid h);
unsigned int PLC_postProcess(pvoid h);
void App_TaskPLC(void *p_arg);


#ifdef __cplusplus
}
#endif

#endif
