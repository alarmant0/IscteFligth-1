#include "/home/so/reference/so_ipc.h"
#include "/home/so/reference/so_utils.h"

/************************************************************************
 * IPC SEMAPHORES FUNCTIONS
 ************************************************************************/

/**
 * @brief Internal Private Function, not to be used by the students.
 */
int __so_SemGet( int nrElements, int semFlags, char showOutput = TRUE ) {
    int ipcSemId = semget( IPC_KEY, nrElements, semFlags );
    if ( ipcSemId < 0 ) {
        debug( "Could not create/open the Semaphores Group with key=0x%x", IPC_KEY );
    } else {
        debug( "Using the Semaphores Group with key=0x%x and id=%d", IPC_KEY, ipcSemId );
    }
    return ipcSemId;
}

/**
 * @brief Creates an IPC Semaphores Group NON-exclusively, associated with the IPC_KEY, with the passed number of Semaphores
 *
 * @param nrElements Number of Semaphores of the Group
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
int so_SemCreate( int nrElements ) {
    return __so_SemGet( nrElements, IPC_CREAT | 0600 );
}

/**
 * @brief Creates an IPC Semaphores Group exclusively, associated with the IPC_KEY, with the passed number of Semaphores
 *
 * @param nrElements Number of Semaphores of the Group
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
int so_SemCreateExcl( int nrElements ) {
    return __so_SemGet( nrElements, IPC_CREAT | IPC_EXCL | 0600 );
}

/**
 * @brief Opens an already created IPC Semaphores Group associated with the IPC_KEY
 *
 * @return int ipcSemId. In case of error, returns -1 and sets errno with the error value
 */
int so_SemGet() {
    return __so_SemGet( 0, 0 );
}

/**
 * @brief Removes the IPC Semaphores Group associated with the IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @return int 0 if success or if the Semaphores Group already did not exist, or -1 if the Semaphores Group exists and could not be removed
 */
int so_SemRemove( int ipcSemId ) {
    // Ignore any errors here, as this is only to check if the semaphore group exists and remove it
    if ( ipcSemId > 0 ) {
        // If the semaphore group with IPC_KEY already exists, remove it.
        int result = semctl( ipcSemId, 0, IPC_RMID, 0 );
        if ( result < 0) {
            debug( "Could not remove the Semaphores Group with key=0x%x and id=%d", IPC_KEY, ipcSemId );
        } else {
            debug( "Removed the Semaphores Group with key=0x%x and id=%d", IPC_KEY, ipcSemId );
        }
        return result;
    }
    return 0;
}

/**
 * @brief Sets the value of the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @param value Value to be defined in the Semaphore semNr
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int so_SemNrSetValue( int ipcSemId, int semNr, int value ) {
    int result = semctl( ipcSemId, semNr, SETVAL, value );
    if ( result < 0) {
        debug( "Could not set the value of the Semaphore %d of this Semaphore Group", semNr );
    } else {
        debug( "The Semaphore %d of this Semaphore Group was set with value %d", semNr, value );
    }
    return result;
}

/**
 * @brief Sets the value of the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @param value Value to be defined in the Semaphore semNr
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int so_SemSetValue( int ipcSemId, int value ) {
    return so_SemNrSetValue( ipcSemId, 0, value );
}

/**
 * @brief Gets the value of the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int Value of the Semaphore, or -1 in case of error and sets errno with the error value
 */
int so_SemNrGetValue( int ipcSemId, int semNr ) {
    int result = semctl( ipcSemId, semNr, GETVAL, 0 );
    if ( result < 0 ) {
        debug( "Could not get the value of the Semaphore %d of this Semaphore Group", semNr );
    } else {
        debug( "The Semaphore %d of this Semaphore Group has the value %d", semNr, result );
    }
    return result;
}

/**
 * @brief Gets the value of the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @return int Value of the Semaphore, or -1 in case of error and sets errno with the error value
 */
int so_SemGetValue( int ipcSemId ) {
    return so_SemNrGetValue( ipcSemId, 0 );
}

/**
 * @brief Adds a value to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @param value Value to be added to the value of the Semaphore semNr
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int so_SemNrAddValue( int ipcSemId, int semNr, int addValue ) {
    int result = semctl( ipcSemId, semNr, GETVAL, 0 );
    exit_on_error( result, "Error on semctl" );
    debug( "The Semaphore %d of this Semaphore Group had the value %d", semNr, result );

    struct sembuf operation = { semNr, addValue, 0 };
    result = semop( ipcSemId, &operation, 1 );

    if ( result < 0 ) {
        debug( "Could not add the value %d to the value of the Semaphore %d of this Semaphore Group", addValue, semNr );
    } else {
        result = semctl( ipcSemId, semNr, GETVAL, 0 );
        exit_on_error( result, "Error on semctl" );
        debug( "The Semaphore %d of this Semaphore Group now has the value %d", semNr, result );
    }
    return result;
}

/**
 * @brief Adds a value to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @param value Value to be added to the value of the Semaphore semNr
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int so_SemAddValue( int ipcSemId, int addValue ) {
    return so_SemNrAddValue( ipcSemId, 0, addValue );
}

/**
 * @brief Adds 1 (one) to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int so_SemNrUp( int ipcSemId, int semNr ) {
    return so_SemNrAddValue( ipcSemId, semNr, 1 );
}

/**
 * @brief Adds -1 (minus one) to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int so_SemNrDown( int ipcSemId, int semNr ) {
    return so_SemNrAddValue( ipcSemId, semNr, -1 );
}

/**
 * @brief Adds 1 (one) to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int so_SemUp( int ipcSemId ) {
    return so_SemAddValue( ipcSemId, 1 );
}

/**
 * @brief Adds -1 (minus one) to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param ipcSemId IPC SemId
 * @return int success (if error, returns -1 and sets errno with the error value)
 */
int so_SemDown( int ipcSemId ) {
    return so_SemAddValue( ipcSemId, -1 );
}