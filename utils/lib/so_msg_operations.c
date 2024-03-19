#include "common.h"
#include "utils.h"

/**
 * @brief Internal Private Function, not to be used by the students.
 */
int __msgGet( int msgFlags ) {
    int msgId = msgget( IPC_KEY, msgFlags );
    if ( msgId < 0 ) {
        debug( "Could not create/open the Message Queue with key=0x%x", IPC_KEY );
    } else {
        debug( "Using the Message Queue with key=0x%x and id=%d", IPC_KEY, msgId );
    }
    return msgId;
}

/**
 * @brief Creates an IPC Message Queue NON-exclusively, associated with the IPC_KEY, of an array of size multiple of sizeof(Aluno)
 * 
 * @return int msgId. In case of error, returns -1
 */
int msgCreate() {
    return __msgGet( IPC_CREAT | 0600 );
}

/**
 * @brief Opens an already created IPC Message Queue associated with the IPC_KEY
 * 
 * @return int msgId. In case of error, returns -1
 */
int msgGet() {
    return __msgGet( 0 );
}

/**
 * @brief Removes the IPC Message Queue associated with the IPC_KEY
 * 
 * @return int 0 if success or if the Message Queue already did not exist, or -1 if the Message Queue exists and could not be removed
 */
int msgRemove() {
    int msgId = msgGet();
    // Ignore any errors here, as this is only to check if the Message Queue exists and remove it
    if ( msgId > 0 ) {
        // If the Message Queue with IPC_KEY already exists, remove it
        int result = msgctl( msgId, IPC_RMID, 0 );
        if ( result < 0) {
            debug( "Could not remove the Message Queue with key=0x%x and id=%d", IPC_KEY, msgId );
        } else {
            debug( "Removed the Message Queue with key=0x%x and id=%d", IPC_KEY, msgId );
        }
        return result;
    }
    return 0;
}

/**
 * @brief Sends the passed message to the IPC Message Queue associated with the IPC_KEY
 * 
 * @param msgId IPC MsgID
 * @param mensagem Pointer to the Message to be sent
 * @param tipoMensagem Message Type (or Address)
 * @param sizeConteudo Size of the message contents
 * @return int success
 */
int msgSend( int msgId, Mensagem* mensagem, int tipoMensagem, int sizeConteudo ) {
    mensagem->tipoMensagem = tipoMensagem;
    int result = msgsnd(msgId, mensagem, sizeConteudo, 0);
    if ( result < 0) {
        debug( "Could not send the Message to the Message Queue with key=0x%x and id=%d", IPC_KEY, msgId );
    } else {
        debug( "Sent the Message to the Message Queue with key=0x%x and id=%d", IPC_KEY, msgId );
    }
    return result;
}

/**
 * @brief Reads a message of the passed tipoMensagem from the IPC Message Queue associated with the IPC_KEY
 * 
 * @param msgId IPC MsgID
 * @param mensagem Pointer to the Message to be filled
 * @param tipoMensagem Message Type (or Address)
 * @param sizeConteudo Size of the message contents
 * @return int Number of bytes read, or -1 in case of error
 */
int msgReceive( int msgId, Mensagem* mensagem, int tipoMensagem, int sizeConteudo ) {
    int result = msgrcv(msgId, mensagem, sizeConteudo, tipoMensagem, 0);
    if ( result < 0) {
        debug( "Could not Receive the Message of Type %d from the Message Queue with key=0x%x and id=%d", tipoMensagem, IPC_KEY, msgId );
    } else {
        debug( "Received a Message of Type %d from the Message Queue with key=0x%x and id=%d, with %d bytes", tipoMensagem, IPC_KEY, msgId, result );
    }
    return result;
}