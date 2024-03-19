#include <fcntl.h>
//#define SO_HIDE_DEBUG                     // Uncomment this line to hide all @DEBUG statements
#include "/home/so/reference/so_utils.h"    // Include Utilities functions for SO

int main() {
    so_debug("#1) Teste a so_debug(). Repare que não só a macro so_debug mostra o nome do ficheiro source, a linha de código e a função que está a ser executada (main)\ncomo também mostra esta mensagem, que pode levar %d argumentos %s (ou mais) como se fosse printf()", 9999999, "variáveis");

    so_debug("#2) Teste a so_debug() com SO_HIDE_DEBUG definido. Para realizar esse teste, remova o comentário da linha %d", 2);
    #ifdef SO_HIDE_DEBUG
        printf("Se consegue ler esta linha, é porque o símbolo SO_HIDE_DEBUG está definido, e, portanto, não vai conseguir ler as outras mensagens de so_debug()\n");
        printf("Para continuar para o próximo teste, volte a comentar a linha %d\n", 2);
        exit(0);
    #endif

    so_debug("#3) Teste a so_exit_on_error() sem erro");
    int status = system("true");    // "true" é um comando Linux que retorna sempre 0 (sem erro)
    so_exit_on_error(status, "Erro no comando system executado");
    so_debug("#3) O programa continua a correr mesmo depois do so_exit_on_error() porque não houve erro");

    so_debug("#4) Teste a so_exit_on_error() com erro. Para continuar o teste, depois terá de comentar a linha %d, \"status = open...\", senão não saímos daqui...", 22);
    so_debug("#4) O programa não continuará a correr depois do so_exit_on_error(). Repare que não só a macro termina o processo como dá informação extra sobre qual foi o erro.");
    status = open("Ficheiro_Inexistente.nofile", O_RDONLY);    // Esta operação irá retornar -1
    so_exit_on_error(status, "Erro na operação open()");
    so_debug("#4) Se consegue ler esta linha, é porque comentou a linha %d, \"status = open...\", senão não saíamos daqui...", 22);

    so_debug("#5) Teste a so_exit_on_null() sem erro");
    FILE *f = malloc(sizeof(FILE));       // à partida esta operação não irá dar erro...
    so_exit_on_null(f, "Erro na operação malloc()");
    so_debug("#5) O programa continua a correr mesmo depois do so_exit_on_null() porque não houve erro");

    so_debug("#6) Teste a so_exit_on_null() com erro. Para continuar o teste, depois terá de comentar a linha %d, \"FILE *f = fopen...\", senão não saímos daqui...", 33);
    so_debug("#6) O programa não continuará a correr depois do so_exit_on_null(). Repare que não só a macro termina o processo como dá informação extra sobre qual foi o erro.");
    f = fopen("Ficheiro_Inexistente.nofile", "r");    // Esta operação irá retornar NULL
    so_exit_on_null(f, "Erro na operação fopen()");
    so_debug("#6) Se consegue ler esta linha, é porque comentou a linha %d, \"f = fopen...\", senão não saímos daqui...", 33);
    free(f);

    so_debug("#7) Teste 1 a so_fgets()");
    f = fopen("so_utils-tester.c", "r");
    so_exit_on_null(f, "Erro na operação fopen()");    // Esta operação não é suposto que dê erro, mas na mesma deverá sempre ser validado.
    char str[99];
    int buffer_size = 99;
    so_exit_on_null(so_fgets(str, buffer_size, f), "Erro na operação so_fgets()");
    fclose(f);
    so_debug("#7) Esta chamada a so_fgets() deverá ler os primeiros %d caracteres da frase (mais do que o tamanho da frase), e não ter um \\n no final. O resultado final é \"%s\"", buffer_size - 1, str);

    so_debug("#8) Teste 2 a so_fgets()");
    f = fopen("so_utils-tester.c", "r");
    so_exit_on_null(f, "Erro na operação fopen()");    // Esta operação não é suposto que dê erro, mas na mesma deverá sempre ser validado.
    buffer_size = 15;
    so_exit_on_null(so_fgets(str, buffer_size, f), "Erro na operação so_fgets()");
    so_debug("#8) Esta primeira chamada a so_fgets() deverá ler só os primeiros %d caracteres da frase, e não ter um \\n no final. O resultado final é \"%s\", mas na mesma a função consome toda a linha até ao fim.", buffer_size - 1, str);
    so_exit_on_null(so_fgets(str, buffer_size, f), "Erro na operação so_fgets()");
    so_debug("#8) Esta segunda chamada a so_fgets() serve para mostrar que, apesar da primeira chamada não ter retornado toda a primeira linha,\nconsumiu na mesma toda a primeira linhe do ficheiro, e esta segunda chamada já deve mostrar os primeiros %d caracteres da segunda linha do ficheiro, e não ter um \\n no final. O resultado final é \"%s\", e, novamente, a função consome toda a linha até ao fim.", buffer_size - 1, str);
    fclose(f);

    so_debug("#9) Teste 1 a so_gets()");
    printf("Escreva uma frase (não vazia): ");
    buffer_size = 15;
    so_exit_on_null(so_gets(str, buffer_size), "Erro na operação so_gets()");
    so_debug("#9) Esta chamada a so_gets() deverá ler só os primeiros %d caracteres da frase introduzida pelo utilizador, e não ter um \\n no final.O resultado final é \"%s\", mas na mesma a função consome toda a linha até ao fim.", buffer_size - 1, str);

    so_debug("#10) Teste 2 a so_gets()");
    printf("Escreva uma frase vazia (só pressione ENTER): ");
    buffer_size = 15;
    so_exit_on_null(so_gets(str, buffer_size), "Erro na operação so_gets()");
    so_debug("#10) so_gets() agora já lê strings vazias, e tira-lhes o \\n final, o resultado é \"%s\".", str);

    so_debug("#11) Teste 3 a so_gets(): Correr so_gets após scanf(%%d)");
    printf("Escreva um número entre 0 e 9: ");
    int numero;
    if (scanf("%d", &numero) < 1) {
        so_exit_on_error(-1, "Erro na operação scanf()");
    }
    printf("Escreva uma frase (não vazia): ");
    buffer_size = 15;
    so_exit_on_null(so_gets(str, buffer_size), "Erro na operação so_gets()");
    so_debug("#11) Como pode ver, so_gets() a seguir a scanf(%%d) nem sequer espera que o utilizador escreva nada, e o resultado é \"%s\".", str);

    so_debug("#12) Teste 4 a so_gets(): Correr so_gets após scanf(%%d)");
    printf("Escreva novamente um número entre 0 e 9: ");
    if (scanf("%d", &numero) < 1) {
        so_exit_on_error(-1, "Erro na operação scanf()");
    }
    getchar();
    printf("Escreva uma frase (não vazia): ");
    buffer_size = 15;
    so_exit_on_null(so_gets(str, buffer_size), "Erro na operação so_gets()");
    so_debug("#12) Como pode ver, agora so_gets() a seguir a scanf(%%d) já espera que o utilizador escreva uma string, e o resultado é \"%s\".", str);

    so_debug("#13) Teste 1 a so_geti(): Lê um inteiro do STDIN");
    printf("Escreva um número (com, no máximo, %d dígitos): ", __SO_UTILS_TEMPORARY_BUFFER_SIZE__ - 1);
    int geti = so_geti();
    so_debug("#13) O resultado lido é %d.", geti);

    so_debug("#14) Teste 2 a so_geti(): Lê um inteiro do STDIN");
    printf("Escreva um número com mais de %d dígitos: ", __SO_UTILS_TEMPORARY_BUFFER_SIZE__ - 1);
    geti = so_geti();
    so_debug("#14) Como vê, o número foi 'truncado' ao valor máximo da string. O resultado lido é %d.", geti);

    so_debug("#15) Teste 1 a so_getf(): Lê um float do STDIN");
    printf("Escreva um número float (com, no máximo, %d dígitos): ", __SO_UTILS_TEMPORARY_BUFFER_SIZE__ - 1);
    float getf = so_getf();
    so_debug("#15) O resultado lido é %f.", getf);

    so_debug("#16) Teste 2 a so_getf(): Lê um float do STDIN");
    printf("Escreva um número float com mais de %d dígitos: ", __SO_UTILS_TEMPORARY_BUFFER_SIZE__ - 1);
    getf = so_getf();
    so_debug("#16) Como vê, o número foi 'truncado' ao valor máximo da string. O resultado lido é %f.", getf);

    so_debug("#17) Teste 1 a so_rand()");
    so_debug("Analise os três primeiros valores \"aleatórios\" gerados pela função rand(): %d, %d e %d", rand(), rand(), rand());
    so_debug("Analise os três primeiros valores \"aleatórios\" gerados pela função so_rand(): %d, %d e %d", so_rand(), so_rand(), so_rand());
    so_debug("Corra agora novamente o programa de testes testa-utils e compare novamente os valores \"aleatórios\" gerados por ambas as funções");

    so_debug("#18) Teste 1 a error() e a success()");
    so_error("C1.2.2", "");
    so_error("C1.2.3", "String Complexa, com %d, %f, e %s", 43, 12.45, "outra string");
    so_success("C1.2.2", "");
    so_success("C1.2.3", "String Complexa, com %d, %f, e %s", 43, 12.45, "outra string");
}
