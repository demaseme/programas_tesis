# Generar Thrackles de tamaño _k_.
El programa para generar los thrackles de tamaño k para todos los tipos de orden de n:
`./main n k`.
Genera los siguientes archivos de salida:
- ths/n_k_All.ths - Archivo binario con la información geométrica de los thrackles encontrados.
- ths/n_k_All_bool.ths - Archivo binario con la información lógica de las aristas de los thrackles encontrados.
- K_n_k_statistics.dat - Archivo de texto que especifíca cuántos thrackles se encontraron para cada tipo de orden y si la gráfica completa puede ser cubierta o no por la unión de los thrackles encontrados.

## Estructura de los archivos n_k_All.ths y n_k_All_bool.ths.
La información de los thrackles encontrados para cada n en [3,10] es
almacenada en archivos binarios de nombre n_k_All_bool.ths
donde k es el número de aristas para cada thrackle. El archivo binario
tiene la siguiente estructura:
### ths/n_k_All_bool.ths
Tipo de orden escrito como caracter binario de tipo uint16_t.
  Número de thrackles de tamaño $k$ para determinado tipo de orden
  escrito como caracter binario de tipo uint16_t.
  \item Para cada thrackle, se escribe una lista de (n take 2) caracteres
  binarios que representan cada una de las aristas, si el $j$-ésimo elemento de
  la lista tiene un 0 en el i-ésimo caracter entonces el thrackle j
  tiene la arista i. Cada caracter de la lista está escrito con un caracter
  de tipo char.


La figura binaryfile.png muestra un ejemplo de la sintaxis descrita anteriormente.

  Un segmento de un archivo binario, en este ejemplo n=6 y k=6.
  La primera línea indica que para el tipo de orden 4 existen 3 thrackles
  con 6 aristas. Las siguientes 3 lineas indican las aristas de cada uno
  de los thrackles con un 1. Después, para el tipo de orden 5, existe un
  thrackle, para el tipo de orden 6 no existen thrackles con 6 aristas. El
  archivo binario continua de esta manera para cada uno de los tipos de orden
  para $n=6$. Este ejemplo no representa necesariamente los datos reales
  encontrados en este trabajo para n=6


### ths/n_k_All.ths
Para estos archivos, más grandes en tamaño también se almacenan las coordenadas de las aristas y los puntos de cada thrackle encontrado.
Tamaño del conjunto (uint16_t), Coordenadas xy de los puntos (uint16_t), Número de OT (uint16_t), Tamaño de los thrackles (uint16_t), número de thrackles encontrados (uint16_t), coordenadas xy de cada arista (uint16_t).



# Generar particiones de un entero.
El programa para generar las particiones de un entero dado:
`./integer_partitions n` genera las particiones que cumplen con lo siguiente:
- Los elementos de la particion son igual o menores que _n_.
- La longitud de la partición es menor o igual a n - floor( sqrt( 2*n + (1/2)) - 1/4).
- No existen dos elementos iguales a _n_.
## Compilar:
`make integer_partitions`
# Comprobar descomposición manual.
Este programa tiene escritos procedimientos para verificar descomposiciones de manera manual, basandose en las particiones mencionadas anteriormente.
Carga a memoria todos los thrackles encontrados para todos los ordertypes de las _n_ necesarias. Es decir sí la descomposición es 9+8+7+7+7, se cargan todos los thrackles de todos los OT para _n=9,8,7_

## Compilar:
`make manual_dec`

# Contar repeticiones y verificar si hay descomposición menor a la del caso convexo.
Este programa busca para cada OT si existe o no una descomposición de tamaño menor o igual a la del caso convexo, usando solo
thrackles máximos.
`./m_statistics n`

Genera el archivo de texto **m_nstats.dat** con información acerca de cuáles tipos de orden lograron ser descompuestos de la manera antes mencionada y cuál fue el número de aristas repetidas como máximo.
