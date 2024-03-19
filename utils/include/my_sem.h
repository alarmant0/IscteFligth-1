/******************************************************************************
 ** ISCTE-IUL: Protótipos genéricos úteis para manuseamento de IPC
 ******************************************************************************/
#ifndef __MY_SEM_H__
#define __MY_SEM_H__

#include <sys/ipc.h>
#include <sys/sem.h>

#ifndef __IPC_KEY__
#define __IPC_KEY__

/**
 *  KEY to be used on all Linux IPC get operations
 */
#define IPC_KEY 0x0a123456      // Suggestion: Replace with your student number

#endif

/************************************************************************
 * IPC SEMAPHORES FUNCTIONS (integrates with /home/so/reference/my_sem.c)
 ************************************************************************/

/**
 * @brief Creates an IPC Semaphores Group NON-exclusively, associated with the IPC_KEY, with the passed number of Semaphores
 * 
 * @param nrElements Number of Semaphores of the Group
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
int my_SemCreate( int nrElements );

/**
 * @brief Creates an IPC Semaphores Group exclusively, associated with the IPC_KEY, with the passed number of Semaphores
 * 
 * @param nrElements Number of Semaphores of the Group
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
int my_SemCreateExcl( int nrElements );

/**
 * @brief Opens an already created IPC Semaphores Group associated with the IPC_KEY
 * 
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
int my_SemGet();

/**
 * @brief Removes the IPC Semaphores Group associated with the IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @return int 0 if success or if the Semaphores Group already did not exist, or -1 if the Semaphores Group exists and could not be removed
 */
int my_SemRemove( int ipcSemId );

/**
 * @brief Sets the value of the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @param value Value to be defined in the Semaphore semNr
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_SemNrSetValue( int ipcSemId, int semNr, int value );

/**
 * @brief Sets the value of the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @param value Value to be defined in the Semaphore semNr
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_SemSetValue( int ipcSemId, int value );

/**
 * @brief Gets the value of the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int Value of the Semaphore, or -1 in case of error and sets errno with the error value
 */
int my_SemNrGetValue( int ipcSemId, int semNr );

/**
 * @brief Gets the value of the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @return int Value of the Semaphore, or -1 in case of error and sets errno with the error value
 */
int my_SemGetValue( int ipcSemId );

/**
 * @brief Adds a value to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @param value Value to be added to the value of the Semaphore semNr
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_SemNrAddValue( int ipcSemId, int semNr, int addValue );

/**
 * @brief Adds a value to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @param value Value to be added to the value of the Semaphore semNr
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_SemAddValue( int ipcSemId, int addValue );

/**
 * @brief Adds 1 (one) to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_SemNrUp( int ipcSemId, int semNr );

/**
 * @brief Adds -1 (minus one) to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_SemNrDown( int ipcSemId, int semNr );

/**
 * @brief Adds 1 (one) to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_SemUp( int ipcSemId );

/**
 * @brief Adds -1 (minus one) to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 * 
 * @param ipcSemId IPC SemId
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int my_SemDown( int ipcSemId );

#endif