#include "my_msg.h"
#include "utils.h"

/************************************************************************
 * IPC MESSAGE QUEUE FUNCTIONS
 ************************************************************************/

/**
 * @brief Internal Private Function, not to be used by the students.
 */
int __my_MsgGet( int msgFlags ) {
    int ipcMsgId = msgget( IPC_KEY, msgFlags );
    if ( ipcMsgId < 0 ) {
        debug( "Could not create/open the Message Queue with key=0x%x", IPC_KEY );
    } else {
        debug( "Using the Message Queue with key=0x%x and id=%d", IPC_KEY, ipcMsgId );
    }
    return ipcMsgId;
}

/**
 * @brief Creates an IPC Message Queue NON-exclusively, associated with the IPC_KEY
 * 
 * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
 */
int my_MsgCreate() {
    return __my_MsgGet( IPC_CREAT | 0600 );
}

/**
 * @brief Creates an IPC Message Queue exclusively, associated with the IPC_KEY
 * 
 * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
 */
int my_MsgCreateExcl() {
    return __my_MsgGet( IPC_CREAT | IPC_EXCL | 0600 );
}

/**
 * @brief Opens an already created IPC Message Queue associated with the IPC_KEY
 * 
 * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
 */
int my_MsgGet() {
    return __my_MsgGet( 0 );
}

/**
 * @brief Removes the IPC Message Queue associated with the IPC_KEY
 * 
 * @param ipcMsgId IPC MsgID
 * @return int 0 if success or if the Message Queue already did not exist, or -1 if the Message Queue exists and could not be removed
 */
int my_MsgRemove( int ipcMsgId ) {
    // Ignore any errors here, as this is only to check if the Message Queue exists and remove it
    if ( ipcMsgId > 0 ) {
        // If the Message Queue with IPC_KEY already exists, remove it
        int result = msgctl( ipcMsgId, IPC_RMID, 0 );
        if ( result < 0) {
            debug( "Could not remove the Message Queue with key=0x%x and id=%d", IPC_KEY, ipcMsgId );
        } else {
            debug( "Removed the Message Queue with key=0x%x and id=%d", IPC_KEY, ipcMsgId );
        }
        return result;
    }
    return 0;
}

/**
 * @brief Sends the passed message to the IPC Message Queue associated with the IPC_KEY
 * 
 * @param ipcMsgId IPC MsgID
 * @param ipcMessage Pointer to the IPC Message to be sent
 * @param ipcMessageType IPC Message Type (or Address)
 * @param sizeContents Size of the message contents
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_MsgSend( int ipcMsgId, IPC_Message *ipcMessage, int ipcMessageType, int sizeContents ) {
    ipcMessage->ipcMessageType = ipcMessageType;
    int result = msgsnd( ipcMsgId, ipcMessage, sizeContents, 0 );
    if ( result < 0) {
        debug( "Could not send the Message to the Message Queue with key=0x%x and id=%d", IPC_KEY, ipcMsgId );
    } else {
        debug( "Sent the Message to the Message Queue with key=0x%x and id=%d", IPC_KEY, ipcMsgId );
    }
    return result;
}

/**
 * @brief Reads a message of the passed tipoMensagem from the IPC Message Queue associated with the IPC_KEY
 * 
 * @param ipcMsgId IPC MsgID
 * @param ipcMessage Pointer to the Message to be filled
 * @param ipcMessageType Message Type (or Address)
 * @param sizeContents Size of the message contents
 * @return int Number of bytes read, or -1 in case of error and sets errno with the error value
 */
int my_MsgReceive( int ipcMsgId, IPC_Message *ipcMessage, int ipcMessageType, int sizeContents ) {
    int result = msgrcv( ipcMsgId, ipcMessage, sizeContents, ipcMessageType, 0 );
    if ( result < 0) {
        debug( "Could not Receive the Message of Type %d from the Message Queue with key=0x%x and id=%d", ipcMessageType, IPC_KEY, ipcMsgId );
    } else {
        debug( "Received a Message of Type %d from the Message Queue with key=0x%x and id=%d, with %d bytes", ipcMessageType, IPC_KEY, ipcMsgId, result );
    }
    return result;
}