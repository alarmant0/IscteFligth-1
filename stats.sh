#!/bin/bash
# SO_HIDE_DEBUG=1                   ## Uncomment this line to hide all @DEBUG statements
# SO_HIDE_COLOURS=1                 ## Uncomment this line to disable all escape colouring
. ./so_utils.sh                     ## This is required to activate the macros so_success, so_error, and so_debug

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos 2023/2024, Enunciado Versão 3+
##
## Aluno: Nº:105448       Nome:David Pinheiro
## Nome do Módulo: S4. Script: stats.sh
## 
###############################################################################

## Este script obtém informações sobre o sistema, afixando resultados diferentes no STDOUT consoante os argumentos passados na sua invocação. A sintaxe resumida é: ./stats.sh <passageiros>|<top <nr>>

## S4.1. Validações:
## S4.1.1. Valida os argumentos recebidos e, conforme os mesmos, o número e tipo de argumentos recebidos. Se não respeitarem a especificação, dá so_error e termina. Caso contrário, dá so_success.
if [ "$#" -eq 1 ]; then
    if [ "$1" == "passageiros" ]; then
        so_success "S4.1.1"
    else
        so_error "S4.1.1"
        exit 1
    fi
elif [ "$#" -eq 2 ]; then
    if [ "$1" == "top" ] && [[ $2 =~ ^[0-9]+$ ]]; then
        so_success "S4.1.1"
    else    
        so_error "S4.1.1"
        exit 1
    fi
else
    so_error "S4.1.1"
    exit 1
fi
## S4.2.1 Invocação do script:

if [ "$1" == "passageiros" ]; then
    if ! touch "./stats.txt"; then
        so_error "S4.2.1"
        exit 1
    fi
    USERS=$(cat ./relatorio_reservas.txt | cut -d ":" -f 6 | sort | uniq -c | sort -nr | cut -d " " -f 8)
    while IFS= read -r userr; do
        NAME=$(cat ./passageiros.txt | grep "$userr" | cut -d ":" -f 3)
        RESERVAS=$(cat ./relatorio_reservas.txt | grep ":$userr:" | wc -l)
        PRECOS=$(cat ./relatorio_reservas.txt | sort -n | grep ":$userr:" | cut -d ":" -f 5)
        TOTAL=0
        while IFS= read -r preco; do
        TOTAL=$(($preco+$TOTAL))
        done <<< "$PRECOS"
        if [ "$RESERVAS" -gt "1" ]; then
            echo "$NAME: $RESERVAS reservas; $TOTAL€" >> "./stats.txt"
        else
            echo "$NAME: $RESERVAS reserva; $TOTAL€" >> "./stats.txt"
        fi
    done <<< "$USERS"
    so_success "S4.2.1"

else
#S4.2.2
    if [ -f "./stats.txt" ]; then
        rm -f "./stats.txt"
    fi
    if ! touch "./stats.txt"; then
        so_error "S4.2.2"
        exit 1
    fi
    VOOS=$(cat "./relatorio_reservas.txt" | cut -d ":" -f 2 | sort | uniq)
    while IFS= read -r voo; do
        TOTAL=0
        PRECOS=$(cat "./relatorio_reservas.txt" | grep ":$voo:" | cut -d ":" -f 5)
        while IFS= read -r preco; do
            TOTAL=$(($TOTAL+$preco))
        done <<< "$PRECOS"
        echo "$voo: $TOTAL€" >> "./stats.txt"
    done <<< "$VOOS"
    sort -t: -k2 -nr "./stats.txt" -o "./stats.txt"
    if ! cat "./stats.txt" | head -n "$2" | sort -t: -k2 -nr -o "./stats.txt"; then
        so_error "S4.2.2"
        exit 1
    else
        so_success "S4.2.2"
    fi
fi

