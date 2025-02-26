# ProyectoPrimerTrimestreCpp
Trabajo sobre lo aprendido en Cpp. Gestión de usuarios y 3 pequeños juegos.

# Breve descripción del proyecto

El proyecto consiste en el almacenamiento, de hasta 10 usuarios, y la gestión de sus datos tales como: nombre, contraseña, email (estos 3 se solicitan por teclado); si está conectado o no, su id de jugador y su saldo (estas 3 se asignan de forma automática). Además, se podrá modificar los datos que se solicitan por teclado, una vez creados.
Después consiste en 3 versiones de juegos rápidos, más o menos conocidos, donde se obtendrá una recompensa positiva o negativa, dependiendo de si gana o pierde el jugador. Dichos juegos son el Ahorcado, el BlackJack y el Poker Dados.

# Manual de uso de software

El programa está construido para que el usuario se mueva a base de menús. (¡En ningún caso se deberá pulsar una letra como opción a un menú! para que funcione correctamente).
Menú de Inicio: Al comienzo será necesario registrar al menos a un usuario, pudiendo registrar más antes de continuar. Tras el primer registro, en caso de no querer registrar más, iremos al Menú de acceso de usuarios mediante login y contraseña.
Una vez confirmado el usuario y contraseña, se nos mostrará el Menú principal, que contiene 2 submenús: el de Usuario y el de Juegos.

# Menú Usuarios                                                                
1. Introducir nuevo usuario.                                                  
2. Modificar nombre.
3. Modificar password.                                                       
4. Modificar Email.
5. Consultar datos del usuario conectado.                                     
6. Consultar usuarios registrados y cambiar usuario.
7. Salir al Menú Principal
   
# Menú Juegos
1. Jugar al Ahorcado.
2. Jugar al BlackJack.
3. Jugar al Poker Dados.
4. Salir al Menú Principal.
   
# Información a tener en cuenta sobre la gestión de usuarios:
Para el nombre y la contraseña se establece un límite de 10 caracteres.
El email deberá cumplir con algunas de las condiciones necesarias de un email real, es decir solo podrá tener un @, este no puede ir ni al principio ni al final. Además, también controlo que al menos haya un punto y no esté situado justo delante ni detrás del @ , así como que no esté ni al final ni al principio de la cuenta de email.
Ambos, tanto el nombre de usuario como el email no podrán repetirse.
En la opción 6 tras listar los usuarios registrados, será obligatorio volver hacer el login, aunque sea con el mismo usuario que ya está conectado. 

# Información a tener en cuenta sobre los juegos:
Ahorcado:
Funciona a través de un menú de 2 opciones: 1 para decir letra y 2 para comprobar la palabra si se cree saber.
Hay un total de 10 palabras, que se asignan aleatoriamente.
Se podrá decir tanto vocales como consonantes.
Tras introducir la primera letra, se mostrará si se acierta la letra o no y la longitud de la palabra mediante *(asteriscos)  para las letras ocultas.
Se dispondrá de 5 fallos, si se intenta comprobar la palabra de forma errónea se restará 3 fallos.
El juego repartirá 25 créditos por averiguar la palabra y restará 15 créditos si se consumen todos los intentos disponibles.

BlackJack:
Se usa una sola baraja, generando primero las 2 cartas del crupier y posteriormente las cartas del jugador (todas aleatoriamente). 
Después se mostrará por pantalla 1 carta del crupier y la otra oculta. Seguidamente se mostrarán las 2 cartas del jugador seguido de un menú con 3 opciones: 1 Pedir carta, 2 Plantarse y 3 Abandonar. Este menú se ejecutará mientras el jugador no se plante y este por debajo de 21. (Si alcanza o supera los 21, automáticamente pasa al turno del crupier). Si el jugador saca BlackJack de inicio la ronda termina.
El crupier mostrará la carta oculta y estará obligado a pedir carta siempre que esté por debajo de 21.
El programa asigna valor a las cartas y compara las del jugador y crupier indicando quién gana, o en su defecto empate.
No se podrá dividir las cartas si salen 2 iguales.
Los Ases, para el crupier está diseñado para que automáticamente decida si es un 1 o un 11. Siendo la condición pasarse de 21, es decir, si valiendo 11 se pasa de 21 entonces valdrá 1. El jugador, salvo que haga BlackJack con la segunda carta, se le solicitará elegir el valor para ese As, 11 ó 1, a menos que la suma pase de 21 si valiera 11 que entonces, sin preguntar, valdrá 1.
El reparto de créditos queda de la siguiente manera: - 5 créditos si abandonas, -10 créditos si gana el crupier, 10 si gana el jugador y 15 si hace BlackJack el jugador.

Poker Dados:
Para este juego se generará aleatoriamente una ronda de dados, primero será el turno del jugador y una vez este haya finalizado sus acciones se mostrará la ronda del crupier.
Trás mostrar por pantalla la tirada del jugador, este se moverá por un menú con 4 opciones: 1 para pasar, 2 para duplicar la apuesta, 3 para triplicar la apuesta y 4 para abandonar la ronda.
Una vez elegida la opción, se mostrará por pantalla la tirada del jugador y del crupier, además indicando quién gana. En caso de empate, se generan 2 números aleatorios del 1 al 100, uno para el jugador y otro para el crupier, el más alto gana.(Si es el mismo número para ambos, se generan de nuevo).
Las apuestas son: inicial 5 créditos, 10 créditos si se duplica, 15 créditos si se triplica (si el jugador gana, las apuestas serán positivas; si el jugador pierde, las apuestas serán negativas) y -2 créditos si el jugador se retira.

# Problemas encontrados durante la realización del programa y sus soluciones (Sólo aparecen alguna, las que más me llamaron la atención para recalcar):
Problema: 
Al intentar asignar el “saldo” de los usuarios en la función para crear los datos del usuario: nombre, password, etc…este, sin saber por qué, no guardaba correctamente los datos.
Solución:
Al iniciar el Main, tras declarar las variables usadas, asignó con un bucle for el saldo inicial para todo el array que contiene los saldos de cada usuario. (Quizás no sea la mejor solución, pero es válida en cuanto a funcionalidad)

Problema:
El array booleano “conectado[]” del struct “usuarios” daba problemas(había valores en true, que no debían) en el acceso inicial o una vez dentro del menú usuarios cuando creabas un usuario nuevo y luego querías realizar un cambio de usuario.
Solución:
Crear otra variable para confirmar el acceso, que recibiera el retorno de la función correspondiente.  Además, igualé a false las posiciones del array “conectado” en el case 6 del switch del menú de usuarios.

Problema: 
Al principio, en el juego poker dados, al intentar contabilizar las dobles parejas y parejas de las manos, daba error y nunca entraban en las parejas.
Solución:
Añadí un contador de parejas y use un condicional if para cuando eran dobles parejas o parejas solo.

Problema:
Tras moverme por varios menús y sus submenús, al pulsar la opción de salir, a veces(no siempre, creo que dependía de los usuarios registrados y el conectado), requiere que se vuelva a pulsar la opción de salir desde el menú principal.
Solución:
Me fije que estaba dentro de un bucle, y dependiendo de las iteraciones que le quedarán solicitaba la salida de nuevo (volvía al menú principal). Y tras la salida del bucle(anidado) que controla el menú principal, le di el valor de salida a “i” para que en la siguiente iteración salga del bucle for principal (usado para comprobar qué usuario está conectado de los existentes). 

Problema:
En el juego del BlackJack, hago un bucle que dentro contiene un switch y tras terminar la opciones del jugador este volvía a ejecutarse (do while) sin tener que hacerlo.
Solución:
Creo una variable a la que dar valor cuando se desee continuar con el juego porque el jugador ya terminó sus acciones y al principio del bucle pongo condicionales si esos valores se cumplen, pasando al punto que le corresponde.

Problema:
En el juego del BlackJack, cuando sale un As, puede tener 2 valores: 11 o 1, de primeras puse que se pregunte qué valor elegir. Para el jugador sirve esa opción, pero para la máquina debía ser automático.
Solución:
Sacar un algoritmo que lo automatiza. De manera que si al salir un As con valor 11, la suma de la mano del crupier supera los 21, el As pasará a valer 1. De lo contrario, valdrá 11.
