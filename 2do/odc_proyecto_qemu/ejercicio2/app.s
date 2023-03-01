.equ SCREEN_WIDTH, 		640 //
.equ SCREEN_HEIGH, 		480 //
.equ BITS_PER_PIXEL,  	32 

.globl main
main:
	// X0 contiene la direccion base del framebuffer
 	mov x20, x0	// Save framebuffer base address to x20	
	//---------------- CODE HERE ------------------------------------
infloop:
	movz x5, 0x00, lsl 16
	movk x5, 0xffff, lsl 00
	
	bl FondoRor
	mov x19, 4 				//bits per pixel 
	//en x20 se guarda la posicion inicial de la pantalla
	mov x21 , SCREEN_WIDTH	
	mov x22 , SCREEN_HEIGH
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////DIBUJANDO LA CONSOLA////////////////////////////////////////////////////////////////

	mov x1, 410				//seteo tamanio   (alto)
	mov x2, 300 			// seteo tamanio  (largo)
	movz x5, 0xff, lsl 16	//color
	movk x5, 0xff66, lsl 00	//color
	mov x3, 40				//EJE Y
	movz x4, 170			//EJE X
	bl posicion
	BL RectanguloPintado

	mov x1, 267	      		//seteo tamanio   (alto)
	mov x2, 240				// seteo tamanio  (largo)
	movz x5, 0xff, lsl 16	//color 
	mov x3, 79 				//EJE Y
	movz x4, 200			//EJE X
	mov x19, 4 				//bits per pixel 
	movz x5, 0xff, lsl 0
	bl posicion
	bl RectanguloDegrade

	movz x5, 0x75, lsl 16
	movz x5, 0x7A7E, lsl 0
	bl Botones

//////////////////////////////////////FIN CONSOLA////////////////////////////////////////////////////////////////
	movz x10, 0x08ff, lsl 16 

	bl Delay

 	mov x1, 10	      		//seteo tamanio   (alto)
	mov x3, 185				//EJE Y
	movz x4, 203			//EJE X
	movz x5, 0xff, lsl 16
	bl LetraT
	bl Delay

	bl LetraE
	bl Delay

	bl LetraT2
	bl Delay

	bl LetraR
	bl Delay

	bl LetraI
	bl Delay

	bl LetraS
	bl Delay
////voy a tener que tener una funcion que me dibuje el RectanguloDegrade y las letras para poder hacer aparecer y
////desaparecer los bloques de abajo

	bl consolaLetras
	movz x10, 0x03ff,  lsl 16
	movz x9, 0x0002, lsl 0        //cant de parpadeos 

parpadear:
	bl bloquesInitColor
	movz x5, 0xff, lsl 16 
	bl Botones

	bl Delay

	bl consolaLetras
	movz x5, 0x75, lsl 16
	movz x5, 0x7A7E, lsl 0
	bl Botones
	
	bl Delay

	sub x9, x9, 1
	cbnz x9, parpadear 

	bl bloquesInitColor
	movz x5, 0xff, lsl 16 
	bl Botones

	movz x10, 0x1fff, lsl 16 
	
	mov x14, x10
	bl Delay

//////////////////////////////////reseteo el fondo para empezar el juego///////////////////////////////////////////////
	movz x5, 0x75, lsl 16
	movz x5, 0x7A7E, lsl 0
	bl Botones
 	
	mov x1, 267	      		//seteo tamanio   (alto)
	mov x2, 240				// seteo tamanio  (largo)
	movz x5, 0xff, lsl 16	//color 
	mov x3, 79 				//EJE Y
	movz x4, 200			//EJE X
	movz x5, 0xff, lsl 0
	bl posicion
    bl RectanguloDegrade
///////////////////////////////empiezo a hacer caer las fichas//////////////////////////////////////////////////////////
//primera ficha//
	movz x10, 0x4ff, lsl 16 
	
	mov x1, 20	      		//seteo tamanio   (alto)
	mov x3, 78 				//EJE Y
	mov x4, 280				//EJE X

	mov x11, 45
caida: 
	bl posicion
	bl Tblock

	bl Delay
	bl fondolimpio

	sub x11,x11, 1
	add x3,x3,5 
	cbnz x11, caida

	add x3, x3, 3
	bl bloque1

//segundo bloque
	mov x1, 20	      		//seteo tamanio   (alto)
	mov x3, 78 				//EJE Y
	mov x4, 280				//EJE X

	mov x11, 14

caida2: 
	bl posicion
	bl Jblock

	bl Delay
	bl fondolimpio
	bl bloque1

	sub x11,x11, 1
	add x3,x3,5 
	cbnz x11, caida2

	mov x9, 2 
 	
	movz x5, 0xff, lsl 16
	bl BotonArriba 

	mov x11, 18
caida3: 
	cbz x9, boton
	sub x9,x9,1 

	bl posicion
	bl Jblockright

	bl Delay
	bl fondolimpio
	bl bloque1

	sub x11,x11, 1
	add x3,x3,5 
	cbnz x11, caida3

	bl bloque2
	b skip

boton:
	movz x5, 0x75, lsl 16
	movz x5, 0x7A7E, lsl 0
	movz x9, 0xffff, lsl 16		//para no volver a saltar aca
	bl BotonArriba 
	b caida3

	skip:

//tercer bloque
   mov x1, 20        		//seteo tamanio   (alto)
   mov x3, 78              	//EJE Y
   mov x4, 280         		//EJE X
 
   mov x11, 10
 
caida4:
   bl posicion
   bl Zblock
 
   bl Delay
   bl fondolimpio
   bl bloque1
   bl bloque2
 
   sub x11,x11, 1
   add x3,x3,5
   cbnz x11, caida4
 
   mov x9, 2
  
   movz x5, 0xff, lsl 16
   bl BotonDerecho
 
   mov x11, 19
   add x4, x4, 21
caida5:
   cbz x9, boton1
   sub x9,x9,1
 
   bl posicion
   bl Zblock
 
   bl Delay
   bl fondolimpio
   bl bloque1
   bl bloque2
 
   sub x11,x11, 1
   add x3,x3,5
   cbnz x11, caida5
 
   bl bloque3
   b skip1
 
boton1:
   movz x5, 0x75, lsl 16
   movz x5, 0x7A7E, lsl 0
   movz x9, 0xffff, lsl 16     //para no volver a saltar aca
   bl BotonDerecho
   b caida5
 
   skip1:
//cuarto bloque//
   mov x1, 20        		//seteo tamanio   (alto)
   mov x3, 78              	//EJE Y
   mov x4, 280         		//EJE X
 
   mov x11, 21
caida6:
   bl posicion
   bl Oblock
 
   bl Delay
   bl fondolimpio
   bl bloque1
   bl bloque2
   bl bloque3
 
   sub x11,x11, 1
   add x3,x3,5
   cbnz x11, caida6
 
   add x3, x3, 3
   bl bloque4
//quinto//
	mov x1, 20	      		//seteo tamanio   (alto)
	mov x3, 78 				//EJE Y
	mov x4, 280				//EJE X

	mov x11, 2

caida7: 
	bl posicion
	bl Lblock

	bl Delay
	bl fondolimpio
	bl bloque1
	bl bloque2
	bl bloque3
	bl bloque4

	sub x11,x11, 1
	add x3,x3,5 
	cbnz x11, caida7


	movz x5, 0xff, lsl 16
	bl BotonArriba 

	mov x11, 3
	mov x9, 2

 caida8: 
	cbz x9, boton2
	sub x9,x9,1 

	bl posicion
	bl Lblockleft

	bl Delay
	bl fondolimpio
	bl bloque1
	bl bloque2
	bl bloque3
	bl bloque4

	sub x11,x11, 1
	add x3,x3,5 
	cbnz x11, caida8

	bl bloque5
	b skip2 

boton2:
	movz x5, 0x75, lsl 16
	movz x5, 0x7A7E, lsl 0
	movz x9, 0xffff, lsl 16		//para no volver a saltar aca
	bl BotonArriba
	b caida8

	skip2:	
//sexto//
	mov x1, 20	      			//seteo tamanio   (alto)
	mov x3, 78 					//EJE Y
	mov x4, 300					//EJE X
bl Iblock

b Fin

////////////////////////////////////FUNCIONES////////////////////////////////////////////////
b end
trianguloInvertido:
///////////////////////////TRIANGULO INVERTIDO //////////////////////////////////////////////
	sub sp,sp, #8  			
    str x30,[sp,#0]  		

	BL posicion
	mov x14, x1     	     	//seteo un contador de cuantas veces voy a ejecutar el loop
	lsr x14, x14, 1				//divido por dos (la mitad del tamanio del triangulo)
 
 looppintar:
//----------------------------linea vertical izquierda -------------------------------------
	mov x15, x1					//x2 = x1

lineaIzquierda:
	stur w5, [x0]				//pinto el primer pixel
	madd X7, x21, X19, x19
	sub x0, x0, x7          	//al indice lo resto en 640 posiciones(4*640) y lo corro 1 posicion (4*1) a la izquierda
	sub x15,x15,1				//decremento el count del eje Y
	cbnz x15,lineaIzquierda		//if x2 no es 0 voy a loop6
//----------------------------linea de arriba --------------------------------------------
	mov x15, x1					//x2 = x1
	lsl x15, x15, 1   			//el doble de donde estaba antes
lineaArriba:
	stur w5, [x0]				//pinto el primer pixel
	add x0,x0,4					//al indice lo aumento en 1 posicion(4*1)
	sub x15,x15,1				//decremento el count del eje X
	cbnz x15,lineaArriba		//if x2 no es 0 voy a loop3

//-------------------------linea medida vertical derecha  ------------------------------
	mov x15, x1					//x2 = x1       largo del lado
lineaDerecha:
	stur w5, [x0]				//pinto el primer pixel
	msub x7,x21, x19, x19				//al indice lo aumento en 640posiciones(4*640)
	sub x0, x0, x7
	sub x15,x15,1				//decremento el count del eje Y
	cbnz x15,lineaDerecha		//if x2 no es 0 voy a loop5
//--------------------------------------------------------------------------------------
	msub x0, x21, x19, x0      		// cambio la posicion
	sub x1, x1, 2          		//dismunuyo el tamaño 
	sub x14, x14, 1				//disminuyo el contador de cuantas veces voy a ejecutar el loop
	cmp x14, 0
	b.ne looppintar
//---------------------------------------------------------------------------------------
	stur w5, [x0]				//pinto el ultimo pixel del medio que quedo sin pintar */
	msub x0, x21, x19, x0 			//muevo el x0 al lugar del ultimo pixel que quedo sin pintar
	stur w5, [x0]				//pinto el ultimo pixel del medio que quedo sin pintar */

	ldr x30,[sp,#0]  			
    add sp,sp, #8  				
	ret
///////////////////////////////////FIN TRIANGULO INVERTIDO /////////////////////////////////////////////
trianguloNormal:
///////////////////////////TRIANGULO NORMAL //////////////////////////////////////////////
	sub sp,sp, #8  			
    str x30,[sp,#0]  		

	BL posicion
	mov x14, x1     	     //seteo un contador de cuantas veces voy a ejecutar el loop
	lsr x14, x14, 1			//divido por dos (la mitad del tamanio del triangulo)
 
 looppintar1:
//----------------------------linea vertical izquierda -------------------------------------
	mov x15, x1				//x2 = x1

lineaIzquierda1:

	stur w5, [x0]			//pinto el primer pixel
	msub x7,x21, x19, x19				//al indice lo aumento en 640posiciones(4*640)
	sub x0, x0, x7			//al indice lo resto en 640 posiciones(4*640) y lo corro 1 posicion (4*1) a la izquierda
	sub x15,x15,1				//decremento el count del eje Y
	cbnz x15,lineaIzquierda1			//if x2 no es 0 voy a loop6

//----------------------------linea de abajo --------------------------------------------
	mov x15, x1				//x2 = x1
	lsl x15, x15, 1   		//el doble de donde estaba antes
lineaAbajo1:
	stur w5, [x0]			//pinto el primer pixel
	add x0,x0,4				//al indice lo aumento en 1 posicion(4*1)
	sub x15,x15,1				//decremento el count del eje X
	cbnz x15,lineaAbajo1			//if x2 no es 0 voy a loop3

//-------------------------linea medida vertical derecha  ------------------------------
	mov x15, x1				//x2 = x1       largo del lado
lineaDerecha1:
	stur w5, [x0]			//pinto el primer pixel
	madd x7, x21, x19, x19
	sub x0,x0, x7			//al indice lo aumento en 640posiciones(4*640)
	sub x15,x15,1				//decremento el count del eje Y
	cbnz x15,lineaDerecha1			//if x2 no es 0 voy a loop5
//--------------------------------------------------------------------------------------
	madd x0, x21, x19, x0       	// cambio la posicion
	sub x1, x1, 2          	//dismunuyo el tamaño 
	sub x14, x14, 1			//disminuyo el contador de cuantas veces voy a ejecutar el loop
	cmp x14, 0
	b.ne looppintar1
//---------------------------------------------------------------------------------------
	stur w5, [x0]			//pinto el ultimo pixel del medio que quedo sin pintar */
	msub x0,x21,x19,x0			//muevo el x0 al lugar del ultimo pixel que quedo sin pintar
	stur w5, [x0]			//pinto el ultimo pixel del medio que quedo sin pintar */

	ldr x30,[sp,#0]  
    add sp,sp, #8  
	ret
/////////////////////////////////// FIN TRIANGULO NORMAL /////////////////////////////////////////////

trianguloDerecho:
///////////////////////////TRIANGULO DERECHO //////////////////////////////////////////////

	sub sp,sp, #8  			
    str x30,[sp,#0]  		

	BL posicion
	mov x14, x1     	     //seteo un contador de cuantas veces voy a ejecutar el loop
	lsr x14, x14, 1			//divido por dos (la mitad del tamanio del triangulo)
 
 looppintarDerecho:

//----------------------------linea vertical izquierda -------------------------------------
	mov x15, x1				//x2 = x1

lineaArribaDerecha:

	stur w5, [x0]			//pinto el primer pixel
	madd x7,x21,x19,x19 
	sub x0,x0,x7			//al indice lo resto en 640 posiciones(4*640) y lo corro 1 posicion (4*1) a la izquierda
	sub x15,x15,1				//decremento el count del eje Y
	cbnz x15,lineaArribaDerecha			//if x2 no es 0 voy a loop6

//----------------------------linea de arriba --------------------------------------------
	mov x15, x1						//x2 = x1
	lsl x15, x15, 1   				//el doble de donde estaba antes
lineaIzquierdaDerecha:
	stur w5, [x0]					//pinto el primer pixel
	madd x0,x21,x19,x0					//al indice lo aumento en 1 posicion(4*1)
	sub x15,x15,1					//decremento el count del eje X
	cbnz x15,lineaIzquierdaDerecha	//if x2 no es 0 voy a loop3

//-------------------------linea medida vertical derecha  ------------------------------
	mov x15, x1					//x2 = x1       largo del lado
lineaAbajoDerecha:
	stur w5, [x0]				//pinto el primer pixel
	msub x7,x21,x19,x19				//al indice lo aumento en 640posiciones(4*640)
	add x0, x0, x7
	sub x15,x15,1				//decremento el count del eje Y
	cbnz x15,lineaAbajoDerecha	//if x2 no es 0 voy a loop5
//--------------------------------------------------------------------------------------
	sub x0, x0, 4       	// cambio la posicion
	sub x1, x1, 2          	//dismunuyo el tamaño 
	sub x14, x14, 1			//disminuyo el contador de cuantas veces voy a ejecutar el loop
	cmp x14, 0
	b.ne looppintarDerecho
//---------------------------------------------------------------------------------------
	stur w5, [x0]			//pinto el ultimo pixel del medio que quedo sin pintar */
	msub x0,x21,x19,x0			//muevo el x0 al lugar del ultimo pixel que quedo sin pintar
	stur w5, [x0]			//pinto el ultimo pixel del medio que quedo sin pintar */

	ldr x30,[sp,#0]  
    add sp,sp, #8  
	ret
///////////////////////////////////FIN TRIANGULO DERECHO /////////////////////////////////////////////
trianguloIzquierdo:
///////////////////////////TRIANGULO IZQUIERDO //////////////////////////////////////////////

	sub sp,sp, #8  			
    str x30,[sp,#0]  		

	BL posicion
	mov x14, x1     	     //seteo un contador de cuantas veces voy a ejecutar el loop
	lsr x14, x14, 1			//divido por dos (la mitad del tamanio del triangulo)
 
 looppintarIzquierdo:

//----------------------------linea vertical izquierda -------------------------------------
	mov x15, x1				//x2 = x1

lineaArribaIzquierda:

	stur w5, [x0]					//pinto el primer pixel
	msub x7,x21,x19,x19 					//al indice lo resto en 640 posiciones(4*640) y lo corro 1 posicion (4*1) a la izquierda
	add x0,x0,x7
	sub x15,x15,1					//decremento el count del eje Y
	cbnz x15,lineaArribaIzquierda	//if x2 no es 0 voy a loop6

//----------------------------linea de arriba --------------------------------------------
	mov x15, x1						//x2 = x1
	lsl x15, x15, 1   				//el doble de donde estaba antes
lineaDerechaIzquierda:
	stur w5, [x0]					//pinto el primer pixel
	madd x0,x21,x19,x0					//al indice lo aumento en 1 posicion(4*1)
	sub x15,x15,1					//decremento el count del eje X
	cbnz x15,lineaDerechaIzquierda	//if x2 no es 0 voy a loop3

//-------------------------linea medida vertical derecha  ------------------------------
	mov x15, x1							//x2 = x1       largo del lado
lineaAbajoIzquierdo:
	stur w5, [x0]						//pinto el primer pixel
	madd x7,x21,x19,x19
	sub x0,x0, x7						//al indice lo aumento en 640posiciones(4*640)
	sub x15,x15,1						//decremento el count del eje Y
	cbnz x15,lineaAbajoIzquierdo		//if x2 no es 0 voy a loop5
//--------------------------------------------------------------------------------------
	add x0, x0, 4       	// cambio la posicion
	sub x1, x1, 2          	//dismunuyo el tamaño 
	sub x14, x14, 1			//disminuyo el contador de cuantas veces voy a ejecutar el loop
	cmp x14, 0
	b.ne looppintarIzquierdo
//---------------------------------------------------------------------------------------
	stur w5, [x0]			//pinto el ultimo pixel del medio que quedo sin pintar */
	msub x0,x21,x19,x0			//muevo el x0 al lugar del ultimo pixel que quedo sin pintar
	stur w5, [x0]			//pinto el ultimo pixel del medio que quedo sin pintar */

	ldr x30,[sp,#0]  
    add sp,sp, #8  
	ret
///////////////////////////////////FIN TRIANGULO IZQUIERDO /////////////////////////////////////////////
// *CUADRADO/rectangulo con relleno**/

RectanguloPintado:

mov x14, x1 				//salvo en x14 el alto 
siguiente:
	mov x15, x2        		//salvo en x15 el largo
raya:
	stur w5,[x0]	   		// Seteo el color del pixel N
	add x0,x0,4	   			// proximo pixel
	sub x15,x15,1	   		// decrement X counter
	cbnz x15, raya	 		//si no termine de pintar la primera raya pinto el proximo pixel 
	sub x14, x14, 1 		//decrement y counter 
	msub x0, x19, x2, x0    //vuelvo al principio de la linea x0 - x2 * 4	= x0	
	madd x0, x21, x19, x0 	//muevo el puntero al inicio de la proxima linea (640*4+x0)=x0
	cbnz x14, siguiente

	ret

posicion:
///////////////////////////////////SETEO POSICION////////////////////////////////////////////

	sub sp,sp, #16
    str x3,[sp,#0]
    str x4,[sp,#8]

	mov x21 , SCREEN_WIDTH	//seteo x21 con mi largo de pantalla
	
	mov x0, x20				//seteo x0 en primer pixel
	mov x13, xzr			//seteo el x13 en vacio x13 registro auxiliar
	madd x13, x3, x21, x4	//en x13 guardo el resultado de 640*x3 (coord de y) + x
	lsl x13, x13, 2         //multiplico mi resultado anterior por lo que ocupa cada pixel (4)
	add x0,x0, x13			//guardo en x0 lo que calcule en mi registro aux

	ldr x4,[sp,#8]  
	ldr x3, [sp,#0] 
    add sp,sp, #16  
	ret
/////////////////////////////////FIN POSICION////////////////////////////////////////////////
FondoRor: 
// AHORA VOY  HACER UN PATRON DE COLORES CON ROR (retroalimentacion con lsl)
	sub sp, sp, 8
	str x30, [sp,#0]

	mov x0, x20                		// vuelvo a guardar el inicio del arreglo en x0
	movz X10, 0x4f, lsl 16 			// tiempo de animacion
   	movz x5, 0x4F3C, lsl 0 

	mov x14, SCREEN_HEIGH         	// Y Size
	sub x14, x14, 1  
loop1:
	mov x15, SCREEN_WIDTH         	// X Size
	ror w5, w5,  #30  				//si cambio el numero desp de # cambio el fondo
loop0:

	stur w5,[x0]	   				// Set color of pixel N
	add x0,x0,4	   					// Next pixel
	sub x15,x15,1	   				// decrement X counter
	cbnz x15,loop0	   				// If not end row jump
	sub x14,x14,1	   				// Decrement Y counter
	bl Delay
	cbnz x14, loop1	   				// if not last row, jump

	ldr x30, [sp, #0]
	add sp, sp, 8
	ret
//-------------------------------------------------------------

consolaLetras:

	sub sp,sp, #8
    str x30,[sp,#0]

	mov x1, 267	      			//seteo tamanio   (alto)
	mov x2, 240					// seteo tamanio  (largo)
	movz x5, 0xff, lsl 16		//color 
	mov x3, 79 					//EJE Y
	movz x4, 200				//EJE X
	mov x19, 4 					//bits per pixel 
	movz x5, 0xff, lsl 0
	bl posicion
	bl RectanguloDegrade
 
 	mov x1, 10	      			//seteo tamanio   (alto)
	mov x3, 185					//EJE Y
	movz x4, 203				//EJE X
	movz x5, 0xff, lsl 16

	bl LetraT
	bl LetraE
	bl LetraT2
	bl LetraR
	bl LetraI
	bl LetraS  

	ldr x30,[sp,#0]  
    add sp,sp, #8  
ret

//-------------------------------------------------------------
RectanguloDegrade:
mov x14, x1 				//salvo en x14 el alto 
lsr x14, x14, 1 			//divido en 2 

siguiente2:
	mov x15, x2        		//salvo en x15 el largo
	add x5, x5, 1
raya2:
	stur w5,[x0]	   		// Seteo el color del pixel N
	add x0,x0,4	   			// proximo pixel
	sub x15,x15,1	   		// decrement X counter
	cbnz x15, raya2	 		//si no termine de pintar la primera raya pinto el proximo pixel 
	sub x14, x14, 1 		//decrement y counter 
	msub x0, x19, x2, x0    //vuelvo al principio de la linea x0 - x2 * 4	= x0	
	madd x0, x21, x19, x0 	//muevo el puntero al inicio de la proxima linea (640*4+x0)=x0
	cbnz x14, siguiente2
	//la mitad de la pantalla
mov x14, x1 				//salvo en x14 el alto 
lsr x14, x14, 1 			//divido en 2 
siguiente3:
	mov x15, x2        		//salvo en x15 el largo
	sub x5, x5, 1
raya3:
	stur w5,[x0]	   		// Seteo el color del pixel N
	add x0,x0,4	   			// proximo pixel
	sub x15,x15,1	   		// decrement X counter
	cbnz x15, raya3	 		//si no termine de pintar la primera raya pinto el proximo pixel 
	sub x14, x14, 1 		//decrement y counter 
	msub x0, x19, x2, x0    //vuelvo al principio de la linea x0 - x2 * 4	= x0	
	madd x0, x21, x19, x0 	//muevo el puntero al inicio de la proxima linea (640*4+x0)=x0
	cbnz x14, siguiente3

	ret
///////////////////////////////////////////////////////////////////////////////////////////////////
////solo llamar con tamaños pares//////

cuadradito:
	sub sp,sp, 40  			// Reserve space for registers and after Store Registe in stack
	str x5, [sp, #32]
	str x3, [sp,#24]
	str x4, [sp,#16]
	str x1, [sp, #8]
    str x30,[sp,#0]


	mov x14, 2				// x14 = 6 ancho del color oscuro
	mov x2, x1
	sub x2, x2, 2   		// guardo el tamaño que voy a usar para llamar al rectangulo

 loop15:
	mov x15, x1 
	madd x0, x21, x19 ,x0	//aumento en 1 en x y en 1 en y aca aumente en y
	add x0, x0, 4			// aca aumente x 
 
// hacer el cuadrado por lineas
loop11:
	stur w5, [x0]			//pinto el primer pixel
	add x0,x0, 2560			//al indice lo aumento en 640posiciones(4*640)
	sub x15,x15,1			//decremento el count del eje Y
	cbnz x15,loop11			//if x2 no es 0 voy a loop2
//-----------------linea medida horizontal inferior ---------
	mov x15, x1				//x2 = x1
loop12:
	stur w5, [x0]			//pinto el primer pixel
	add x0,x0,4				//al indice lo aumento en 1 posicion(4*1)
	sub x15,x15,1			//decremento el count del eje X
	cbnz x15,loop12			//if x2 no es 0 voy a loop3
//-------------linea medida vertical derecha ------------------
	mov x15, x1				//x2 = x1       largo del lado
loop13:
	stur w5, [x0]			//pinto el primer pixel
	sub x0,x0, 2560			//al indice lo aumento en 640posiciones(4*640)
	sub x15,x15,1			//decremento el count del eje Y
	cbnz x15,loop13			//if x2 no es 0 voy a loop5
//-----------------linea medida horizontal sup------------
	mov x15, x1				//x2 = x1       largo del lado

loop14:
	stur w5, [x0]			//pinto el primer pixel
	sub x0,x0,4				//al indice lo aumento en 1 posicion(4*1)
	sub x15,x15,1			//decremento el count del eje X
	cbnz x15,loop14			//if x2 no es 0 voy a loop4

	sub x14, x14, 1
 	sub x1, x1, 2 			//resto en 2 el tamaño

	cbnz x14, loop15 

 	mov x5,x6 
	mov x1,x2 
	//rectangulo pintado
	mov x14, x1 			//salvo en x14 el alto 
siguiente4:
	mov x15, x2        		//salvo en x15 el largo
raya4:
	stur w5,[x0]	   		// Seteo el color del pixel N
	add x0,x0,4	   			// proximo pixel
	sub x15,x15,1	   		// decrement X counter
	cbnz x15, raya4	 		//si no termine de pintar la primera raya pinto el proximo pixel 
	sub x14, x14, 1 		//decrement y counter 
	msub x0, x19, x2, x0    //vuelvo al principio de la linea x0 - x2 * 4	= x0	
	madd x0, x21, x19, x0 	//muevo el puntero al inicio de la proxima linea (640*4+x0)=x0
	cbnz x14, siguiente4
	mov x6, x5  			//vuelvo 6 a su valor

	ldr x5, [sp, #0]
	ldr x1, [sp, #8]
	ldr x4, [sp,#16]
	ldr x3, [sp,#24]
	ldr x5, [sp, #32]
	add sp,sp, 40

	ret
/////////////////////////////////////////////////////////////////////////////////////////////////////
Tetris:
//////////////////////////////////////////////////////////////////////////////////////////////////////
LetraT:
	sub sp,sp, #8  			
    str x30,[sp,#0]  		

movz x6, 0x1F00, lsl 00		//color claro 	F22B00 
movk x6, 0xAF, lsl 16 
movz x5, 0xD6, lsl 16		// color oscuro

bl posicion
BL cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

add x4,x4,x1
bl posicion
bl cuadradito

add x3, x3, x1		
sub x4, x4, 10
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito   

add x3, x3, x1
bl posicion 
bl cuadradito   

add x3,x3,x1
bl posicion 
bl cuadradito  

sub x3, x3, 40
add x4, x4, 30			//los pongo en las posiciones para empezar la otra letra

	ldr x30,[sp,#0]  	// Restore X30 value from stack
    add sp,sp, #8  		// Restore SP to initial position
ret
///////////////////////////////////////////////////////////////////////
LetraE:
	sub sp,sp, #8  				// Reserve space for two registers
    str x30,[sp,#0]  			// Store Register X30 in stack

	movz x6, 0xf3, lsl 16		//color oscuro   F35D00
	movk x6, 0x5d00, lsl 00 	//color oscuro
	movz x5, 0xc2, lsl 16   	//color claro  C24A00
	movk x5, 0x4a00, lsl 00		//color claro

bl posicion
BL cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion
bl cuadradito

add x3, x3,x1
sub x4,x4, x1
sub x4,x4, x1
bl posicion 
bl cuadradito

add x3, x3,x1
add x4, x4, x1
bl posicion 
bl cuadradito

sub x4,x4,x1
bl posicion 
bl cuadradito   

add x3,x3,x1
bl posicion 
bl cuadradito   

add x3,x3,x1
bl posicion 
bl cuadradito   

add x4,x4,x1
bl posicion 
bl cuadradito

add x4,x4,x1
bl posicion
bl cuadradito

sub x3, x3, 40 
add x4, x4, 20

ldr x30,[sp,#0]
add sp,sp, #8
ret
///////////////////////////////////////////////////////////////////////////
LetraT2:
	sub sp,sp, #8  			
    str x30,[sp,#0]  		

	movz x6, 0xca, lsl 16		//color oscuro   CAB100
	movk x6, 0xb100, lsl 00 	//color oscuro
	movz x5, 0xf3, lsl 16   	//color claro  F3D600
	movk x5, 0xd600, lsl 00		//color claro

bl posicion
BL cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion
bl cuadradito

add x3, x3,x1
sub x4,x4, x1
bl posicion 
bl cuadradito

add x3, x3,x1
bl posicion 
bl cuadradito

add x3,x3,x1
bl posicion 
bl cuadradito   

add x3,x3,x1
bl posicion 
bl cuadradito   

sub x3, x3, 40
add x4, x4, 30

ldr x30,[sp,#0]  
add sp,sp, #8  
ret
//////////////////////////////////////////////////////////////////////////

LetraR:
	sub sp,sp, #8  	
    str x30,[sp,#0]  

	movz x6, 0x6f, lsl 16		//color oscuro   6FA700
	movk x6, 0xa700, lsl 00 	//color oscuro
	movz x5, 0x8d, lsl 16   	//color claro  8DD300
	movk x5, 0xd300, lsl 00		//color claro

bl posicion
BL cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
add x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
sub x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
add x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

sub x4,x4,x1
sub x4,x4,x1
bl posicion 
bl cuadradito   

sub x3,x3,x1
bl posicion 
bl cuadradito   

sub x3, x3,x1
bl posicion 
bl cuadradito

sub x3, x3,x1
bl posicion 
bl cuadradito

sub x3, x3, x1
bl posicion
bl cuadradito

add x4, x4, 40
	ldr x30,[sp,#0] 
    add sp,sp, #8  	
ret
/////////////////////////////////////////////////////////////////////////////////////////
LetraI:
	sub sp,sp, #8  		
    str x30,[sp,#0]  

	movz x6, 0xc3e1, lsl 00 	//color oscuro  00C3E1
	movz x5, 0x96ad, lsl 00 	//color claro	0096AD

bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

sub x4, x4, x1
add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
sub x4, x4, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

sub x3, x3, 40
add x4, x4, 30

	ldr x30,[sp,#0]
    add sp,sp, #8  
ret
//////////////////////////////////////////////////////////////////////////////////////////////////
LetraS:
	sub sp,sp, #8  
    str x30,[sp,#0] 

	movz x6, 0x5b, lsl 16		//color oscuro   5B00AB
	movk x6, 0x00ab, lsl 00 	//color oscuro
	movz x5, 0x85, lsl 16   	//color claro  8500FA
	movk x5, 0x00fa, lsl 00		//color claro

bl posicion
BL cuadradito

add x4,x4, x1
bl posicion
BL cuadradito

add x3, x3, x1
sub x4,x4, x1
sub x4,x4, x1

bl posicion 
bl cuadradito

add x3, x3, x1
add x4, x4, x1

bl posicion 
bl cuadradito

add x3, x3, x1
add x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
sub x4,x4, x1
sub x4,x4, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

sub x3,x3, 40

ldr x30,[sp,#0]  
add sp,sp, #8  
ret
////////////////////////////////////////////////////BLOQUES//////////////////////////////////////////////////
Tblock:
	sub sp,sp, #32  			
	str x3, [sp,#24]
	str x4, [sp,#16]
	str x1, [sp, #8]
    str x30,[sp,#0]  			

	movz x5, 0x33a0, lsl 00   	//color oscuro  8933A0
	movk x5, 0x89, lsl 16 		//color oscuro	
	movz x6, 0x40ff, lsl 00 	//color claro	D740FF
	movk x6, 0xd7, lsl 16 		//color claro	

bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

sub x4, x4, x1
add x3, x3, x1
bl posicion 
bl cuadradito

sub x3, x3, x1

	ldr x30,[sp,#0]
	ldr x1, [sp, #8]
	ldr x4, [sp,#16]
	ldr x3, [sp,#24]
    add sp,sp, #32

ret
////////////////////////////////////////////////////////////////////////////////////////////////
Oblock:
 	sub sp,sp, #32  
    str x30,[sp,#0]  		
	str x1,[sp,#8]
	str x4,[sp,#16]
	str x3,[sp,#24]

	movz x5, 0xca, lsl 16		//color oscuro   CAB100
	movk x5, 0xb100, lsl 00 	//color oscuro
	movz x6, 0xf3, lsl 16   	//color claro  F3D600
	movk x6, 0xd600, lsl 00		//color claro
	
bl posicion
BL cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

sub x4, x4, x1
bl posicion 
bl cuadradito

sub x4, x4, 20
sub x3, x3, 10 

	ldr x3,[sp,#24]
	ldr x4,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0] 
    add sp,sp, #32 

ret
////////////////////////////////////////////////////////////////////////////////////////////////////

Sblock:
	sub sp,sp, #8  			
    str x30,[sp,#0]  		

	movz x5, 0x6f, lsl 16	//color oscuro   6FA700
	movk x5, 0xa700, lsl 00 //color oscuro
	movz x6, 0x8d, lsl 16   //color claro  8DD300
	movk x6, 0xd300, lsl 00		//color claro

bl posicion
BL cuadradito

add x4,x4, x1
bl posicion
BL cuadradito

add x3, x3, x1
sub x4,x4, x1
sub x4,x4, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

	ldr x30,[sp,#0]  
    add sp,sp, #8  
ret
////////////////////////////////////////////////////////////////////////////////////////////////

Zblock:
	sub sp,sp, #32
    str x30,[sp,#0]
	str x1,[sp,#8]
	str x4,[sp,#16]
	str x3,[sp,#24]
	
movz x5, 0x1F00, lsl 00		//color claro 	F22B00 
movk x5, 0xAF, lsl 16 
movz x6, 0xD6, lsl 16		// color oscuro

bl posicion
BL cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

sub x4, x4, 30
sub x3, x3, 10 

	ldr x3,[sp,#24]
	ldr x4,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0]  
    add sp,sp, #32 
ret
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
Iblock:
	sub sp,sp, #8 
    str x30,[sp,#0] 

	movz x6, 0xc3e1, lsl 00   	//color oscuro  00C3E1
	movz x5, 0x96ad, lsl 00 	//color claro	0096AD

bl posicion
BL cuadradito

add x3, x3, x1
bl posicion
BL cuadradito

add x3, x3, x1
bl posicion
BL cuadradito

add x3, x3, x1
bl posicion
BL cuadradito

sub x3, x3, 40

	ldr x30,[sp,#0]
    add sp,sp, #8
ret 
////////////////////////////////////////////////////////////////////////////////////////////
Jblock:
	sub sp,sp, #24 
    str x30,[sp,#0] 
	str x4,[sp,#8]
	str x3,[sp,#16]

	movz x5, 0x5b, lsl 16		//color oscuro   5B00AB
	movk x5, 0x00ab, lsl 00 	//color oscuro
	movz x6, 0x85, lsl 16   	//color claro  8500FA
	movk x6, 0x00fa, lsl 00		//color claro

bl posicion
BL cuadradito

add x3, x3, x1
bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

	ldr x3,[sp,#16]
	ldr x4,[sp,#8]
	ldr x30,[sp,#0]
    add sp,sp, #24 

ret
///////////////////////////////////////////////////////////////////////////////////////////////
Lblock:
 	sub sp,sp, #32 
    str x30,[sp,#0]
	str x1,[sp,#8]
	str x4,[sp,#16]
	str x3,[sp,#24]

	movz x6, 0xf3, lsl 16		//color oscuro   F35D00
	movk x6, 0x5d00, lsl 00 	//color oscuro
	movz x5, 0xc2, lsl 16   	//color claro  C24A00
	movk x5, 0x4a00, lsl 00		//color claro

add x3, x3, x1
bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

sub x3,x3,x1

bl posicion
BL cuadradito

 	ldr x3,[sp,#24]
	ldr x4,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0]
    add sp,sp, #32 

ret
/////////////////////////////////////////////////////////////////////////////////////////////
bloquesInitColor:
	sub sp,sp, #8  
    str x30,[sp,#0]

mov x1, 20	     		//seteo tamanio   (alto)
mov x3, 303				//EJE Y
mov x4, 357				//EJE X
bl Sblock
	
mov x3, 303				
mov x4, 378				
bl Lblock
	
mov x3, 283				
mov x4, 220				
bl Tblock

mov x3, 263			
mov x4, 300			
bl Iblock

mov x3, 303			
mov x4, 199			
bl Oblock 

	ldr x30,[sp,#0]
    add sp,sp, #8  
ret
/////////////////////////////////////////////////////////////////////////////////////////////
bloquesInitBlanco:
	sub sp,sp, #8  
    str x30,[sp,#0] 
	mov x1, 20	      		//seteo tamanio   (alto)

	movz x5, 0xff, lsl 16
	movk x5, 0xffff, lsl 00
	
	movz x6, 0xdf, lsl 16
	movk x6, 0xdfdf, lsl 00

mov x3, 303				//EJE Y
mov x4, 357				//EJE X
bl Sblock

mov x3, 303				
mov x4, 378				
bl Lblock

mov x3, 283				
mov x4, 220				
bl Tblock

mov x3, 263				
mov x4, 300				
bl Iblock

mov x3, 303				
mov x4, 199				
bl Oblock 

	ldr x30,[sp,#0]
    add sp,sp, #8
ret
/////////////////////////////////////////////////////////////////////////////////////////////////////////
Botones:	
	sub sp,sp, #8
    str x30,[sp,#0]

mov x1, 18	      		//seteo tamanio   (alto)
mov x3, 434				//EJE Y
mov x4, 320				//EJE X
bl trianguloInvertido

mov x1, 18	      		
mov x3, 356				
mov x4, 320				
bl trianguloNormal

mov x1, 18	      		
mov x3, 395				
mov x4, 360				
bl trianguloDerecho
	
mov x1, 18	      		
mov x3, 395				
mov x4, 280				
bl trianguloIzquierdo

	ldr x30,[sp,#0]
    add sp,sp, #8  

ret
/////////////////////////////////////////////////////////////////////////////////////////////
Delay:
sub sp,sp,8
str x10,[sp,#0]

stay11:
	sub x10, x10, 1
	cbnz x10, stay11
ldr x10, [sp,#0]
add sp,sp ,8
ret
/////////////////////////////////////////////////////////////////////////////////////////////
fondolimpio:
	sub sp,sp, #32 
    str x30,[sp,#0]
	str x1, [sp,#8]
	str x4, [sp,#16]
	str x3, [sp,#24]

mov x1, 267	      		//seteo tamanio   (alto)
mov x2, 240				// seteo tamanio  (largo)
movz x5, 0xff, lsl 16	//color 
mov x3, 79 				//EJE Y
movz x4, 200			//EJE X
movz x5, 0xff, lsl 0
bl posicion
bl RectanguloDegrade

	ldr x3, [sp,#24]
	ldr x4, [sp,#16]
	ldr x1, [sp, #8]
	ldr x30,[sp,#0]
    add sp,sp, #32 

ret
/////////////////////////////////////////////////////////////////////////////////////////////
bloque1:
	sub sp, sp, 32
	str  x30, [sp, #0]
	str  x1, [sp, #8]
	str  x3, [sp, #16]
	str  x4, [sp, #24]

mov x3, 303
mov x4, 280

bl posicion
bl Tblock

	ldr x4,[sp,#24]
	ldr x3,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0]
    add sp,sp, 32  
ret
/////////////////////////////////////////////////////////////////////////////////////////////
bloque2:
 	sub sp,sp, #32 
    str x30,[sp,#0]
	str x1,[sp,#8]
	str x4,[sp,#16]
	str x3,[sp,#24]

mov x3, 242
mov x4, 280
 
bl posicion
bl Jblockright
 
	ldr x3,[sp,#24]
	ldr x4,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0]
	add sp,sp, #32 
ret
/////////////////////////////////////////////////////////////////////////////////////////////
bloque3: 
 	sub sp,sp, #32 
    str x30,[sp,#0]
	str x1,[sp,#8]
	str x4,[sp,#16]
	str x3,[sp,#24]
 
mov x3, 221
mov x4, 301
 
bl posicion
bl Zblock

 	ldr x3,[sp,#24]
	ldr x4,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0]

ret
/////////////////////////////////////////////////////////////////////////////////////////////
bloque4:
 	sub sp,sp, #32 
    str x30,[sp,#0]
	str x1,[sp,#8]
	str x4,[sp,#16]
	str x3,[sp,#24]

mov x3, 180
mov x4, 280
 
bl posicion
bl Oblock

 	ldr x3,[sp,#24]
	ldr x4,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0]
    add sp,sp, #32 

ret
/////////////////////////////////////////////////////////////////////////////////////////////
bloque5:
 	sub sp,sp, #32 
    str x30,[sp,#0]
	str x1,[sp,#8]
	str x4,[sp,#16]
	str x3,[sp,#24]

mov x3, 99
mov x4, 280

bl posicion
bl Lblockleft

 	ldr x3,[sp,#24]
	ldr x4,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0]
    add sp,sp, #32 

ret 
/////////////////////////////////////////////////////////////////////////////////////////////
Jblockright:
	sub sp, sp, 32 
	str x30, [sp,#0]
	str x1, [sp,#8]
	str x4, [sp,#16]
	str x3, [sp,#24]

	movz x5, 0x5b, lsl 16		//color oscuro   5B00AB
	movk x5, 0x00ab, lsl 00 	//color oscuro
	movz x6, 0x85, lsl 16   	//color claro  8500FA
	movk x6, 0x00fa, lsl 00		//color claro

bl posicion
BL cuadradito

add x3, x3, x1
bl posicion
BL cuadradito

add x3, x3, x1
bl posicion
BL cuadradito

sub x3, x3, x1
sub x3, x3, x1
add x4, x4, x1
bl posicion
BL cuadradito

	ldr x3, [sp,#24]
	ldr x4, [sp,#16]
	ldr x1, [sp,#8]
	ldr x30, [sp,#0]
	add sp, sp, 32

ret
/////////////////////////////////////////////////////////////////////////////////////////////
Lblockleft:
 	sub sp,sp, #32  			// Reserve space for two registers
    str x30,[sp,#0]  			// Store Register X30 in stack
	str x1,[sp,#8]
	str x4,[sp,#16]
	str x3,[sp,#24]
 
   movz x6, 0xf3, lsl 16   		//color oscuro   F35D00
   movk x6, 0x5d00, lsl 00 		//color oscuro
   movz x5, 0xc2, lsl 16   		//color claro  C24A00
   movk x5, 0x4a00, lsl 00     	//color claro
 
add x3, x3, x1
bl posicion
BL cuadradito
 
add x3, x3, x1
bl posicion
BL cuadradito
 
add x3, X3, x1
bl posicion
BL cuadradito
 
add x4, x4,x1
bl posicion
BL cuadradito
 
 	ldr x3,[sp,#24]
	ldr x4,[sp,#16]
	ldr x1,[sp,#8]
	ldr x30,[sp,#0]
    add sp,sp, #32 
ret
/////////////////////////////////////////////////////////////////////////////////////////////
BotonArriba:
	sub sp, sp, 32
	str x1, [sp,#24]
	str x3, [sp,#16]
	str X4, [sp,#8]
	str x30, [sp,#0]

mov x1, 18	      		//seteo tamanio   (alto)
mov x3, 356				//EJE Y
mov x4, 320				//EJE X
bl trianguloNormal
	
	ldr x30, [sp,#0]
	ldr X4, [sp,#8]
	ldr x3, [sp,#16]
	ldr x1, [sp,#24]
	add sp, sp, 32
ret
/////////////////////////////////////////////////////////////////////////////////////////////
 BotonDerecho:
   sub sp, sp, 32
   str x1, [sp,#24]
   str x3, [sp,#16]
   str X4, [sp,#8]
   str x30, [sp,#0]
 
mov x1, 18        		//seteo tamanio   (alto)
mov x3, 395             	//EJE Y
mov x4, 360     			//EJE X
bl trianguloDerecho
  
   ldr x30, [sp,#0]
   ldr X4, [sp,#8]
   ldr x3, [sp,#16]
   ldr x1, [sp,#24]
   add sp, sp, 32
ret
//////////////////////////////////////////////////////////////////////////////////////////////////
GAMEOVER:
	sub sp, sp, #8
	str x30, [sp, #0]

mov x1, 18				//Tamaño
//letrag
mov x3, 185				//posiciones iniciales de la primera letra
mov x4,15

movz x5, 0x0, lsl 0
movz x6,0xaa,  lsl 16

bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

add x4, x4, x1
bl posicion
BL cuadradito

sub x4, x4, x1
sub x4, x4, x1
add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

add x4, x4, x1
bl posicion 
bl cuadradito

sub x3, x3, x1
bl posicion 
bl cuadradito

sub x3, x3, x1
bl posicion 
bl cuadradito

sub x4, x4, x1
bl posicion 
bl cuadradito

//LETRA A
add x4,x4,x1
add x4,x4,x1
add x4,x4,x1
bl posicion 
bl cuadradito

add x3,x3,x1
bl posicion 
bl cuadradito

add x3,x3,x1
bl posicion 
bl cuadradito

add x4, x4, x1
add x4, x4, x1
bl posicion 
bl cuadradito
sub x3, x3, x1
bl posicion 
bl cuadradito 

sub x3, x3, x1
bl posicion 
bl cuadradito 

sub x4, x4, x1
sub x4, x4, x1
sub x3, x3, x1
bl posicion 
bl cuadradito 

add x3,x3,x1
add x4,x4,x1
bl posicion 
bl cuadradito 

sub x3,x3,x1
sub x3,x3,x1
bl posicion 
bl cuadradito 

add x3, x3, x1
add x4, x4, x1
bl posicion 
bl cuadradito 

 //letra M
add x4, x4, x1
add x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

sub x3,x3,x1
sub x3,x3,x1
sub x3,x3,x1
sub x3,x3,x1
bl posicion 
bl cuadradito

add x3,x3,x1
add x4, x4, x1
bl posicion 
bl cuadradito

add x3,x3,x1
add x4, x4, x1
bl posicion 
bl cuadradito

sub x3,x3,x1
add x4, x4, x1
bl posicion 
bl cuadradito

sub x3,x3,x1
add x4, x4, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

add x3, x3, x1
bl posicion 
bl cuadradito

//letra E
add x4,x4,x1
add x4,x4,x1
bl posicion 
bl cuadradito

add x4,x4,x1
bl posicion 
bl cuadradito

add x4,x4,x1
bl posicion 
bl cuadradito

sub x4,x4,x1
sub x3,x3,x1
sub x3,x3,x1
bl posicion 
bl cuadradito

sub x4,x4,x1
bl posicion 
bl cuadradito

add x3,x3,x1
bl posicion 
bl cuadradito

sub x3,x3,x1
sub x3,x3,x1
bl posicion 
bl cuadradito

sub x3,x3,x1
bl posicion 
bl cuadradito

add x4,x4,x1
bl posicion 
bl cuadradito

add x4,x4,x1
bl posicion 
bl cuadradito
 //o
add x4,x4,x1
add x4,x4,x1
add x4,x4,x1
add X3, X3, X1
bl posicion 
bl cuadradito

add X3, X3, X1
bl posicion 
bl cuadradito

add X3, X3, X1
bl posicion 
bl cuadradito

add x4, x4, x1
add X3, X3, X1
bl posicion 
bl cuadradito

add x4, x4, x1
sub X3, X3, X1
bl posicion 
bl cuadradito

sub X3, X3, X1
bl posicion 
bl cuadradito

sub X3, X3, X1
bl posicion 
bl cuadradito

sub x4, x4, x1
sub X3, X3, X1
bl posicion 
bl cuadradito 

//v
add x4, x4, x1
add x4, x4, x1
add x4, x4, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
add x4, x4, x1
bl posicion 
bl cuadradito

sub x3, x3, x1
add x4, x4, x1
bl posicion 
bl cuadradito 

sub x3, x3, x1
bl posicion 
bl cuadradito 

sub x3, x3, x1
bl posicion 
bl cuadradito 

sub x3, x3, x1
bl posicion 
bl cuadradito 

//E
add x4, x4, x1
add x4, x4, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
sub x4, x4, x1
sub x4, x4, x1
bl posicion 
bl cuadradito 

sub x3, x3, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
add x3, x3, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
sub x4, x4, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
bl posicion 
bl cuadradito 

//r
add x4, x4, x1
add x4, x4, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
add x4, x4, x1
bl posicion 
bl cuadradito 

sub x4, x4, x1
sub x4, x4, x1
sub x3, x3, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
add x4, x4, x1
bl posicion 
bl cuadradito 

sub x4, x4, x1
sub x4, x4, x1
sub x3, x3, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
bl posicion 
bl cuadradito 

add x4, x4, x1
sub x3, x3, x1
bl posicion 
bl cuadradito 

sub x4, x4, x1
sub x3, x3, x1
bl posicion 
bl cuadradito 

sub x4, x4, x1
bl posicion 
bl cuadradito 

add x3, x3, x1
bl posicion 
bl cuadradito 

	ldr x30,[sp,#0]
	add sp,sp, #8  
ret
///////////////////////////////////////////////////////////////////////
Fin:
mov x14, SCREEN_HEIGH 		//salvo en x14 el alto 
lsr x14, x14, 1 			//divido en 2 
movz x5, 0xff, lsl 16
movz x10,0x4f, lsl 16
mov x3,479
mov x4,1
bl posicion

mov x7,x20
mov x2,SCREEN_WIDTH

siguienteIter:
	mov x15, x2        		//salvo en x15 el largo
	add x5, x5, 1
rayaInfSup:
	stur w5,[x0]	   		// Seteo el color del pixel N
	add x0,x0,4	   			// proximo pixel

	stur w5,[x7]	   		// Seteo el color del pixel N
	add x7,x7,4	   			// proximo pixel

	sub x15,x15,1	   		// decrement X counter
	cbnz x15, rayaInfSup 	//si no termine de pintar la primera raya pinto el proximo pixel 

	sub x14, x14, 1 		//decrement y counter 
	msub x7, x19, x2, x7    //vuelvo al principio de la linea x0 - x2 * 4	= x0	
	madd x7, x21, x19, x7 	//muevo el puntero al inicio de la proxima linea (640*4+x0)=x0

	sub x3,x3,1
	bl posicion

	bl Delay
	cbnz x14, siguienteIter
	
movz x10,0xfff, lsl 16
mov x9, 2

finalisimo:
	bl Delay
	bl GAMEOVER
	bl Delay
	mov x1, SCREEN_HEIGH	//seteo tamanio   (alto)
	mov x2, SCREEN_WIDTH	// seteo tamanio  (largo) 
	mov x3, 0				//EJE Y
	mov x4, 0				//EJE X
	movz x5, 0xff, lsl 16
	bl posicion
	bl RectanguloDegrade

	bl Delay
	bl GAMEOVER
	sub x9,x9,1
	cbnz x9, finalisimo

b infloop

end:
