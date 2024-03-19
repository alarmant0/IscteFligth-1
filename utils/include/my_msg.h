/******************************************************************************
 ** ISCTE-IUL: Protótipos genéricos úteis para manuseamento de IPC
 ******************************************************************************/
#ifndef __MY_MSG_H__
#define __MY_MSG_H__

#include <sys/ipc.h>
#include <sys/msg.h>

#ifndef __IPC_KEY__
#define __IPC_KEY__

/**
 *  KEY to be used on all Linux IPC get operations
 */
#define IPC_KEY 0x0a123456      // Suggestion: Replace with your student number

#endif

#ifndef __IPC_MSG__
#define __IPC_MSG__

/**
 *  Default data type for the message
 */
typedef struct {
    long ipcMessageType;
    int contents;
} IPC_Message;

#endif

/***************************************************************************
 * IPC MESSAGE QUEUE FUNCTIONS (integrates with /home/so/reference/my_msg.c)
 ***************************************************************************/

/**
 * @brief Creates an IPC Message Queue NON-exclusively, associated with the IPC_KEY
 * 
 * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
 */
int my_MsgCreate();

/**
 * @brief Creates an IPC Message Queue exclusively, associated with the IPC_KEY
 * 
 * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
 */
int my_MsgCreateExcl();

/**
 * @brief Opens an already created IPC Message Queue associated with the IPC_KEY
 * 
 * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
 */
int my_MsgGet();

/**
 * @brief Removes the IPC Message Queue associated with the IPC_KEY
 * 
 * @param ipcMsgId IPC MsgID
 * @return int 0 if success or if the Message Queue already did not exist, or -1 if the Message Queue exists and could not be removed
 */
int my_MsgRemove( int ipcMsgId );

/**
 * @brief Sends the passed message to the IPC Message Queue associated with the IPC_KEY
 * 
 * @param ipcMsgId IPC MsgID
 * @param ipcMessage Pointer to the IPC Message to be sent
 * @param ipcMessageType IPC Message Type (or Address)
 * @param sizeContents Size of the message contents
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_MsgSend( int ipcMsgId, IPC_Message *ipcMessage, int ipcMessageType, int sizeContents );

/**
 * @brief Reads a message of the passed tipoMensagem from the IPC Message Queue associated with the IPC_KEY
 * 
 * @param ipcMsgId IPC MsgID
 * @param ipcMessage Pointer to the Message to be filled
 * @param ipcMessageType Message Type (or Address)
 * @param sizeContents Size of the message contents
 * @return int Number of bytes read, or -1 in case of error and sets errno with the error value
 */
int my_MsgReceive( int ipcMsgId, IPC_Message *ipcMessage, int ipcMessageType, int sizeContents );

#endif