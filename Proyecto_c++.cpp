
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <windows.h>
using namespace std;
const int MAX = 10;
const int MAX_CARTAS = 52;
const int MAX_DADOS = 5;
const int VALOR_DADOS = 6;

struct usuarios{
    string nombres[MAX];
    string passwords[MAX];
    string emails[MAX];
    int ids[MAX];
    bool conectado[MAX];
    int saldos[MAX];
};

/*############## Declaracion de FUNCIONES usadas ##############*/
/**** FUNCIONES Mostrar Menús ****/
//Sin parámetros ya que no intervienen variables del main
int mostrar_menu_inicial();
int mostrar_opcion_agregar_otro_usuario();
int mostrar_menu_principal();
int mostrar_menu_usuario();
int mostrar_menu_jugar();
int mostrar_menu_turno_jugador_blackjack();

/**** FUNCIONES del Menú Principal ****/
int switch_menu_usuarios_del_menu_principal(int opcion, int contador, string nombres[], string passwords[], string emails[], int ids[], bool conectado[], int saldos[]);
void switch_jugar_juego(int opcion, int contador, bool conectado[], int saldos[]);

/**** FUNCIONES Usuario ****/
void agregar_usuario(int contador, string nombres[], string passwords[], string correo_e[], bool conectado[]);
string alta_nombre_usuario(int contador, string nombres[]);
string alta_nueva_password(int contador, string passwords[]);
bool comprobar_longitud_entrada_caracteres(string entrada);
string alta_nuevo_email(int contador, string correo_e[]);
bool acceder_al_menu_principal(bool conectado[],string nombres[], string passwords[], int contador);
void mostrar_dato_usuario_conectado(bool conectado[], int ids[], string nombres[], string emails[], string passwords[], int saldo[], int contador);
string cambiar_nombre(bool conectado[], string nombres[], int contador);
string cambiar_password(bool conectado[], string passwords[], int contador);
string cambiar_email(bool conectado[], string email[], int contador);
void mostrar_datos_usuarios(bool conectado[], int ids[], string nombres[], string emails[], string passwords[], int contador);

/*FUNCIONES de Juegos:
 Ahorcado*/
int jugar_al_ahorcado();

//BlackJack
int jugar_al_blackjack();
string generar_carta(string mazo_cartas_usadas[], int contador);
int dar_valor_a_la_carta(string carta, int suma, bool turno);
void imprimir_cartas_iniciales(string carta1, string carta2);
void imprimir_una_carta(string carta);

//Poker Dados
int jugar_al_poker_dados();
void generar_dados(string ronda[]);
float asignar_valor_tirada_dados(string ronda[]);

/*################## Fin declaración de FUNCIONES usadas ###################################*/

int main(){
    /*Declaracion del Struct con sus arrays*/
    usuarios usuario;
    usuario.nombres[MAX];
    usuario.passwords[MAX];
    usuario.emails[MAX];
    usuario.ids[MAX] = {0};
    usuario.conectado[MAX] = {false};
    usuario.saldos[MAX];
    /*Declaracion de variables usas en el Main()*/
    int contador_usuarios = 0; 
    bool usuario_verificado = false;
    int opcion_menu_inicial;
    int opcion_menu_principal;
    int saldo_en_juego = 0;
    //Asignación del saldo inicial
    for (int i = 0; i < MAX; i++){
        usuario.saldos[i] = 100;
    }
    
    /*##### Menu de Inicio #########*/
    do{
        opcion_menu_inicial = mostrar_menu_inicial();
        //Agregar usuario por primera vez.
        if (opcion_menu_inicial == 1){ 
            int agregar_otro_usuario_mas = 0;
            do{
                agregar_usuario(contador_usuarios, usuario.nombres, usuario.passwords, usuario.emails, usuario.conectado);
                contador_usuarios++;
                usuario.ids[contador_usuarios - 1] = contador_usuarios; //Autoincrementar el ID para cada nuevo usuario.
                opcion_menu_inicial = 2;
                system("cls");
                agregar_otro_usuario_mas = mostrar_opcion_agregar_otro_usuario();
            }while(agregar_otro_usuario_mas == 1);
        }
        system("cls");
        //Validar Usuario para acceder al Menu Principal
        if (opcion_menu_inicial == 2){ 
            usuario_verificado = acceder_al_menu_principal(usuario.conectado, usuario.nombres, usuario.passwords, contador_usuarios);  
        }      
    }while(usuario_verificado == false); //Salida al Menú Principal con el acceso correcto

    /*########### Menu Principal ###########*/
    system("cls");
    for (int i = 0; i < contador_usuarios; i++){
        if (usuario_verificado == true && usuario.conectado[i] == true){
            do{
                system("cls");
                opcion_menu_principal = mostrar_menu_principal();
                switch (opcion_menu_principal){
                    case 1: //Menu Usuario  
                        int opcion_menu_usuario;
                        system("cls");
                        do{
                            opcion_menu_usuario = mostrar_menu_usuario();
                            /*Llamada a la función que contiene el switch del menu usuario. RETURN el contador de usuarios, en caso de agregar nuevos usuarios*/
                            contador_usuarios = switch_menu_usuarios_del_menu_principal(opcion_menu_usuario, contador_usuarios, usuario.nombres, usuario.passwords, usuario.emails, usuario.ids, usuario.conectado, usuario.saldos); 
                        }while(opcion_menu_usuario != 7);
                        break;
                    case 2: //Menu Juegos
                        int opcion_menu_jugar;
                        saldo_en_juego = 0;
                        system("cls");
                        do{ //Bucle hasta pulsar 4 para regresar al menu pincipal
                            opcion_menu_jugar = mostrar_menu_jugar(); //Llamada funcion
                            /*Llamada a la función que contiene el switch del menu juegos */
                            switch_jugar_juego(opcion_menu_jugar, contador_usuarios, usuario.conectado, usuario.saldos);
                        }while(opcion_menu_jugar != 4);
                    default:
                        break;
                }
            } while(opcion_menu_principal !=3);
        i = contador_usuarios;        
        }
    }
    return 0;    
}

/*############# Definicion FUNCIONES usadas ###############*/
/*Funciones Mostar Menu */
int mostrar_menu_inicial(){
    int opcion = 0;
    do{
        cout << "MENU INICIAL \n";
        cout << "WELLCOME. \n";
        cout << "Pulse 1 para crear una cuenta de un nuevo usuario. \n";
        cin >> opcion;
        if (opcion != 1){
            cout << "Pulse la disponible. \n";
        } 
    } while (opcion != 1);
    return opcion;
}

int mostrar_opcion_agregar_otro_usuario(){
    int opcion;
    do{
    cout << "Pulse 1 para agregar otro usuario. \n";
    cout << "Pulse 2 para ir al Menu de acceso de usuarios registrados. \n";
    cin >> opcion;
    if (opcion != 1 && opcion != 2)
    {
        cout << "Pulse las opciones disponibles. \n";
    }
    
    }while(opcion != 1 && opcion != 2);
    return opcion;
}

int mostrar_menu_principal(){
    int opcion = 0;
    do{
    cout << "MENU PRINCIPAL\n";
    cout << "\tPulse 1 para el Menu Usuarios. \n";
    cout << "\tPulse 2 para el Menu Juegos. \n";
    cout << "\tPulse 3 para Salir. \n";
    cin >> opcion;
    if (opcion < 1 && opcion > 3){
        cout << "Pulse una opcion disponible. \n";
    }
    }while(opcion < 1 && opcion > 3);
    return opcion;
}

int mostrar_menu_usuario(){
    int opcion;
    do{
        cout << "MENU USUARIO \n";
        cout << "\tPulse 1 para agregar nuevo usuario. \n";
        cout << "\tPulse 2 para modificar nombre usuario. \n";
        cout << "\tPulse 3 para modificar password. \n";
        cout << "\tPulse 4 para modificar email. \n";
        cout << "\tPulse 5 para consultar datos usuario. \n";
        cout << "\tPulse 6 para listar y cambiar de usuario. \n";
        cout << "\tPulse 7 para volver al Menu Principal. \n";
        cin >> opcion;
        if (opcion < 1 || opcion > 7){
            cout << "Pulse las opciones disponibles. \n";
        }
    }while(opcion < 1 && opcion > 7);
    return opcion;
}

int mostrar_menu_jugar(){
    int opcion;
    do{
        cout << "SELECCIONA EL JUEGO: \n";
        cout << "\tPulse 1 para jugar al Ahorcado. \n";
        cout << "\tPulse 2 para jugar al BlackJack. \n";
        cout << "\tPulse 3 para jugar al PokerDados. \n";
        cout << "\tPulse 4 para volver al Menu Juegos. \n";
        cin >> opcion;
        if (opcion < 1 || opcion > 4){
            cout << "Pulse las opciones disponibles. \n";
        }
    }while(opcion < 1 && opcion > 4);
    return opcion;
}

int mostrar_menu_turno_jugador_blackjack(){
    int opcion;
    do
    {
        cout << "TURNO DEL JUGADOR \n";
        cout << "\tPulse 1 para pedir otra carta. \n";
        cout << "\tPulse 2 para planterse. \n";
        cout << "\tPulse 3 para abandonar (se pierde solo la midad de la apuesta). \n";
        cin >> opcion;
        if (opcion < 1 || opcion > 3){
            cout << "Pulse las opciones disponibles. \n";
        }
    } while (opcion < 1 && opcion > 3);
    return opcion;
}

/*Funciones Del Menu Principal*/
int switch_menu_usuarios_del_menu_principal(int opcion, int contador, string nombres[], string passwords[], string emails[], int ids[], bool conectado[], int saldos[]){    
    switch (opcion){
        case 1: //Agregar Nuevo Usuario
            if (contador >= MAX){  
                cout << "Maximo alcanzado. No se admiten usuarios nuevos.\n";
            }
            else{ //Agregar datos del usuario si no esta completo el array
                system("cls");
                agregar_usuario(contador, nombres, passwords, emails, conectado);
                contador++;
                ids[contador - 1] = contador; //Autoincrementar el ID para cada nuevo usuario.
            }
            break;
        case 2: //Modificar Nombre Usuario
            system("cls");
            for (int i = 0; i < contador; i++){
                if (conectado[i] == true){
                    nombres[i] = cambiar_nombre(conectado, nombres, contador);
                }     
            }
            break;
        case 3: //Modificar Password
            system("cls");
            for (int i = 0; i < contador; i++){
                if (conectado[i] == true){
                    passwords[i] = cambiar_password(conectado, passwords, contador);
                }                           
            }
            break;                        
        case 4: //Modificar Email
            system("cls");
            for (int i = 0; i < contador; i++){
                if (conectado[i] == true){
                    emails[i] = cambiar_email(conectado, emails, contador);
                }   
            }
            break;                            
        case 5: //Mostrar Datos del Usuario conectado
            system("cls");
            mostrar_dato_usuario_conectado(conectado, ids, nombres, emails, passwords, saldos, contador);
            break;
        case 6: //Mostrar lista de usuarios registrados y cambiar de usuario
            system("cls");
            mostrar_datos_usuarios(conectado, ids, nombres, emails, passwords, contador);
            bool verificar_usuario ;
            conectado[MAX] = {false};
            verificar_usuario = acceder_al_menu_principal(conectado, nombres, passwords, contador);                        
            break;
        default:
            break;
    }
    return contador;
}

void switch_jugar_juego(int opcion, int contador, bool conectado[], int saldos[]){
    int saldo_en_juego = 0;
    switch (opcion){
        case 1: //Jugar al Ahorcado
            system("cls");
            for (int i = 0; i < contador; i++){
                if (conectado[i] == true){
                    saldo_en_juego = jugar_al_ahorcado();
                    saldos[i] += saldo_en_juego;
                }   
            }
            saldo_en_juego = 0;
            break;
        case 2: //Jugar al Blackjack
            system("cls");
            for (int i = 0; i < contador; i++){
                if (conectado[i] == true){
                    saldo_en_juego = jugar_al_blackjack();
                    saldos[i] += saldo_en_juego;
                }   
            }
            saldo_en_juego = 0;
            break;
        case 3: //Jugar al Poker Dados
            system("cls");
            for (int i = 0; i < contador; i++){
                if (conectado[i] == true){
                    saldo_en_juego = jugar_al_poker_dados();
                    saldos[i] += saldo_en_juego;
                }   
            } 
            saldo_en_juego = 0;                          
            break;
        default:
            break;
    }
}

/*Funciones Usuario*/
void agregar_usuario(int contador, string nombres[], string passwords[], string correo_e[], bool conectado[]){
    system("cls");
    cout << "MENU REGISTRO NUEVO USUARIO \n";
    nombres[contador] = alta_nombre_usuario(contador, nombres);
    passwords[contador] = alta_nueva_password(contador, passwords);
    correo_e[contador] = alta_nuevo_email(contador, correo_e);
    conectado[contador] = false;
}

string alta_nombre_usuario(int contador, string nombres[]){
    string nombre;
    bool nombre_ocupado;
    bool longitud_nombre_valido;
    do{
        nombre_ocupado = false;
        do{
            longitud_nombre_valido = false;
            cout << "Introduzca el nombre de nuevo usuario (MAX 10 caracteres): ";
            cin >> nombre;
            longitud_nombre_valido = comprobar_longitud_entrada_caracteres(nombre);
            if (longitud_nombre_valido == false){
                cout << "Maximo de caracteres permitdo. \n";
            }
        }while(longitud_nombre_valido == false);
        if (longitud_nombre_valido == true){
            for (int i = 0; i < contador; i++){
                if (nombres[i] == nombre){
                    nombre_ocupado = true;
                    i = contador;
                    cout << "Ya existe. \n";
                }
            }
        } 
    } while (nombre_ocupado == true);
    return nombre;
}

string alta_nueva_password(int contador, string passwords[]){
    bool verificar_password = false;
    bool longitud_password_valido = false;
    string password_de_verificacion;
    do{
        do{
            cout << "Introduce la nueva password (Max 10 caracteres): \n";
            cin >> passwords[contador];
            longitud_password_valido = comprobar_longitud_entrada_caracteres(passwords[contador]);
            if (longitud_password_valido == false){
                    cout << "Maximo de caracteres permitdo. \n";
            }
        }while(longitud_password_valido == false);
        if (longitud_password_valido == true){
            cout << "Verifica la password: \n";
            cin >> password_de_verificacion;
            if (passwords[contador] == password_de_verificacion){
                verificar_password = true;
            }
            else{
                cout << "Las passwords no coinciden.\n";
            }
        }
    } while (verificar_password == false);
    return password_de_verificacion;
}

string alta_nuevo_email(int contador, string correo_e[]){
    bool correo_e_repetido = true;
    bool correo_e_valido = false;
    int posicion_arroba, posicion_punto;
    int contador_arrobas = 0;
    int contador_puntos = 0;
    string correo_e_auxiliar;
    while (correo_e_valido == false && correo_e_repetido == true){
        while (correo_e_valido == false){
            int longitud_correo_e;
            cout << "Introduce el email: \n";
            cin >> correo_e_auxiliar;
            longitud_correo_e = correo_e_auxiliar.length();
            if (correo_e_auxiliar[0] == '@' || correo_e_auxiliar[longitud_correo_e - 1] == '@' || correo_e_auxiliar[0] == '.' || correo_e_auxiliar[longitud_correo_e - 1] == '.'){
                cout << "Cuenta de Email incorrecta. Un email no puede empezar/acabar en @ o punto. \n";
            }
            else{
                for (int i = 0; i < longitud_correo_e; i++){
                    if (correo_e_auxiliar[i] == '@'){
                        contador_arrobas++;
                        posicion_arroba = i;
                    }
                    if (correo_e_auxiliar[i] == '.'){
                        contador_puntos++;
                        posicion_punto = i;
                    }      
                }
                if (contador_arrobas == 1 && contador_puntos > 0 && posicion_arroba < posicion_punto && correo_e_auxiliar[posicion_arroba + 1] != '.' && correo_e_auxiliar[posicion_arroba - 1] != '.'){
                    correo_e_valido = true;
                    //Restablecer valores a 0
                    contador_arrobas = 0;
                    contador_puntos = 0;

                }
                else{
                    cout << "Email no valido. Comprueba las @ y los puntos. \n";
                    correo_e_valido = false;
                    contador_arrobas = 0;
                    contador_puntos = 0;
                }
            }
        }
        for (int i = 0; i < contador; i++){
            if (correo_e[i] == correo_e_auxiliar){
                cout << "El email ya existe. \n";
                correo_e_repetido = true;
                correo_e_valido = false;
                i = contador;
            }
            else{
                correo_e_repetido = false;
            }   
        }
    } 
    return correo_e_auxiliar;
}

bool acceder_al_menu_principal(bool conectado[], string nombres[], string passwords[], int contador){
    string nombre_acceso, password_acceso;
    bool acceso_verificado = false;
    do{
        cout << "MENU DE ACCESO USUARIOS REGISTRADOS \n";
        cout << "Introduce el nombre de usuario: ";
        cin >> nombre_acceso;
        cout << "Introduce la password: ";
        cin >> password_acceso;
        for (int i = 0; i < contador; i++){
            conectado[i] = false;
            if (nombres[i] == nombre_acceso && passwords[i] == password_acceso){
                acceso_verificado = true;
                conectado[i] = true;
            }
        }
    } while (acceso_verificado == false);

    return acceso_verificado;
}

void mostrar_dato_usuario_conectado(bool conectado[], int ids[], string nombres[], string emails[], string passwords[], int saldo[], int contador){
    for (int i = 0; i < contador; i++){
        if (conectado[i] == true){
            cout << "ID: " << ids[i] << "  ";
            cout << "Nombre: " << nombres[i] << "  ";
            cout << "Email: " << emails[i] << "  ";
            cout << "Password: " << passwords[i] << "  ";
            cout << "Conectado.   ";
            cout << "Saldo: " << saldo[i] << "\n";
            i = contador;
        }
    }
}

string cambiar_nombre(bool conectado[], string nombres[], int contador){
    string nombre_nuevo;
    for (int i = 0; i < contador; i++){
        if (conectado[i] == true){
            nombre_nuevo = alta_nombre_usuario(contador, nombres);
        }    
    }
    return nombre_nuevo;
}

string cambiar_password(bool conectado[], string passwords[], int contador){
    string nueva_password;
    for (int i = 0; i < contador; i++){
        if (conectado[i] == true){
            nueva_password = alta_nueva_password(contador, passwords);
        }    
    }
    return nueva_password;
}

string cambiar_email(bool conectado[], string email[], int contador){
    string nueva_password;
    for (int i = 0; i < contador; i++){
        if (conectado[i] == true){
            nueva_password = alta_nuevo_email(contador, email);
        }    
    }
    return nueva_password;
}

void mostrar_datos_usuarios(bool conectado[], int ids[], string nombres[], string emails[], string passwords[], int contador){
    for (int i = 0; i < contador; i++){
        cout << "ID: " << ids[i] << "  ";
        cout << "Nombre: " << nombres[i] << "  ";
        cout << "Email: " << emails[i] << "  ";
        cout << "Password:  **********  ";
        if(conectado[i] == true){
            cout << "Conectado. \n";
        }
        else{
            cout << "No conectado. \n";
        }            
    }
}

bool comprobar_longitud_entrada_caracteres(string entrada){
    bool longitud_valida = false;
    int longitud_entrada = 0;
    longitud_entrada = entrada.length();
    if (longitud_entrada <= MAX){
        longitud_valida = true;
    }
    return longitud_valida;
}

/*Funciones juegos:
Ahoracado*/
int jugar_al_ahorcado(){
    int saldo_partida;
    char letra;
    string palabra_auxiliar;
    string palabra_usuario;
    int posicion_aleatoria = 0;
    string palabras_disponibles[MAX] = {"marinero", "aguacate", "retrospectiva", "alucinante", "azulejo", "rimbombante", "terciopelo", "edulcorante", "innifugo", "jactarse"};
    srand(time(NULL));
    posicion_aleatoria = rand()% 10;
    int fallos_restantes = 5;
    int longitud_palabra = 0;
    int contador_aciertos = 0;
    bool acierta_palabra = false;
    palabra_auxiliar = palabras_disponibles[posicion_aleatoria]; 
    longitud_palabra = palabra_auxiliar.length();
    cout << "La palabra tiene " << longitud_palabra << " letras.\n";
    bool letra_acertada[longitud_palabra] = {false};
    while (fallos_restantes > 0){
        int opcion;
        do{
            cout << "Pulsa 1 para introducir una letra. \tPulse 2 para resolver. \n";
            cin >> opcion;
        }while(opcion !=1 && opcion !=2);
        if (opcion == 1){
            cout << "Introduce una letra: \n";
            cin >> letra;
            for (int i = 0; i < longitud_palabra; i++){
                if (palabra_auxiliar[i] == letra){
                    letra_acertada[i] = true;
                    contador_aciertos++;    
                }
            }
            if (contador_aciertos > 0){
                cout << "Has acertado. La letra " << letra << " esta en la palabra " << contador_aciertos << " vez/veces.\n";
            }
            else{
                cout << "Fallaste. La letra " << letra << " no esta en la palabra. \n";
                fallos_restantes--;
            }
            for (int i = 0; i < longitud_palabra; i++){
                if (letra_acertada[i] == true){
                    cout << palabra_auxiliar[i] << " ";
                }
                else{
                    cout << "* ";
                }    
            }
        }
        else{
            cout << "Introduce la palabra: \n";
            cin >> palabra_usuario;
            if (palabra_usuario == palabra_auxiliar){
                acierta_palabra = true;
                fallos_restantes = 0;
            }
            else{
                fallos_restantes -= 3; 
            }
            
        }
        contador_aciertos= 0;
        if (fallos_restantes > 0){
            cout << "\nFallos restantes " << fallos_restantes << "\n";
        }    
    }
    if (acierta_palabra == true){
        cout << "\nEnhorabuen. Ganaste. \n";
        saldo_partida = 25;
    }
    else{
        cout << "\nPerdiste. Suerte la siguiente vez. \n";
        saldo_partida = -15;
    }
    return saldo_partida;
}

/* BlackJack */
int jugar_al_blackjack(){
    string mazo_cartas_usadas[MAX_CARTAS];
    string carta1_usuario, carta2_usuario, carta1_crupier, carta2_crupier;
    int valor_cartas1_jugador = 0; 
    int valor_cartas2_jugador = 0;
    int valor_cartas1_crupier = 0;
    int valor_cartas2_crupier = 0;
    bool turno_crupier = false;
    bool carta_repetida = false;
    int contador_cartas_usadas = 0;
    int suma_cartas_jugador = 0;
    int suma_cartas_crupier = 0;
    int opcion_jugador_tras_ver_cartas = 0;
    bool jugador_gana = false;
    int saldo_en_juego = 0;
    string carta_oculta_crupier = "************";
    cout << "Repartiendo Cartas Crupier... \n";
    carta1_crupier = generar_carta(mazo_cartas_usadas, contador_cartas_usadas);
    imprimir_cartas_iniciales(carta1_crupier, carta_oculta_crupier);
    contador_cartas_usadas++;
    carta2_crupier = generar_carta(mazo_cartas_usadas, contador_cartas_usadas);
    contador_cartas_usadas++;
    cout << "Repartiendo Cartas Jugador... \n";
    carta1_usuario = generar_carta(mazo_cartas_usadas, contador_cartas_usadas);
    contador_cartas_usadas++;
    carta2_usuario = generar_carta(mazo_cartas_usadas, contador_cartas_usadas);
    imprimir_cartas_iniciales(carta1_usuario, carta2_usuario);
    contador_cartas_usadas++;
    valor_cartas1_jugador = dar_valor_a_la_carta(carta1_usuario, suma_cartas_jugador,turno_crupier);
    suma_cartas_jugador += valor_cartas1_jugador;
    valor_cartas2_jugador = dar_valor_a_la_carta(carta2_usuario, suma_cartas_jugador,turno_crupier);
    suma_cartas_jugador += valor_cartas2_jugador;
    cout << "Puntuacion: " << suma_cartas_jugador << "\n";
    if (suma_cartas_jugador == 21)
    {
        cout << "BLACKJACK. Enhoranuena ganaste. \n";
        jugador_gana = true;
        saldo_en_juego = 15;
    }
    else{
        int contador_carta_turno = 0;
        string carta_reparto_aux;
        int valor_carta_repartida;
        string carta_de_reparto[MAX];
        do{
            valor_carta_repartida = 0;
            if (opcion_jugador_tras_ver_cartas == 1000){
                opcion_jugador_tras_ver_cartas = 2;
            }
            else if (opcion_jugador_tras_ver_cartas == 2000) {
                opcion_jugador_tras_ver_cartas = 0;
            }
            else{
                opcion_jugador_tras_ver_cartas = mostrar_menu_turno_jugador_blackjack();
            }
            switch (opcion_jugador_tras_ver_cartas){
                case 1:
                    carta_reparto_aux = generar_carta(mazo_cartas_usadas, contador_cartas_usadas);
                    valor_carta_repartida = dar_valor_a_la_carta(carta_reparto_aux, suma_cartas_jugador,turno_crupier /*nuevos suma y turno*/);
                    suma_cartas_jugador += valor_carta_repartida;
                    carta_de_reparto[contador_carta_turno] = carta_reparto_aux;
                    contador_cartas_usadas++;
                    contador_carta_turno++;
                    imprimir_cartas_iniciales(carta1_usuario, carta2_usuario);
                    for (int i = 0; i < contador_carta_turno; i++){
                        imprimir_una_carta(carta_de_reparto[i]);
                    }
                    cout << "\nPuntuacion " << suma_cartas_jugador << "\n";
                    if (suma_cartas_jugador > 21){
                        cout << " Te pasaste \n";
                        opcion_jugador_tras_ver_cartas = 1000;
                    }
                    else if (suma_cartas_jugador == 21){
                        cout << " 21. \n";
                        opcion_jugador_tras_ver_cartas = 1000;
                        jugador_gana = true;
                    }
                    break;
                case 2:
                    turno_crupier = true;
                    Sleep(2000);
                    valor_cartas1_crupier = dar_valor_a_la_carta(carta1_crupier, suma_cartas_crupier,turno_crupier);
                    suma_cartas_crupier += valor_cartas1_crupier;
                    valor_cartas2_crupier = dar_valor_a_la_carta(carta2_crupier, suma_cartas_crupier,turno_crupier);
                    suma_cartas_crupier += valor_cartas2_crupier;
                    cout << "TURNO DEL CRUPIER \n";
                    cout << carta1_crupier << "\t" << carta2_crupier << "\n";
                    cout << "Puntuacion " << suma_cartas_crupier << "\n";
                    Sleep(2000);
                    if (suma_cartas_crupier == 21)
                    {
                        cout << "21 BLACKJACK. \n";
                        jugador_gana = false;
                        saldo_en_juego = -10;
                    }
                    else{
                        contador_carta_turno = 0;
                        while (suma_cartas_crupier < 21){
                            carta_reparto_aux = generar_carta(mazo_cartas_usadas, contador_cartas_usadas);
                            valor_carta_repartida = dar_valor_a_la_carta(carta_reparto_aux, suma_cartas_crupier,turno_crupier);
                            suma_cartas_crupier += valor_carta_repartida;
                            carta_de_reparto[contador_carta_turno] = carta_reparto_aux;
                            contador_cartas_usadas++;
                            contador_carta_turno++;
                            cout << carta1_crupier << "\t\t" << carta2_crupier << "\t\t";
                            for (int i = 0; i < contador_carta_turno; i++){
                                cout << carta_de_reparto[i] << "\t\t";
                            }
                            cout << "\nPuntuacion " << suma_cartas_crupier << "\n";
                            Sleep(2000);
                        }
                        if (suma_cartas_crupier == 21){
                            cout << " 21. \n";
                        }
                        else{
                            cout << "El Crupier se pasa. \n";
                        }
                        cout << "El Jugador muestra " << suma_cartas_jugador << ".   El Crupier muestra " << suma_cartas_crupier << "\n";
                        if(suma_cartas_jugador == suma_cartas_crupier){
                            cout << "Empate. \n";
                        }
                        else{ 
                            if(suma_cartas_jugador < suma_cartas_crupier && suma_cartas_crupier != 21){
                                jugador_gana = true;
                            }
                            else if(suma_cartas_jugador > suma_cartas_crupier){
                                jugador_gana = false;   
                            }
                            if (jugador_gana == true)
                            {
                                saldo_en_juego = 10;
                                cout << "El Jugador gana. \n"; 
                            }
                            else{
                                cout << "El Cuprier gana. \n";
                                saldo_en_juego = -10;
                            }
                        }    
                    }
                    opcion_jugador_tras_ver_cartas = 2000;
                    turno_crupier = false; 
                    break;
                case 3:
                    opcion_jugador_tras_ver_cartas = 2000;
                    saldo_en_juego = -5;
                    break;
                default:
                    break;
            }
        }while(opcion_jugador_tras_ver_cartas != 0);
    }    
    return saldo_en_juego;
}

string generar_carta(string mazo_cartas_usadas[], int contador){
    
    struct barajas{ 
        string numero_carta[13] = {"As", "2", "3", "4", "5", "6", "7", "8", "9" , "10", "J", "Q", "K"};
        string palo_carta[4] = {"Trebol", "Diamantes", "Corazones", "Picas"};
    };
    barajas baraja1;
    int aleatorio_numero_carta, aleatorio_palo_carta;
    string carta_generada;
    bool carta_repetida;
    srand(time(NULL));
    do{
        aleatorio_numero_carta =  rand()% 13;
        aleatorio_palo_carta =  rand()% 4;
        carta_generada = baraja1.numero_carta[aleatorio_numero_carta] + " " + baraja1.palo_carta[aleatorio_palo_carta];
        carta_repetida = false;
        for (int i = 0; i < contador; i++){
            if (mazo_cartas_usadas[i] == carta_generada){
                carta_repetida = true;
            }
        }
    }while(carta_repetida == true);
    mazo_cartas_usadas[contador] = carta_generada;
    return carta_generada;
}

int dar_valor_a_la_carta(string carta, int suma, bool turno){
    int valor_carta;
    int opcion = 0;
    if (carta == "As Trebol" || carta == "As Diamantes" || carta == "As Corazones" || carta == "As Picas"){
        if (turno == true){ 
            if (suma + 11 <= 21){
                valor_carta = 11;
            }
            else if(suma + 11 > 21){
                valor_carta = 1;
            }
        }
        else{
            if (suma + 11 == 21){
                valor_carta = 11; 
            }
            else if(suma + 11 > 21){ 
                valor_carta = 1;
            }
            else{
                cout << "Pulsa 1 para usar el AS valor 11.      Pulsa 2 para usar el AS valor 1. \n";
                cin >> opcion;
                if (opcion == 1){
                    valor_carta = 11;
                }
                else{
                    valor_carta = 1;
                }
            }
        }   
    }
    else if(carta == "2 Trebol" || carta == "2 Diamantes" || carta == "2 Corazones" || carta == "2 Picas"){
        valor_carta = 2;
    }
    else if(carta == "3 Trebol" || carta == "3 Diamantes" || carta == "3 Corazones" || carta == "3 Picas"){
        valor_carta = 3;
    }
    else if(carta == "4 Trebol" || carta == "4 Diamantes" || carta == "4 Corazones" || carta == "4 Picas"){
        valor_carta = 4;
    }
    else if(carta == "5 Trebol" || carta == "5 Diamantes" || carta == "5 Corazones" || carta == "5 Picas"){
        valor_carta = 5;
    }
    else if(carta == "6 Trebol" || carta == "6 Diamantes" || carta == "6 Corazones" || carta == "6 Picas"){
        valor_carta = 6;
    }
    else if(carta == "7 Trebol" || carta == "7 Diamantes" || carta == "7 Corazones" || carta == "7 Picas"){
        valor_carta = 7;
    }
    else if(carta == "8 Trebol" || carta == "8 Diamantes" || carta == "8 Corazones" || carta == "8 Picas"){
        valor_carta = 8;
    }
    else if(carta == "9 Trebol" || carta == "9 Diamantes" || carta == "9 Corazones" || carta == "9 Picas"){
        valor_carta = 9;
    }
    else if(carta == "10 Trebol" || carta == "10 Diamantes" || carta == "10 Corazones" || carta == "10 Picas"){
        valor_carta = 10;
    }
    else if(carta == "J Trebol" || carta == "J Diamantes" || carta == "J Corazones" || carta == "J Picas"){
        valor_carta = 10;
    }
    else if(carta == "Q Trebol" || carta == "Q Diamantes" || carta == "Q Corazones" || carta == "Q Picas"){
        valor_carta = 10;
    }
    else if(carta == "K Trebol" || carta == "K Diamantes" || carta == "K Corazones" || carta == "K Picas"){
        valor_carta = 10;
    }
    return valor_carta;
}

void imprimir_cartas_iniciales(string carta1, string carta2){
    while(carta1.length() < 12){
        carta1 = ' ' + carta1;
    }
    while(carta2.length() < 12){
        carta2 = ' ' + carta2;
    }
    cout << "################\t################\n";
    cout << "#              #\t#              #\n";
    cout << "#              #\t#              #\n";
    cout << "#              #\t#              #\n";
    cout << "#              #\t#              #\n";
    cout << "# " << carta1 << " #\t# " << carta2 << " #\n";
    cout << "#              #\t#              #\n";
    cout << "#              #\t#              #\n";
    cout << "#              #\t#              #\n";
    cout << "#              #\t#              #\n";
    cout << "################\t################\n";
}

void imprimir_una_carta(string carta){
    while(carta.length() < 12){
        carta = ' ' + carta;
    } 
    cout << "################\n";
    cout << "#              #\n";
    cout << "#              #\n";
    cout << "#              #\n";
    cout << "#              #\n";
    cout << "# " << carta << " #\n";
    cout << "#              #\n";
    cout << "#              #\n";
    cout << "#              #\n";
    cout << "#              #\n";
    cout << "################\n";
}

/*Poker Dados*/
int jugar_al_poker_dados(){
    int apuesta = 5;
    string ronda_jugador[MAX_DADOS];
    string ronda_crupier[MAX_DADOS];
    float valor_mano_jugador;
    float valor_mano_crupier;
    int contador_dados = 0;
    int opcion_ronda_jugador;
    generar_dados(ronda_jugador);
    cout << "TU MANO ES \n";
    for(int i = 0; i < MAX_DADOS; i++){
        cout << ronda_jugador[i] << "\t";
    }
    do{
        cout << "\nPulsa: 1 para pasar.   2 para doblar apuesta.     3 para triplicar apuesta.    4 para retirarte.";
        cin >> opcion_ronda_jugador;
    }while(opcion_ronda_jugador < 1 || opcion_ronda_jugador > 4);
    if(opcion_ronda_jugador == 4){
        cout << "El jugador se retira. \n";
        apuesta = -2;
    }
    else{
        cout << "MANO JUGADOR \n";
        for(int i = 0; i < MAX_DADOS; i++){
            cout << ronda_jugador[i] << "\t";
        }
        valor_mano_jugador = asignar_valor_tirada_dados(ronda_jugador);
        cout << "\nMANO CRUPIER \n";
        generar_dados(ronda_crupier);
        for(int i = 0; i < MAX_DADOS; i++){
            cout << ronda_crupier[i] << "\t";
        }
        valor_mano_crupier = asignar_valor_tirada_dados(ronda_crupier);
        if(opcion_ronda_jugador == 2){
            apuesta = 10;
        }
        else if(opcion_ronda_jugador == 3){
            apuesta = 15;
        }
        if(valor_mano_jugador == valor_mano_crupier){
            cout << "Empate. Generando unos al azar para el desempate.\n";
            int numero_azar_jugador, numero_azar_crupier;
            do{
                numero_azar_jugador = 1 + rand() % 100;
                numero_azar_crupier = 1 + rand() % 100;
                
            }while(numero_azar_jugador == numero_azar_crupier);
            if(numero_azar_jugador > numero_azar_crupier){
                cout << "El jugador gana " << apuesta << " creditos con " << numero_azar_jugador << " que gana al crupier con " << numero_azar_crupier << "\n";
            }
            else{
                cout << "El crupier con " << numero_azar_crupier << " gana al jugador con " << numero_azar_jugador << ", que pierde " << apuesta << " creditos \n";
                apuesta = apuesta - apuesta - apuesta;
            }  
        }
        else if(valor_mano_jugador > valor_mano_crupier){
            cout << "El jugador gana " << apuesta <<  " creditos \n";
        }
        else{
            cout << "Crupier Gana. \nEl jugador pierde " << apuesta <<  " creditos \n";
            apuesta = apuesta - apuesta - apuesta;
        }
        Sleep(3000);
    }  
    return apuesta;
}

void generar_dados(string ronda[]){
    int posicion_dado;
    int contador_dados = 0;
    string valor_dados[VALOR_DADOS] = {"AS", "K", "Q", "J", "10", "9"};
    srand(time(NULL));
    while (contador_dados < MAX_DADOS){
        posicion_dado = rand() % 6;
        ronda[contador_dados] = valor_dados[posicion_dado];
        contador_dados++;
    }
}

float asignar_valor_tirada_dados(string ronda[]){
    float valor_mano;
    int contador_valor_dados[VALOR_DADOS] = {0};
    int contador_parejas = 0;
    bool posicion_ocupada[MAX_DADOS] = {false};
    //Contar las cartas de la mano
    for(int i = 0; i < MAX_DADOS; i++){
        if(ronda[i] == "AS" && posicion_ocupada[i] == false){
            contador_valor_dados[0]++;
            posicion_ocupada[i] = true;
        }
        if(ronda[i] == "K" && posicion_ocupada[i] == false){
            contador_valor_dados[1]++;
            posicion_ocupada[i] = true;
        }
        if(ronda[i] == "Q" && posicion_ocupada[i] == false){
            contador_valor_dados[2]++;
            posicion_ocupada[i] = true;
        }
        if (ronda[i] == "J" && posicion_ocupada[i] == false){
            contador_valor_dados[3]++;
            posicion_ocupada[i] = true;
        }
        if(ronda[i] == "10" && posicion_ocupada[i] == false){
            contador_valor_dados[4]++;
            posicion_ocupada[i] = true;
        }
        if(ronda[i] == "9" && posicion_ocupada[i] == false){
            contador_valor_dados[5]++;
            posicion_ocupada[i] = true;
        }
    }
    // Contar parejas
    for(int i = 0; i < VALOR_DADOS; i++){
        if(contador_valor_dados[i] == 2){
            contador_parejas++;
        }     
    }
    // Comprobar Repoker y asignar valores
    if(contador_valor_dados[0] == 5 || contador_valor_dados[1] == 5 || contador_valor_dados[2] == 5 || contador_valor_dados[3] == 5 || contador_valor_dados[4] == 5 || contador_valor_dados[5] == 5){
        if(contador_valor_dados[0] == 5){
            valor_mano = 10.9;
            cout << "Repoker de Ases\n";
        }
        else if(contador_valor_dados[1] == 5){
            valor_mano = 10.8;
            cout << "Repoker de Reyes\n";
        }
        else if(contador_valor_dados[2] == 5){
            valor_mano = 10.7;
            cout << "Repoker de Damas \n";
        }
        else if(contador_valor_dados[3] == 5){
            valor_mano = 10.6;
            cout << "Repoker de Sotas \n";
        }
        else if(contador_valor_dados[4] == 5){
            valor_mano = 10.5;
            cout << "Repoker de dieces\n";
        }
        else if(contador_valor_dados[5] == 5){
            valor_mano = 10.4;
            cout << "Repoker de nueves\n";
        }
    }
    // Comprobar Escalera y asignar valor
    else if(contador_valor_dados[1] == 1 && contador_valor_dados[2] == 1 && contador_valor_dados[3] == 1 && contador_valor_dados[4] == 1){
        valor_mano = 7;
        cout << "Escalera \n";
    }
    // Comprobar Poker y asignar valor
    else if(contador_valor_dados[0] == 4 || contador_valor_dados[1] == 4 || contador_valor_dados[2] == 4 || contador_valor_dados[3] == 4 || contador_valor_dados[4] == 4 || contador_valor_dados[5] == 4){
        if(contador_valor_dados[0] == 4){
            valor_mano = 9.9;
            cout << "Poker de Ases \n";
        }
        else if(contador_valor_dados[1] == 4){
            valor_mano = 9.8;
            cout << "Poker de Reyes \n";
        }
        else if(contador_valor_dados[2] == 4){
            valor_mano = 9.7;
            cout << "Poker de Damas \n";
        }
        else if(contador_valor_dados[3] == 4){
            valor_mano = 9.6;
            cout << "Poker de Sotas \n";
        }
        else if(contador_valor_dados[4] == 4){
            valor_mano = 9.5;
            cout << "Poker de Dieces \n";
        }
        else if (contador_valor_dados[5] == 4){
            valor_mano = 9.4;
            cout << "Poker de Nueves\n";
        }
    }
    // Comprobar Full o Trio y asignar valor
    else if(contador_valor_dados[0] == 3 || contador_valor_dados[1] == 3 || contador_valor_dados[2] == 3 || contador_valor_dados[3] == 3 || contador_valor_dados[4] == 3 || contador_valor_dados[5] == 3){
        if (contador_valor_dados[0] == 3){ //Full de Ases
            if(contador_valor_dados[1] == 2 || contador_valor_dados[2] == 2 || contador_valor_dados[3] == 2 || contador_valor_dados[4] == 2 || contador_valor_dados[5] == 2){
                if(contador_valor_dados[1] == 2){
                    valor_mano = 8.99;
                    cout << "Full Ases/Reyes \n";
                }
                else if(contador_valor_dados[2] == 2){
                    valor_mano = 8.98;
                    cout << "Full Ases/Damas \n";
                }
                else if(contador_valor_dados[3] == 2){
                    valor_mano = 8.97;
                    cout << "Full Ases/Sotas \n";
                }
                else if(contador_valor_dados[4] == 2){
                    valor_mano = 8.96;
                    cout << "Full Ases/Dieces \n";
                }
                else if(contador_valor_dados[5] == 2){
                    valor_mano = 8.95;
                    cout << "Full Ases/Nueves \n";
                }
            }
            else{ // Sino es Full es Trio
                valor_mano = 6.9;
                cout << "Trio de Ases \n";
            }  
        }
        else if (contador_valor_dados[1] == 3){ // Full de Reyes
            if (contador_valor_dados[0] == 2 || contador_valor_dados[2] == 2 || contador_valor_dados[3] == 2 || contador_valor_dados[4] == 2 || contador_valor_dados[5] == 2){
                if(contador_valor_dados[0] == 2){
                    valor_mano = 8.89;
                    cout << "Full Reyes/Ases \n";
                }
                else if(contador_valor_dados[2] == 2){
                    valor_mano = 8.88;
                    cout << "Full Reyes/Damas \n";
                }
                else if(contador_valor_dados[3] == 2){
                    valor_mano = 8.87;
                    cout << "Full Reyes/Sotas \n";
                }
                else if(contador_valor_dados[4] == 2){
                    valor_mano = 8.86;
                    cout << "Full Reyes/Dieces \n";
                }
                else if(contador_valor_dados[5] == 2){
                    valor_mano = 8.85;
                    cout << "Full Reyes/Nueves \n";
                }
            }
            else{ //Sino es Full es Trio
                valor_mano = 6.8; 
                cout << "Trio de Reyes \n";
            }  
        }
        else if(contador_valor_dados[2] == 3){ // Full de Damas
            if(contador_valor_dados[0] == 2 || contador_valor_dados[1] == 2 || contador_valor_dados[3] == 2 || contador_valor_dados[4] == 2 || contador_valor_dados[5] == 2){
                if(contador_valor_dados[0] == 2){
                    valor_mano = 8.79;
                    cout << "Full Damas/Ases \n";
                }
                else if(contador_valor_dados[1] == 2){
                    valor_mano = 8.78;
                    cout << "Full Damas/Reyes \n";
                }
                else if(contador_valor_dados[3] == 2){
                    valor_mano = 8.77;
                    cout << "Full Damas/Sotas \n";
                }
                else if(contador_valor_dados[4] == 2){
                    valor_mano = 8.76;
                    cout << "Full Damas/Dieces \n";
                }
                else if(contador_valor_dados[5] == 2){
                    valor_mano = 8.75;
                    cout << "Full Damas/Nueves \n";
                }
            }
            else{ //Sino es Full es Trio
                valor_mano = 6.7; 
                cout << "Trio de Damas \n";
            }  
        }
        else if(contador_valor_dados[3] == 3){ //Full de Sotas
            if(contador_valor_dados[0] == 2 || contador_valor_dados[1] == 2 || contador_valor_dados[2] == 2 || contador_valor_dados[4] == 2 || contador_valor_dados[5] == 2){
                if(contador_valor_dados[0] == 2){
                    valor_mano = 8.69;
                    cout << "Full Sotas/Ases \n";
                }
                else if(contador_valor_dados[1] == 2){
                    valor_mano = 8.68;
                    cout << "Full Sotas/Reyes \n";
                }
                else if(contador_valor_dados[3] == 2){
                    valor_mano = 8.67;
                    cout << "Full Sotas/Damas \n";
                }
                else if(contador_valor_dados[4] == 2){
                    valor_mano = 8.66;
                    cout << "Full Sotas/Dieces \n";
                }
                else if(contador_valor_dados[5] == 2){
                    valor_mano = 8.65;
                    cout << "Full Sotas/Nueves \n";
                }
            }
            else{ // Sino es Full es Trio
                valor_mano = 6.6;  
                cout << "Trio de Sotas \n";
            }  
        }
        else if (contador_valor_dados[4] == 3){ // Full de Dieces
            if(contador_valor_dados[0] == 2 || contador_valor_dados[1] == 2 || contador_valor_dados[2] == 2 || contador_valor_dados[3] == 2 || contador_valor_dados[5] == 2){
                if(contador_valor_dados[0] == 2){
                    valor_mano = 8.59;
                    cout << "Full Dieces/Ases \n";
                }
                else if(contador_valor_dados[1] == 2){
                    valor_mano = 8.58;
                    cout << "Full Dieces/Reyes \n";
                }
                else if(contador_valor_dados[2] == 2){
                    valor_mano = 8.57;
                    cout << "Full Dieces/Damas \n";
                }
                else if(contador_valor_dados[3] == 2){
                    valor_mano = 8.56;
                    cout << "Full Dieces/Sotas \n";
                }
                else if(contador_valor_dados[5] == 2){
                    valor_mano = 8.55;
                    cout << "Full Dieces/Nueves \n";
                }
            }
            else{ // Sino es Full es Trio
                valor_mano = 6.5; 
                cout << "Trio de Dieces \n";
            }  
        }  
        else if (contador_valor_dados[5] == 3){ // Full de Nueves
            if(contador_valor_dados[0] == 2 || contador_valor_dados[1] == 2 || contador_valor_dados[2] == 2 || contador_valor_dados[3] == 2 || contador_valor_dados[4] == 2){
                if(contador_valor_dados[0] == 2){
                    valor_mano = 8.49;
                    cout << "Full Nueves/Ases \n";
                }
                else if(contador_valor_dados[1] == 2){
                    valor_mano = 8.48;
                    cout << "Full Nueves/Reyes \n";
                }
                else if(contador_valor_dados[2] == 2){
                    valor_mano = 8.47;
                    cout << "Full Nueves/Damas \n";
                }
                else if(contador_valor_dados[3] == 2){
                    valor_mano = 8.46;
                    cout << "Full Nueves/Sotas \n";
                }
                else if(contador_valor_dados[4] == 2){
                    valor_mano = 8.45;
                    cout << "Full Nueves/Dieces \n";
                }
            }
            else{ // Sino es Full es Trio
                valor_mano = 6.4;
                cout << "Trio de Nueves \n";

            }  
        }
    }
    else if (contador_parejas > 0){
        // Comprobar Dobles Parejas
        if(contador_parejas == 2){
            if(contador_valor_dados[0] == 2){ // Ases
                if(contador_valor_dados[1] == 2){
                    cout << "Dobles Parejas Ases/Reyes \n";
                    valor_mano = 5.99;
                }
                else if(contador_valor_dados[2] == 2){
                    cout << "Dobles Parejas Ases/Damas \n";
                    valor_mano = 5.98;
                }
                else if(contador_valor_dados[3] == 2){
                    cout << "Dobles Parejas Ases/Sotas \n";
                    valor_mano = 5.97;
                }
                else if(contador_valor_dados[4] == 2){
                    cout << "Dobles Parejas Ases/Dieces \n";
                    valor_mano = 5.96;
                }
                else if(contador_valor_dados[5] == 2){
                    cout << "Dobles Parejas Ases/Nueves \n";
                    valor_mano = 5.97;
                }
            }
            else if(contador_valor_dados[1] == 2){ // Reyes
                if(contador_valor_dados[2] == 2){
                    cout << "Dobles Parejas Reyes/Damas \n";
                    valor_mano = 5.88;
                }
                else if(contador_valor_dados[3] == 2){
                    cout << "Dobles Parejas Reyes/Sotas \n";
                    valor_mano = 5.87;
                }
                else if(contador_valor_dados[4] == 2){
                    cout << "Dobles Parejas Reyes/Dieces \n";
                    valor_mano = 5.86;
                }
                else if(contador_valor_dados[5] == 2){
                    cout << "Dobles Parejas Reyes/Nueves \n";
                    valor_mano = 5.85;
                }
            }
            else if(contador_valor_dados[2] == 2){ // Damas
                if(contador_valor_dados[3] == 2){
                    cout << "Dobles Parejas Damas/Sotas \n";
                    valor_mano = 5.77;
                }
                else if(contador_valor_dados[4] == 2){
                    cout << "Dobles Parejas Damas/Dieces \n";
                    valor_mano = 5.76;
                }
                else if(contador_valor_dados[5] == 2){
                    cout << "Dobles Parejas Damas/Nueves \n";
                    valor_mano = 5.75;
                }
            }
            else if(contador_valor_dados[3] == 2){ // Sotas
                if(contador_valor_dados[4] == 2){
                    cout << "Dobles Parejas Sotas/Dieces \n";
                    valor_mano = 5.66;
                }
                else if(contador_valor_dados[5] == 2){
                    cout << "Dobles Parejas Sotas/Nueves \n";
                    valor_mano = 5.65;
                }
            }
            else if(contador_valor_dados[4] == 2){ // Dieces
                if(contador_valor_dados[5] == 2){
                    cout << "Dobles Parejas Dieces/Nueves \n";
                    valor_mano = 5.55;
                }
            }
            else if(contador_valor_dados[5] == 2){ // Nueves
                cout << "Dobles Parejas Nueves/Nueves \n";
                valor_mano = 5.4;
            }
        }
        // Comprobar Parejas
        else if(contador_parejas == 1){
            if(contador_valor_dados[0] == 2){
                cout << "Pareja de Ases \n";
                valor_mano = 4.9;
            }
            else if(contador_valor_dados[1] == 2){
                cout << "Pareja de Reyes \n";
                valor_mano = 4.8;
            }
            else if(contador_valor_dados[2] == 2){
                cout << "Pareja de Damas \n";
                valor_mano = 4.7;
            }
            else if(contador_valor_dados[3] == 2){
                cout << "Pareja de Sotas \n";
                valor_mano = 4.6;
            }
            else if(contador_valor_dados[4] == 2){
                cout << "Pareja de Dieces \n";
                valor_mano = 4.5;
            }
            else if(contador_valor_dados[5] == 2){
                cout << "Pareja de Nueves \n";
                valor_mano = 4.4;
            }    
        }   
    }
    // Sino se da el Repoker, poker, full, escalera, trio, dobles parejas o parejas; es Carta alta
    else{
        valor_mano = 3;
        cout << "Carta Alta \n";
    }
    return valor_mano;
}