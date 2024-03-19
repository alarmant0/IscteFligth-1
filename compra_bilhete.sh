#!/bin/bash
# SO_HIDE_DEBUG=1                   ## Uncomment this line to hide all @DEBUG statements
# SO_HIDE_COLOURS=1                 ## Uncomment this line to disable all escape colouring
. ./so_utils.sh                     ## This is required to activate the macros so_success, so_error, and so_debug

## Este script não recebe nenhum argumento, e permite que o passageiro compre um bilhete para um voo da lista de voos disponíveis. Para realizar a compra, o passageiro deve fazer login para confirmar sua identidade e saldo disponível. Os voos disponíveis estão listados no ficheiro voos.txt. Se não quiser produzir o seu próprio ficheiro, pode utilizar o ficheiro exemplo fornecido, dando o comando: cp voos-exemplo.txt voos.txt. O mesmo procedimento pode ser realizado também com o ficheiro passageiros.txt.
###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos 2023/2024, Enunciado Versão 3+
##
## Aluno: Nº:105448       Nome:David Pinheiro
## Nome do Módulo: S3. Script: estado_voos.sh
##
###############################################################################
## S2.1. Validações e Pedido de informações interativo:
## S2.1.1. O script valida se os ficheiros voos.txt e passageiros.txt existem. Se algum não existir, dá so_error e termina. Caso contrário, dá so_success.

if [ ! -f "voos.txt" ] || [ ! -f "passageiros.txt" ]; then
    so_error "S2.1.1"
    exit 1
else
    so_success "S2.1.1"
    if ! [ -f "./relatorio_reservas.txt" ]; then
        touch ./relatorio_reservas.txt
    fi
fi

## S2.1.2. Na plataforma é possível consultar os voos pela sua <Origem> ou <Destino>. Pedindo "Insira a cidade de origem ou destino do voo: _". O utilizador insere a cidade Origem ou Destino do voo (o interesse é que pesquise nos 2 campos). Caso o utilizador tenha introduzido uma cidade que não exista no ficheiro voos.txt, ou se não existirem voos com lugares disponíveis com origem ou destino nessa cidade, dá so_error e termina. Caso contrário, dá so_success <Cidade>.

read -p "Insira a cidade de origem ou destino do voo: " CITY

if grep -q ":$CITY:" ./voos.txt; then
    LUGARES=$(grep ":$CITY:" ./voos.txt | cut -d ":" -f 8)
    EXISTS=0
    while IFS= read -r line; do
        if [ "$line" != "0" ]; then 
            EXISTS=1
        fi
    done <<< "$LUGARES"
    if [ "$EXISTS" == "0" ]; then
        so_error "S2.1.2"
        exit 1
    fi
    so_success "S2.1.2" "$CITY"
else
    so_error "S2.1.2"
    exit 1
fi

## S2.1.3. O programa pede ao utilizador para inserir uma opção de voo, listando os voos que existem de acordo com a origem/destino inserida anteriormente, da seguinte forma: "Lista de voos, numerada, ou 0 para sair, Insira o voo que pretende reservar: _" O utilizador insere a opção do voo (neste exemplo, números de 1 a 3 ou 0). Se o utilizador escolheu um número de entre as opções de voos apresentadas (neste caso, entre 1 e 3), dá so_success <opção>. Caso contrário, dá so_error e termina.

CORRESPONDENCIAS=$(grep ":$CITY:" ./voos.txt)
I=1
while IFS= read -r line; do
    LOTACAO=$(echo $line | cut -d ":" -f 8)
    if [ "$LOTACAO" != "0" ]; then
        ORIGEM=$(echo $line | cut -d ":" -f 2)
        DESTINO=$(echo $line | cut -d ":" -f 3)
        DATA=$(echo $line | cut -d ":" -f 4)
        PARTIDA=$(echo $line | cut -d ":" -f 5)
        PRECO=$(echo $line | cut -d ":" -f 6)
        LINHA="$I.$ORIGEM para $DESTINO, $DATA, Partida:$PARTIDA, Preço: $PRECO, Disponíveis:$LOTACAO lugares"
        echo "$LINHA"
        I=$(($I+1))
    fi
done <<< "$CORRESPONDENCIAS"
echo "0.Sair"
echo ""
read -p "Insira o voo que pretende reservar: " VOO
if [[ "$VOO" =~ ^[0-"$I"]$ ]]; then
    so_success "S2.1.3" "$VOO"
else
    so_error "S2.1.3" 
    exit 1
fi

## S2.1.4. O programa pede ao utilizador o seu <ID_passageiro>: "Insira o ID do seu utilizador: _" O utilizador insere o respetivo ID de passageiro (dica: UserId Linux). Se esse ID não estiver registado no ficheiro passageiros.txt, dá so_error e termina. Caso contrário, reporta so_success <ID_passageiro>.

read -p "Insira o ID do seu utilizador: " ID

if grep -q "$ID:" /etc/passwd; then
        so_success "S2.1.4" "$ID"
else
    so_error "S2.1.4"
    exit 1
fi

## S2.1.5. O programa pede ao utilizador a sua <Senha>: "Insira a senha do seu utilizador: _" O utilizador insere a respetiva senha. Caso o script veja que essa senha não é a registada para esse passageiro no ficheiro passageiros.txt, dá so_error e termina. Caso contrário, reporta so_success.

read -p "Insira a senha do seu utilizador: " SENHA
if grep -q "$ID:" ./passageiros.txt; then
    SENHA_FILE=$(grep "$ID:" ./passageiros.txt | cut -d ":" -f 5)
    if [ "$SENHA_FILE" == "$SENHA" ]; then
        so_success "S2.1.5"
    else
        so_error "S2.1.5" 
        exit 1
    fi  
fi

## S2.2. Processamento da resposta:
## S2.2.1. Valida se o passageiro possui <Saldo>, definido no ficheiro passageiros.txt, para comprar o bilhete selecionado no passo S2.1.3. Se a compra não é possível por falta de saldo, dá so_error <preço voo> <Saldo> e termina. Caso contrário, dá so_success <preço voo> <Saldo>.
SALDO=$(grep "$ID:" ./passageiros.txt | cut -d ":" -f 6)
PRECO_VOO=$(echo "$CORRESPONDENCIAS" | awk -v VOO="$VOO" 'NR==VOO' | cut -d ":" -f 6)
if [[ "$SALDO" -ge "$PRECO_VOO" ]]; then
    so_success "S2.2.1" "$PRECO_VOO" "$SALDO"
else
    so_error "S2.2.1"
    exit 1
fi

## S2.2.2. Subtrai o valor do <preço voo> no <Saldo> do passageiro, e atualiza o ficheiro passageiros.txt. Em caso de erro (e.g., na escrita do ficheiro), dá so_error e termina. Senão, dá so_success <Saldo Atual>.
NUMBER=$(grep -n "$ID:" ./passageiros.txt | cut -d ":" -f 1)
NEW_SALDO=$(($SALDO-$PRECO_VOO))
if sed -i "${NUMBER}s/:[0-9]*$/:$NEW_SALDO/" ./passageiros.txt; then
    so_success "S2.2.2" "$NEW_SALDO"
else
    so_error "S2.2.2"
    exit 1
fi

## S2.2.3. Decrementa uma unidade aos lugares disponíveis do voo escolhidos no passo S2.1.3, e atualiza o ficheiro voos.txt. Em caso de erro (por exemplo, na escrita do ficheiro), dá so_error e termina. Senão, dá so_success.

NUMBER=$(grep -n "$ORIGEM:$DESTINO" ./voos.txt | cut -d ":" -f 1)
LOTACAO=$(grep "$ORIGEM:$DESTINO" ./voos.txt | cut -d ":" -f 8)
CODE=$(grep "$ORIGEM:$DESTINO" ./voos.txt | cut -d ":" -f 1)
NEW_LOTACAO=$((LOTACAO-1))
if sed -i "${NUMBER}s/:[0-9]*$/:$NEW_LOTACAO/" ./voos.txt; then
    so_success "S2.2.3"
else
    so_error "S2.2.3"
    exit 1
fi

## S2.2.4. Regista a compra no ficheiro relatorio_reservas.txt, inserido uma nova linha no final deste ficheiro. Em caso de erro (por exemplo, na escrita do ficheiro), dá so_error e termina. Caso contrário, dá so_success.
LAST_LINE=$(tail -n 1 "./relatorio_reservas.txt")
LAST_ID=$(echo $LAST_LINE | cut -d ':' -f 1)
NEW_ID=$(expr $LAST_ID + 1)
DATE=$(date +'%Y-%m-%d')
TIME=$(date +'%Hh%M')
LINHA="$NEW_ID:$CODE:$ORIGEM:$DESTINO:$PRECO_VOO:$ID:$DATE:$TIME"
if echo "$LINHA" >> "./relatorio_reservas.txt"; then 
    so_success "S2.2.4"
else
    so_error "S2.2.4"
    exit 1
fi
