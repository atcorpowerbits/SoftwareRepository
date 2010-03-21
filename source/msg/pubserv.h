//---------------------------------------------------------------------------
#ifndef MsgPubservH
#define MsgPubservH
#include <msg\pubtype.h>
//---------------------------------------------------------------------------
//  Enabling/disabling messages
//---------------------------------------------------------------------------
void msg_initialise();
void msg_enable_messages();
void msg_disable_messages();
//---------------------------------------------------------------------------
//  Enabling/disabling memo
//---------------------------------------------------------------------------
void msg_enable_memo(TMemo *pMemo);
void msg_disable_memo();
// replace carriage return on skip
String MsgBox_ReplaceCarriage(String pIn);

int MsgBox_confirmation(String s_body, String s_caption);

int MsgBox_information(String s_body, String s_caption);

int MsgBox_warning(String s_body, String s_caption);


int MsgBox(int id_body, String s_caption, unsigned short Flag);
int MsgBox(String s_body, int id_caption, unsigned short Flag);
int MsgBox(String s_body, String s_caption, unsigned short Flag);
int MsgBox(int id_body, int id_caption, unsigned short Flag);

int MsgBox(int id_body, int id_caption);
int MsgBox(int id_body, String s_caption);
int MsgBox(String s_body, int id_caption);
int MsgBox(String s_body, String s_caption);

int MsgBox(int id_body);
int MsgBox(String s_body);

void MsgBox(TMsgType MsgType, int MsgForUser, int NumMsgForLog);

void MsgBox(TMsgType MsgType, int MsgForUser, int NumMsgForLog, String MsgForLog);

void MsgBox(TMsgType MsgType, String MsgPatientInfo, int MsgForUser,
            int NumMsgForLog);

void MsgBox(TMsgType MsgType, String MsgPatientInfo, int MsgForUser,
            int MsgErrNum, String MsgForLog);

int MsgBox_show(TMsgType  msg_type,
                int       msg_caption_num,
                String    user_msg,
                int       msg_error_num,
                String    log_msg);
#endif
