#include "my_shm.h"
#include "utils.h"

/************************************************************************
 * IPC SHARED MEMORY FUNCTIONS
 ************************************************************************/

/**
 * @brief Internal Private Function, not to be used by the students.
 */
int __my_ShmGet( int nrElements, int shmFlags ) {
    int ipcShmId = shmget( IPC_KEY, nrElements * sizeof(IPC_ShmDataType), shmFlags );
    if ( ipcShmId < 0 ) {
        debug( "Could not create/open the Shared Memory with key=0x%x", IPC_KEY );
    } else {
        debug( "Using the Shared Memory with key=0x%x and id=%d", IPC_KEY, ipcShmId );
    }
    return ipcShmId;
}

/**
 * @brief Creates an IPC Shared Memory NON-exclusively, associated with the IPC_KEY, of an array of size multiple of sizeof(IPC_ShmDataType)
 * 
 * @param nrElements Size of the array
 * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
 */
int my_ShmCreate( int nrElements ) {
    return __my_ShmGet( nrElements, IPC_CREAT | 0600 );
}

/**
 * @brief Creates an IPC Shared Memory exclusively, associated with the IPC_KEY, of an array of size multiple of sizeof(IPC_ShmDataType)
 * 
 * @param nrElements Size of the array
 * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
 */
int my_shmCreateExcl( int nrElements ) {
    return __my_ShmGet( nrElements, IPC_CREAT | IPC_EXCL | 0600 );
}

/**
 * @brief Opens an already created IPC Shared Memory associated with the IPC_KEY
 * 
 * @return int ipcShmId. In case of error, returns -1 and sets errno with the error value
 */
int my_ShmGet() {
    return __my_ShmGet( 0, 0 );
}

/**
 * @brief Removes the IPC Shared Memory associated with the IPC_KEY
 * 
 * @param ipcShmId Id of the Shared Memory
 * @return int 0 if success or if the Shared Memory already did not exist, or -1 if the Shared Memory exists and could not be removed
 */
int my_ShmRemove( int ipcShmId ) {
    // Ignore any errors here, as this is only to check if the shared memory exists and remove it
    if ( ipcShmId > 0 ) {
        // If the shared memory with IPC_KEY already exists, remove it
        int result = shmctl( ipcShmId, IPC_RMID, 0 );
        if ( result < 0) {
            debug( "Could not remove the Shared Memory with key=0x%x and id=%d", IPC_KEY, ipcShmId );
        } else {
            debug( "Removed the Shared Memory with key=0x%x and id=%d", IPC_KEY, ipcShmId );
        }
        return result;
    }
    return 0;
}

/**
 * @brief Attaches a shared memory associated with shmId with a local address
 * 
 * @param ipcShmId Id of the Shared Memory
 * @return IPC_ShmDataType *, or NULL in case of error (and sets errno with the error value)
 */
IPC_ShmDataType *my_ShmAttach( int ipcShmId ) {
    IPC_ShmDataType* array = (IPC_ShmDataType*) shmat( ipcShmId, 0, 0 );
    if ( NULL == array ) {
        debug( "Could not Attach the Shared Memory with id=%d", ipcShmId );
    } else {
        debug( "The Shared Memory with id=%d was Attached on the local address %p", ipcShmId, array );
    }
    return array;
}

/**
 * @brief Detaches a shared memory attached at the passed local address
 * 
 * @param shm local address of the Shared Memory
 * @return success
 */
int my_ShmDetach( IPC_ShmDataType* shm ) {
    int result = shmdt( shm );
    if ( result < 0 ) {
        debug( "Could not detach the Shared Memory attached on the local address %p", shm );
    } else {
        debug( "Detached the Shared Memory attached on the local address %p", shm );
    }
    return result;
}

/**
 * @brief Initiates the Shared Memory with default values
 * 
 * @param shm local address of the Shared Memory
 * @param nrElements Number of elements of the shared memory
 */
void my_ShmInit( IPC_ShmDataType* shm, int nrElements ) {
    for ( int i = 0; i < nrElements; ++i ) {
        shm[i].shmKey = -1;
    }
}

/**
 * @brief Displays the values of the shared memory
 *
 * @param shm Shared Memory
 * @param nrElements Number of elements of the shared memory
 * @param ignoreInvalid Do not display the elements that have the default value
 */
void my_ShmView( IPC_ShmDataType* shm, int nrElements, int ignoreInvalid ) {
    debug( "Contents of the Shared Memory:" );
    for ( int i = 0; i < nrElements; ++i ) {
        if ( !ignoreInvalid || -1 != shm[i].shmKey ) {
            printf( "Index %2d: %6d | %-99s | %2.3f\n", i, shm[i].shmKey, shm[i].shmField1, shm[i].shmField2 );
        }
    }
}

/**
 * @brief Asks the user about the information to fill a structure Aluno
 * 
 * @return Aluno 
 *
Aluno obter_dados_aluno() {
    Aluno a;

    printf("Diga o Número do aluno: ");
    scanf("%d", &a.numero);
	getchar();

    printf("Diga o Nome do aluno: ");
    my_gets(a.nome, 99);

    printf("Diga a Nota do aluno: ");
    scanf("%f", &a.nota);
	getchar();
 
    return a;   
}

/**
 * @brief Inserts a new Aluno in the shared memory if possible
 * 
 * @param shm Shared Memory
 * @param nrAlunos Number of elements of the shared memory
 * @param a Aluno to be inserted
 * @return int The index of the shared memory where the new Aluno was inserted or -1 if the shared memory is already full
 *
int registar_aluno( Aluno *shm, int nrAlunos, Aluno a ) {
    int i;
    for( i = 0; i < nrAlunos; ++i ) {
        if ( -1 == shm[i].numero ) {
            debug( "A inserir o aluno na posição %d", i );
            shm[i] = a;
            break;
        }
    }
    return i < nrAlunos ? i : -1;  // Registou aluno? retorna o índice, senão retorna -1
}
*/