#!/bin/bash
# SO_HIDE_DEBUG=1                   ## Uncomment this line to hide all @DEBUG statements
# SO_HIDE_COLOURS=1                 ## Uncomment this line to disable all escape colouring
. ./so_utils.sh                     ## This is required to activate the macros so_success, so_error, and so_debug
###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos 2023/2024, Enunciado Versão 3+
##
## Aluno: Nº:105448       Nome:David Pinheiro
## Nome do Módulo: S3. Script: estado_voos.sh
##
###############################################################################
## Este script não recebe nenhum argumento, e é responsável pelo relatório do estado dos voos que pertencem à plataforma IscteFlight.
## S3.1. Validações:
## S3.1.1. O script valida se o ficheiro voos.txt existe. Se não existir, dá so_error e termina. Senão, dá so_success.
if [ ! -f "voos.txt" ]; then
    so_error "S3.1.1"
    exit 1
else
    so_success "S3.1.1"
fi  
## S3.1.2. O script valida se os formatos de todos os campos de cada linha do ficheiro voos.txt correspondem à especificação indicada em S2, nomeadamente se respeitam os formatos de data e de hora. Se alguma linha não respeitar, dá so_error <conteúdo da linha> e termina. Caso contrário, dá so_success.
BAD_LINES=$(grep -v -P -i '[a-z0-9]+:[a-z].*[a-z]:[a-z].*[a-z]:[0-9]{4}-[0-9]{2}-[0-9]{2}:\d\dh\d\d:[0-9]+:[0-9]+:[0-9]+' ./voos.txt)
if [ -z "$BAD_LINES" ]; then
    so_success "S3.1.2"
else
    so_error "S3.1.2" "$BAD_LINES"
    exit 1
fi

## S3.2. Processamento do script:
## S3.2.1. O script cria uma página em formato HTML, chamada voos_disponiveis.html, onde lista os voos com lugares disponíveis, indicando nº, origem, destino, data, hora, lotação, nº de lugares disponíveis, e nº de lugares ocupados (para isso deve calcular a diferença dos anteriores). Em caso de erro (por exemplo, se não conseguir escrever no ficheiro), dá so_error e termina. Caso contrário, dá so_success.
if [ -f ./voos_disponiveis.html ]; then
    if ! touch ./voos_disponiveis.html; then
        so_error "S3.2.1" 
        exit 1
    fi
fi
if echo '<html><head><meta charset="UTF-8"><title>IscteFlight: Lista de Voos Disponíveis</title></head>' > ./voos_disponiveis.html
    DATE_ATUAL=$(date +'%Y-%m-%d')
    TIME_ATUAL=$(date +'%H:%M:%S')
    echo "<body><h1>Lista atualizada em $DATE_ATUAL $TIME_ATUAL</h1>" >> ./voos_disponiveis.html; then
    while IFS= read -r line; do
        NUMBER=$(echo $line | cut -d ":" -f 1)
        ORIGEM=$(echo $line | cut -d ":" -f 2)
        DESTINO=$(echo $line | cut -d ":" -f 3)
        DATA=$(echo $line | cut -d ":" -f 4)
        HORA=$(echo $line | cut -d ":" -f 5)
        PRECO=$(echo $line | cut -d ":" -f 6)
        LOTACAO=$(echo $line | cut -d ":" -f 7)
        DISPONIVEL=$(echo $line | cut -d ":" -f 8)
        OCUPADOS=$(($LOTACAO-$DISPONIVEL))
        if [ "$DISPONIVEL" -ne "0" ]; then
            echo "<h2>Voo: $NUMBER, De: $ORIGEM Para: $DESTINO, Partida em $DATA $HORA</h2>" >> ./voos_disponiveis.html
            echo "<ul>" >> ./voos_disponiveis.html
            echo "<li><b>Lotação:</b> $LOTACAO Lugares</li>" >> ./voos_disponiveis.html
            echo "<li><b>Lugares Disponíveis:</b> $DISPONIVEL Lugares</li>" >> ./voos_disponiveis.html 
            echo "<li><b>Lugares Ocupados:</b> $OCUPADOS Lugares</li>" >> ./voos_disponiveis.html
            echo "</ul>" >> ./voos_disponiveis.html
        fi
    done < "./voos.txt" 
    echo "</body></html>" >> ./voos_disponiveis.html
    so_success "S3.2.1"
else
    so_error "S3.2.1"
    exit 1
fi
## S3.3. Invocação do script estado_voos.sh:
## S3.3.1. Altere o ficheiro cron.def fornecido, por forma a configurar o seu sistema para que o script seja executado de hora em hora, diariamente. Nos comentários no início do ficheiro cron.def, explique a configuração realizada, e indique qual o comando que deveria utilizar para despoletar essa configuração. O ficheiro cron.def alterado deverá ser submetido para avaliação juntamente com os outros Shell scripts.