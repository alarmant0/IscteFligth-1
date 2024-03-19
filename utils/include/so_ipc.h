/******************************************************************************
 ** ISCTE-IUL: Trabalho prático de Sistemas Operativos
 **
 ** Nome do Módulo: so_ipc.h
 ** Descrição/Explicação do Módulo:
 **     Definição de funções úteis para manuseamento de IPC
 **
 ******************************************************************************/
#ifndef __SO_IPC_H__
#define __SO_IPC_H__

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>

/********************************************************************************
 * IPC SEMAPHORES FUNCTIONS (integrates with /home/so/reference/so_ipc-sem.c)
 ********************************************************************************/

/**
 * @brief Internal Private Macro, not to be used by the students.
 */
#define __so_SemGet_internal__(nrElements, semFlags, showOutput) ({                                 \
    int _so_IpcSemId = semget(IPC_KEY, nrElements, semFlags);                                       \
    if (showOutput) {                                                                               \
        if ( _so_IpcSemId < 0 ) {                                                                   \
            so_debug("Could not create/open the Semaphores Group with key=0x%x", IPC_KEY );         \
        } else {                                                                                    \
            so_debug("Using the Semaphores Group with key=0x%x and id=%d", IPC_KEY, _so_IpcSemId ); \
        }                                                                                           \
    }                                                                                               \
    _so_IpcSemId;                                                                                   \
})

/**
 * @brief Creates an IPC Semaphores Group NON-exclusively, associated with IPC_KEY, with the passed number of Semaphores
 *
 * @param nrElements Number of Semaphores of the Group
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
#define so_SemCreateMultiple(nrElements) __so_SemGet_internal__(nrElements, IPC_CREAT | 0600, TRUE)

/**
 * @brief Creates an IPC Semaphores Group NON-exclusively, associated with IPC_KEY, with 1 Semaphore
 *
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
#define so_SemCreate() so_SemCreateMultiple(1)

/**
 * @brief Creates an IPC Semaphores Group exclusively, associated with IPC_KEY, with the passed number of Semaphores
 *
 * @param nrElements Number of Semaphores of the Group
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
#define so_SemCreateExclMultiple(nrElements) __so_SemGet_internal__(nrElements, IPC_CREAT | IPC_EXCL | 0600, TRUE)

/**
 * @brief Creates an IPC Semaphores Group exclusively, associated with IPC_KEY, with 1 Semaphore
 *
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
#define so_SemCreateExcl() so_SemCreateExclMultiple(1)

/**
 * @brief Opens an already created IPC Semaphores Group associated with IPC_KEY
 *
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
#define so_SemGet() __so_SemGet_internal__(0, 0, TRUE)

/**
 * @brief Internal Private Macro, not to be used by the students.
 */
#define __so_SemRemoveWithId_internal__(ipcSemId, showOutput) ({                        \
    int __result__ = semctl(ipcSemId, 0, IPC_RMID, 0);                                  \
    if (showOutput) {                                                                   \
        if ( __result__ < 0 ) {                                                         \
            so_debug("Could not remove the Semaphores Group with key=0x%x", IPC_KEY);   \
        } else {                                                                        \
            so_debug("Removed the Semaphores Group with key=0x%x", IPC_KEY);            \
        }                                                                               \
    }                                                                                   \
    __result__;                                                                         \
})

/**
 * @brief Removes the IPC Semaphores Group associated with the passed ipcSemId
 *
 * @param ipcSemId IPC SemId
 * @return int 0 if success or if the Semaphores Group already did not exist, or -1 if the Semaphores Group exists and could not be removed
 */
#define so_SemRemoveWithId(ipcSemId) __so_SemRemoveWithId_internal__(ipcSemId, TRUE)

/**
 * @brief Removes the IPC Semaphores Group associated with IPC_KEY
 *
 * @return int 0 if success or if the Semaphores Group already did not exist, or -1 if the Semaphores Group exists and could not be removed
 */
#define so_SemRemove() so_SemRemoveWithId(__so_SemGet_internal__(0, 0, FALSE))

// /**
//  * @brief Sets the value of the Semaphore semNr of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @param semNr Index of the Semaphore to set value (starting in 0)
//  * @param value Value to be defined in the Semaphore semNr
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_SemNrSetValue( int ipcSemId, int semNr, int value );

// /**
//  * @brief Sets the value of the Semaphore 0 of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @param value Value to be defined in the Semaphore semNr
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_SemSetValue( int ipcSemId, int value );

// /**
//  * @brief Gets the value of the Semaphore semNr of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @param semNr Index of the Semaphore to set value (starting in 0)
//  * @return int Value of the Semaphore, or -1 in case of error and sets errno with the error value
//  */
// int so_SemNrGetValue( int ipcSemId, int semNr );

// /**
//  * @brief Gets the value of the Semaphore 0 of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @return int Value of the Semaphore, or -1 in case of error and sets errno with the error value
//  */
// int so_SemGetValue( int ipcSemId );

// /**
//  * @brief Adds a value to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @param semNr Index of the Semaphore to set value (starting in 0)
//  * @param value Value to be added to the value of the Semaphore semNr
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_SemNrAddValue( int ipcSemId, int semNr, int addValue );

// /**
//  * @brief Adds a value to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @param value Value to be added to the value of the Semaphore semNr
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_SemAddValue( int ipcSemId, int addValue );

// /**
//  * @brief Adds 1 (one) to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @param semNr Index of the Semaphore to set value (starting in 0)
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_SemNrUp( int ipcSemId, int semNr );

// /**
//  * @brief Adds -1 (minus one) to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @param semNr Index of the Semaphore to set value (starting in 0)
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_SemNrDown( int ipcSemId, int semNr );

// /**
//  * @brief Adds 1 (one) to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_SemUp( int ipcSemId );

// /**
//  * @brief Adds -1 (minus one) to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
//  *
//  * @param ipcSemId IPC SemId
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_SemDown( int ipcSemId );

// /***********************************************************************************
//  * IPC MESSAGE QUEUE FUNCTIONS (integrates with /home/so/reference/msg-operations.c)
//  ***********************************************************************************/

// /**
//  * @brief Creates an IPC Message Queue NON-exclusively, associated with the IPC_KEY
//  *
//  * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
//  */
// int so_MsgCreate();

// /**
//  * @brief Creates an IPC Message Queue exclusively, associated with the IPC_KEY
//  *
//  * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
//  */
// int so_MsgCreateExcl();

// /**
//  * @brief Opens an already created IPC Message Queue associated with the IPC_KEY
//  *
//  * @return int ipcMsgId. In case of error, returns -1 and sets errno with the error value
//  */
// int so_MsgGet();

// /**
//  * @brief Removes the IPC Message Queue associated with the IPC_KEY
//  *
//  * @param ipcMsgId IPC MsgID
//  * @return int 0 if success or if the Message Queue already did not exist, or -1 if the Message Queue exists and could not be removed
//  */
// int so_MsgRemove( int ipcMsgId );

// /**
//  * @brief Sends the passed message to the IPC Message Queue associated with the IPC_KEY
//  *
//  * @param ipcMsgId IPC MsgID
//  * @param ipcMessage Pointer to the IPC Message to be sent
//  * @param ipcMessageType IPC Message Type (or Address)
//  * @param sizeContents Size of the message contents
//  * @return int success (if error, returns -1 and sets errno with the error value)
//  */
// int so_MsgSend( int ipcMsgId, IPC_Message *ipcMessage, int ipcMessageType, int sizeContents );

// /**
//  * @brief Reads a message of the passed tipoMensagem from the IPC Message Queue associated with the IPC_KEY
//  *
//  * @param ipcMsgId IPC MsgID
//  * @param ipcMessage Pointer to the Message to be filled
//  * @param ipcMessageType Message Type (or Address)
//  * @param sizeContents Size of the message contents
//  * @return int Number of bytes read, or -1 in case of error and sets errno with the error value
//  */
// int so_MsgReceive( int ipcMsgId, IPC_Message *ipcMessage, int ipcMessageType, int sizeContents );

// /***********************************************************************************
//  * IPC SHARED MEMORY FUNCTIONS (integrates with /home/so/reference/shm-operations.c)
//  ***********************************************************************************/

// /**
//  * @brief Creates an IPC Shared Memory NON-exclusively, associated with the IPC_KEY, of an array of size multiple of sizeof(IPC_ShmDataType)
//  *
//  * @param nrElements Size of the array
//  * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
//  */
// int so_ShmCreate( int nrElements );

// /**
//  * @brief Creates an IPC Shared Memory exclusively, associated with the IPC_KEY, of an array of size multiple of sizeof(IPC_ShmDataType)
//  *
//  * @param nrElements Size of the array
//  * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
//  */
// int so_shmCreateExcl( int nrElements );

// /**
//  * @brief Opens an already created IPC Shared Memory associated with the IPC_KEY
//  *
//  * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
//  */
// int so_ShmGet();

// /**
//  * @brief Removes the IPC Shared Memory associated with the IPC_KEY
//  *
//  * @return int 0 if success or if the Shared Memory already did not exist, or -1 if the Shared Memory exists and could not be removed
//  */
// int so_ShmRemove();

// /**
//  * @brief Attaches a shared memory associated with shmId with a local address
//  *
//  * @param ipcShmId Id of the Shared Memory
//  * @return IPC_ShmDataType *, or NULL in case of error (and sets errno with the error value)
//  */
// IPC_ShmDataType *so_ShmAttach( int ipcShmId );

#endif