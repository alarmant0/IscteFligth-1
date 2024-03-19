/******************************************************************************
 ** ISCTE-IUL: Protótipos genéricos úteis para manuseamento de IPC
 ******************************************************************************/
#ifndef __MY_SHM_H__
#define __MY_SHM_H__

#include <sys/ipc.h>
#include <sys/shm.h>

#ifndef __IPC_KEY__
#define __IPC_KEY__

/**
 *  KEY to be used on all Linux IPC get operations
 */
#define IPC_KEY 0x0a123456      // Suggestion: Replace with your student number

#endif

#ifndef __IPC_SHM__
#define __IPC_SHM__

/**
 *  Default data type for each Shared Memory element
 */
typedef struct {
    int shmKey;
    char shmField1[99];
    float shmField2;
} IPC_ShmDataType;

#endif

/***************************************************************************
 * IPC SHARED MEMORY FUNCTIONS (integrates with /home/so/reference/my_shm.c)
 ***************************************************************************/

/**
 * @brief Creates an IPC Shared Memory NON-exclusively, associated with the IPC_KEY, of an array of size multiple of sizeof(IPC_ShmDataType)
 * 
 * @param nrElements Size of the array
 * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
 */
int my_ShmCreate( int nrElements );

/**
 * @brief Creates an IPC Shared Memory exclusively, associated with the IPC_KEY, of an array of size multiple of sizeof(IPC_ShmDataType)
 * 
 * @param nrElements Size of the array
 * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
 */
int my_shmCreateExcl( int nrElements );

/**
 * @brief Opens an already created IPC Shared Memory associated with the IPC_KEY
 * 
 * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
 */
int my_ShmGet();

/**
 * @brief Removes the IPC Shared Memory associated with the IPC_KEY
 * 
 * @param ipcShmId Id of the Shared Memory
 * @return int 0 if success or if the Shared Memory already did not exist, or -1 if the Shared Memory exists and could not be removed
 */
int my_ShmRemove( int ipcShmId );

/**
 * @brief Attaches a shared memory associated with shmId with a local address
 * 
 * @param ipcShmId Id of the Shared Memory
 * @return IPC_ShmDataType *, or NULL in case of error (and sets errno with the error value)
 */
IPC_ShmDataType *my_ShmAttach( int ipcShmId );

/**
 * @brief Detaches a shared memory attached at the passed local address
 * 
 * @param shm local address of the Shared Memory
 * @return success
 */
int my_ShmDetach( IPC_ShmDataType* shm );

/**
 * @brief Initiates the Shared Memory with default values
 * 
 * @param shm local address of the Shared Memory
 * @param nrElements Number of elements of the shared memory
 */
void my_ShmInit( IPC_ShmDataType* shm, int nrElements );

/**
 * @brief Displays the values of the shared memory
 *
 * @param shm Shared Memory
 * @param nrElements Number of elements of the shared memory
 * @param ignoreInvalid Do not display the elements that have the default value
 */
void my_ShmView( IPC_ShmDataType* shm, int nrElements, int ignoreInvalid );

#endif