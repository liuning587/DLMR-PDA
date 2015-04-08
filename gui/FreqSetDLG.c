
#include "includes.h"
#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0  (GUI_ID_USER + 0x00)
#define ID_LISTBOX_0 (GUI_ID_USER + 0x01)
#define ID_LISTBOX_1 (GUI_ID_USER + 0x02)

#define ID_TEXT_0    (GUI_ID_USER + 0x03)
#define ID_TEXT_1    (GUI_ID_USER + 0x04)

#define ID_BUTTON_0  (GUI_ID_USER + 0x05)
#define ID_BUTTON_1  (GUI_ID_USER + 0x06)




/*********************************************************************
*
*       _aDialogCreate
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect,  "Speed",    ID_WINDOW_0,  0,   0,   240, 295, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect, "Listbox",  ID_LISTBOX_0, 5,   26,  228, 84,  0, 0x0, 0 },
  { TEXT_CreateIndirect,    FRQ_Flag,   ID_TEXT_0,    8,   8,   100, 20,  0, 0x0, 0 },
  { LISTBOX_CreateIndirect, "Listbox",  ID_LISTBOX_1, 5,   134, 228, 122, 0, 0x0, 0 },
  { TEXT_CreateIndirect,    FE_Speed,   ID_TEXT_1,    8,   114, 150, 20,  0, 0x0, 0 },
  { BUTTON_CreateIndirect,  FreqSet,    ID_BUTTON_0,  5,   267, 55,  20,  0, 0x0, 0 },
  { BUTTON_CreateIndirect,  Quit,       ID_BUTTON_1,  175, 267, 55,  20,  0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};


void FRQ_SetFocus(void)
{
    if(g_hWin_ReadMeter > 0)
    {
       WM_SetFocus(g_hWin_ReadMeter);
       RMD_SetFocus();
    }
    else if(g_hWin_std > 0)
    {
       WM_SetFocus(g_hWin_std);
       CPT_SetFocus();
    }
    else if((g_hWin_para > 0)&&(g_hWin_AdvanSet < 0))
    {
       WM_SetFocus(g_hWin_para);
    }
    else if(g_hWin_AdvanSet > 0)
    {
       WM_SetFocus(g_hWin_AdvanSet);
       ADS_SetFocus();
    }
}



void FRQ_FreqSel(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    int SelNum;
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1);
    SelNum = LISTBOX_GetSel(hItem);
    switch(SelNum)
    {
        case 0:
            g_sys_register_para.freqSel = PLC_270_III;
            g_sys_register_para.bpsSpeed = PLC_BPS_MIDDLE;
            break;
            
        case 1:
            g_sys_register_para.freqSel = PLC_270_III_5;
            g_sys_register_para.bpsSpeed = PLC_BPS_SLOW;
            break;
        case 2:
            g_sys_register_para.freqSel = PLC_270_II;
            g_sys_register_para.bpsSpeed = PLC_BPS_MIDDLE;
            break;
        case 3:
            g_sys_register_para.freqSel = PLC_421_50BPS;
            g_sys_register_para.bpsSpeed = PLC_BPS_SNAIL;
            break;
        case 4:
            g_sys_register_para.freqSel = PLC_421_100BPS;
            g_sys_register_para.bpsSpeed = PLC_BSP_100;
            break;
        case 5:
            g_sys_register_para.freqSel = PLC_421_600BPS;
            g_sys_register_para.bpsSpeed = PLC_BPS_MIDDLE;
            break;
        case 6:
            g_sys_register_para.freqSel = PLC_421_1200BPS;
            g_sys_register_para.bpsSpeed = PLC_BPS_MIDDLE;
            break;
    }
}



void FRQ_PreamSel(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    int SelNum;
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
    SelNum = LISTBOX_GetSel(hItem);
    switch(SelNum)
    {
        case 0:
            g_sys_register_para.preamble = 0xFC;
            g_sys_register_para.bpsSpeed = PLC_BPS_SLOW;
            break;
        case 1:
            g_sys_register_para.preamble = 0xFA;
            g_sys_register_para.bpsSpeed = PLC_BPS_MIDDLE;
            break;
        case 2:
            g_sys_register_para.preamble = 0xFB;
            g_sys_register_para.bpsSpeed = PLC_BPS_MIDDLE;
            break;
        case 3:
            g_sys_register_para.preamble = 0xFD;
            g_sys_register_para.bpsSpeed = PLC_BSP_100;
            break;
        case 4:
            g_sys_register_para.preamble = 0xFF;
            g_sys_register_para.bpsSpeed = PLC_BPS_SNAIL;
            break;
        case 5:
            g_sys_register_para.preamble = 0xFE;
            //FRQ_FreqSel(pMsg);
            //g_send_para_pkg.cmdType = PLC_CMD_FREQ_SET;
            break;
        default:
            break;
    }
}


/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  int     SelNum;
  int     i;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Listbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
    for(i = 0;i < 6;i++)
    {
        LISTBOX_AddString(hItem, pTextPreamble[i]);
    }
    switch(g_sys_register_para.preamble)
    {
        case 0xFC:
            LISTBOX_SetSel(hItem,0);
            break;
        case 0xFA:
            LISTBOX_SetSel(hItem,1);
            break;
        case 0xFB:
            LISTBOX_SetSel(hItem,2);
            break;
        case 0xFD:
            LISTBOX_SetSel(hItem,3);
            break;
        case 0xFF:
            LISTBOX_SetSel(hItem,4);
            break;
        case 0xFE:
            LISTBOX_SetSel(hItem,5);
            break;
    }
    //
    // Initialization of 'Listbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_1);
    for(i = 0;i < 7;i++)
    {
        LISTBOX_AddString(hItem, pTextSpeed[i]);
    }
    switch(g_sys_register_para.freqSel)
    {
        case PLC_270_III:
            LISTBOX_SetSel(hItem,0);
            break;
        case PLC_270_III_5:
            LISTBOX_SetSel(hItem,1);
            break;
        case PLC_270_II:
            LISTBOX_SetSel(hItem,2);
            break;
        case PLC_421_50BPS:
            LISTBOX_SetSel(hItem,3);
            break;
        case PLC_421_100BPS:
            LISTBOX_SetSel(hItem,4);
            break;
        case PLC_421_600BPS:
            LISTBOX_SetSel(hItem,5);
            break;
        case PLC_421_1200BPS:
            LISTBOX_SetSel(hItem,6);
            break;
    
    }

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
    BUTTON_SetBkColor(hItem,0,GUI_GREEN);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
    BUTTON_SetBkColor(hItem,0,GUI_YELLOW);

    break;
    
  case WM_KEY:
    if((((WM_KEY_INFO *)(pMsg->Data.p))->PressedCnt)==0)
    {   
        switch(((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
            case GUI_KEY_GREEN:
                if(g_hWin_ReadMeter > 0)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTBOX_0);
                    SelNum = LISTBOX_GetSel(hItem);
                    if(SelNum != 5) //前导符不是FE
                    {
                        hItem = RMD_Get_Speed();
                        EDIT_SetText(hItem,pTextPreamble[SelNum]);
                    }
                    else if(SelNum == 5)
                    {
                        hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTBOX_1);
                        SelNum = LISTBOX_GetSel(hItem);
                        hItem = RMD_Get_Speed();
                        EDIT_SetText(hItem,pTextSpeed[SelNum]);
                    }
                }
                else if(g_hWin_std > 0)
                {
                    hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTBOX_0);
                    SelNum = LISTBOX_GetSel(hItem);
                    if(SelNum != 5) //前导符不是FE
                    {
                        hItem = CPT_Get_Speed();
                        EDIT_SetText(hItem,pTextPreamble[SelNum]);
                    }
                    else if(SelNum == 5)
                    {
                        hItem = WM_GetDialogItem(pMsg->hWin,ID_LISTBOX_1);
                        SelNum = LISTBOX_GetSel(hItem);
                        hItem = CPT_Get_Speed();
                        EDIT_SetText(hItem,pTextSpeed[SelNum]);
                    }
                }
                else if(g_hWin_para > 0)
                {
                    //保留
                }
                FRQ_PreamSel(pMsg);
                if(0xFE == g_sys_register_para.preamble)
                {
                    FRQ_FreqSel(pMsg);
                    g_send_para_pkg.cmdType = PLC_CMD_FREQ_SET;
                    g_sys_control.guiState = GUI_PLC_MSG_FREQ;
                    OSMboxPost(g_sys_control.downMb, (void*)&g_send_para_pkg);
                }
                DEV_Parameters_Write();//保存数据
                
                WM_DeleteWindow(g_hWin_speed);
                g_hWin_speed = HBWIN_NULL;
                FRQ_SetFocus();
                break;

            case GUI_KEY_YELLOW:
                WM_DeleteWindow(g_hWin_speed);
                g_hWin_speed = HBWIN_NULL;
                FRQ_SetFocus();
                break;
        }
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateSpeed
*/
WM_HWIN CreateSpeed(WM_HWIN hParentWin);
WM_HWIN CreateSpeed(WM_HWIN hParentWin) 
{
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, hParentWin, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
