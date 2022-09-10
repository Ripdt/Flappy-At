#include <iostream>
#include <windows.h>
#include <conio.h> ///para o getch()
#include <time.h> ///para o time()

using namespace std;


/**
    F L A P P Y B I R D (M2 Algoritmos)
    - Lembrando: não permitido o uso de funções e variáveis compostas como structs, vetores e matrizes
    - Corrigir os rastros (pássaro e obstáculos)
    - Implementar colisão
    - Implementar pontuação (mais um ponto para cada obstáculo superado)
    - Fazer 2 obstáculos simultâneos (obstaculo1 e obstaculo2)
    - Deixar a pontuação visível durante todo o jogo
    - Definir marcos para acelerar a velocidade

    DESENVOLVEDORES:
        - Filipi Scalvin da Costa
        - Luiz Carlos Braga
        - Luiz Felipe Mantoani Fantini
        - Vitor Alexandre Silveira
*/

int main()
{
    ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, A SEGUIR.
    //INICIO: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    //FIM: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
    //INÍCIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
    COORD coord;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
    ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, ACIMA.

    srand(time(NULL)); //gera um número aleatório a todo momento
    //Não é possível utilizar setLocale pois, caso utilizado, implicará negativamente na geração de obstáculos (219 não imprimirá um bloco branco)

    int bird_x = 5, bird_y = 10; // posição do pássaro
    int eixoY, obstaculo_x1 = 0, obstaculo_y1 = 0, obstaculo_x2 = 0, obstaculo_y2 = 0; // obstáculos
    int tecla=' '; // comando para controle do pássaro -- int recebe valor da tabela ASCII
    int placar = 0, record = 0, velocidade = 400;
    int opcao = '1'; // opção para recomeçar o jogo caso gameover (0 p parar)

    ///DESENHO DO CENÁRIO
    cout << "-PLACAR: 0-------------------------------------------------------------------------------------------";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "-----------------------------------------------------------------------------------------------------";

    while (opcao != '3') { // esse laço faz o jogo rodar, se usuário optar por 3, o jogo para
        ///POSICIONA O OBSTÁCULO
        if (obstaculo_x1 == 0) { // se obstáculo estiver saindo da tela ou na primeira passagem
            obstaculo_x1 = 100;
            obstaculo_y1 = rand() % 14 + 3; // gera um novo
        }
        if (obstaculo_x1 == 55) { // quando um obstáculo estiver no meio da tela gera o segundo
            obstaculo_x2 = 100;
            obstaculo_y2 = rand() % 14 + 3;
        }
        eixoY = 1; //default do contador p percorrer todos os campos do eixoY
        while (eixoY < 20) { //loop pelas posições do eixo

            /// OBSTÁCULO 1
            coord.X = obstaculo_x1;    coord.Y = eixoY;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            if (eixoY<obstaculo_y1 - 1 || eixoY>obstaculo_y1 + 1) {
                cout << char(219);
            }
            else {
                cout << " ";
            }
            coord.X = obstaculo_x1 + 4;    coord.Y = eixoY;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << " ";

            /// OBSTÁCULO 2
            if (obstaculo_x2 > 0 && obstaculo_y2 > 0) { // se já houver um segundo obstáculo
                coord.X = obstaculo_x2;    coord.Y = eixoY;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                if (eixoY<obstaculo_y2 - 1 || eixoY>obstaculo_y2 + 1) {
                    cout << char(219);
                }
                else {
                    cout << " ";
                }
                coord.X = obstaculo_x2 + 4;    coord.Y = eixoY;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout << " ";
            }

            if (obstaculo_x1 > 95) { // tira gradativamente o obstáculo da tela
                coord.X = obstaculo_x1 - 95;    coord.Y = eixoY;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout << " ";
            }

            if (obstaculo_x2 > 95) {
                coord.X = obstaculo_x2 - 95;    coord.Y = eixoY;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout << " ";
            }
            eixoY++;
        }

        ///APAGA RASTRO DO PÁSSARO
        coord.X = bird_x;    coord.Y = bird_y; // coordenada do pássaro antes de ser alterada
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // aponta cursor para coordenada
        cout << " "; // apaga pássaro antigo

        ///VERIFICA COMANDO DO JOGADOR
        if (_kbhit()) { //verifica se uma tecla foi pressionada
            tecla = _getch(); //verifica comando do jogador
        }
        if (tecla == '1') { // capslock ativo ou não
            bird_y--;
            tecla = 0;
        }
        ///PÁSSARO CAI 1 POSIÇÃO SE NÃO FOI PRESSIONADO PARA SUBIR
        else {
            bird_y++;
        }


        ///VERIFICA COLISÃO
        if (bird_y >= 20 || bird_y <= 0 // chão e teto
            || (bird_x >= obstaculo_x1 - 1 && bird_x <= obstaculo_x1 + 4 && (bird_y<obstaculo_y1 - 1 || bird_y>obstaculo_y1 + 1)) // Obstáculo 1
            || (bird_x >= obstaculo_x2 - 1 && bird_x <= obstaculo_x2 + 4 && (bird_y<obstaculo_y2 - 1 || bird_y>obstaculo_y2 + 1)))// Obstáculo 2
        {
            system("CLS"); // Limpa Tela
            cout << "-----------------------------------------------------------------------------------------------------";
            cout << "\n\n\n\n\n\n\nVOCE BATEU\n\n";
            if (placar > record) {
                cout << "VOCE ULTRAPASSOU SEU RECORDE!\nNOVO: " << placar << " - ANTIGO: " << record;
                record = placar;
            }
            else {
                cout << "SEU PLACAR: " << placar << " - RECORDE: " << record << endl;
            }
            cout << "\nAperte 2 para reiniciar o jogo ou 3 para sair\n\n\n\n\n\n\n\n\n";
            cout << "-----------------------------------------------------------------------------------------------------";
            while (opcao != '2' && opcao != '3') { // exige o usuário a clicar em uma destas teclas
                opcao = _getch(); //recebe opção do jogador sem precisar apertar o enter
            }
            if (opcao != '3')
            {
                system("CLS");
                cout << "-PLACAR: 0 ------------------------------------------------------------------------------------------";
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "-----------------------------------------------------------------------------------------------------";

                bird_x = 5; bird_y = 10; // Define a posição inicial do pássaro após a colisão
                coord.X = bird_x;    coord.Y = bird_y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout << char(64); // "Imprime" o pássaro na tela do jogo

                ///VOLTA VARIÁVEIS AOS VALORES DEFAULT
                obstaculo_x1 = 1; // diminuirá 1 logo abaixo
                obstaculo_y1 = 0;
                obstaculo_x2 = 0;
                obstaculo_y2 = 0;
                velocidade = 400;
                placar = 0;
                opcao = '1'; // para forçar o jogador a clicar espaço ou zero novamente
            }
        }
        else { // se não bateu, imprime o pássaro em sua nova posição
            ///POSICIONA O PÁSSARO
            coord.X = bird_x;    coord.Y = bird_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << char(64); // ASCII 64 = @
        }

        ///AUMENTA PLACAR
        if (bird_x == obstaculo_x1 + 3 || bird_x == obstaculo_x2 + 3) { // aumenta placar depois de passar **todo** obstáculo
            placar++;
            coord.X = 1;    coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << "PLACAR: " << placar;
            if (placar % 5 == 0) { // se placar for múltiplo de 5
                velocidade = velocidade * 0.75; // aumenta a velocidade diminuindo o valor de sleep
            }
        }
        ///OBSTÁCULO AVANÇA UMA POSIÇÃO PARA ESQUERDA
        obstaculo_x1--;
        obstaculo_x2--;

        ///TEMPO DE ESPERA
        Sleep(velocidade);
    }
    return 0;
}

