

Lista de verificación personal:
- @= && no more ideas ? stop : stop within @<-20
- Conoce tus MODs
- Entender un problema correctamente y rápidamente es tan importante como resolverlo, por el amor de Dios
- No te limites a una estrategia para ningún problema (especialmente los fáciles, solo por serlo)
  - No pierdas tiempo extra buscando soluciones elegantes en A, ya que muchas As tienen restricciones muy laxas que permiten fuerza bruta
- No te limites a una interpretación de ningún problema (especialmente si tienes un sesgo previo fuerte sobre la configuración/contexto del problema)
- ¿Atascado? Deducción de patrones mediante la exploración de casos de prueba difíciles existentes seleccionados (piensa en exploración eps-greedy)
  - No te centres solo en los casos de prueba fáciles; no aportan mucha información
- ¿WA en la prueba >1 (es decir, casos límite)? Empieza a validar tu propia solución con tu propio caso de prueba antes del primer envío (especialmente si es más fácil de verificar).

Un análisis retrospectivo sobre la pobre tasa efectiva de resolución en C (4/16/26):

Objetivo:
* Resolver ABC lo más rápido posible para permitir tiempo para resolver D en el futuro (con la clasificación actual devaluada para no tramposos, debería dar Especialista)
* Y llegar a esa posición lo antes posible (<1 mes. / esto va a tener mucho efecto contrario)

Problema:
* A simple vista, parece que la tasa de resolución de C varía del 80% al 50% en una ventana de 7 días (recientemente me he topado con un montón de Cs que son >1400 :shock:)
* Incluso si son <=1400, la tasa de resolución no es buena
* Han pasado 1.5 meses y sigo estancado en C => no parece que lo que estoy haciendo actualmente vaya a cambiar la trayectoria
* Cronometrar C restringe cuándo puedo hacer C mientras la tasa de resolución es terrible (hacer C sin cronómetro y centrarse en la tasa de resolución de C)

Análisis:
| Problema (Del más antiguo al más reciente)                     | Clasificación | Etiquetas                | Estado del envío     | Insightes clave                                                                                                                                                                                                                                 |
| -------------------------------------------------------------- | ------------- | ------------------------ | -------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| https://codeforces.com/contest/2202/problem/C1 | 1300   | DS,DSU,G            | Revisado editorial     | Invariancia perdida: el máximo del subsegmento anterior no importa (más restrictivo)                                                                                                                                                                |
| https://codeforces.com/contest/2192/problem/C  | 1300   | BS,G,M              | Revisado editorial     | Observación perdida: verificación lineal **sobre la respuesta** y encontrar el menor *i* que satisfaga para la resp. ópt.                                                                                                                                       |
| https://codeforces.com/contest/2205/problem/C  | 1500   | G,S                 | Resuelto (memorable)    | Elegancia clave: si mal no recuerdo, inviertes el vll general en términos del componente más pequeño (blogs) luego ordenas dentro de cada comp. y deduplicas después de la primera/antes de la última ocurrencia.                                                                                     |
| https://codeforces.com/contest/2203/problem/C  | 1500   | BS,BitM,G,M         | Revisado editorial     | Observación perdida: búsqueda binaria **sobre la respuesta** (longitud mín. *n*); Idea general: dado *n*, ¿puedes aplanar el máximo dentro de *n* y es válido?                                                                                            |
| https://codeforces.com/contest/2197/problem/C  | 1200   | games,G,M           | Revisado editorial     | Obs. perdida: puedes *min* sobre dos/múltiples factores; Obs. encontrada: la comparación funciona en algún factor intrínseco separado de 2,3                                                                                                                  |
| https://codeforces.com/contest/2194/problem/C  | 1300   | BitM,BF,DP,M,NumT   | Resuelto                | Obs. perdida: solo verificamos sobre divisores enteros de *n* y 26 letras (en lugar de conjuntos dinámicos); Obs. encontrada: usé conjuntos a lo largo de tiras en el mismo idx.                                                                                  |
| https://codeforces.com/contest/2207/problem/C  | 1600   | DS,D&Q,DP,M         | Upsolved (memorable)  | Obs. clave: divide el problema en piezas fundamentales individuales y usa estas piezas pequeñas para encontrar la respuesta final con algún método indirecto (es decir, sustraer la intersección); Obs. no usada: D&Q en máx (confundido con múltiples de los mismos máximos) |
| https://codeforces.com/contest/2189/problem/C1 | 1300   | BitM,C,M            | Revisado editorial     | Obs. perdida: si la Pregunta pide *existe*, podemos, por construcción, encontrar un caso simplificado (si es posible); Obs. encontrada: reformulando expr. condicional                                                                                   |
| https://codeforces.com/contest/2183/problem/C  | 1500   | BS,G,M,2Ptr         | Revisado editorial     | Obs. clave: dos punteros **sobre la respuesta** con restricciones variables y con alguna prueba de greedy para transferir el espacio de respuesta al espacio de restricciones                                                                                                   |
| https://codeforces.com/contest/2178/problem/C  | 1200   | DP,G,Impl           | Revisado editorial     | Obs. perdida: una decisión ahora prepara una decisión para el futuro (es decir, retrasada; elem. pos. prev. está vinculado al elem. pos. actual; toma un positivo de un elem. previo cuando encuentras un nuevo elem. positivo) => abstraído para simplificar el problema             |
| https://codeforces.com/contest/2176/problem/C  | 1300   | G,S                 | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2173/problem/C  | 1400   | BF,C,G,NumT         | Revisado editorial (?) | Malentendido                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2170/problem/C  | 1300   | BS,G,2Ptr           | Resuelto                | La visualización con casos complejos ayudó (es decir, r-cone)                                                                                                                                                                                       |
| https://codeforces.com/contest/2208/problem/C  | 1300   | DP,G,M              | Resuelto (memorable)    | Obs. clave: la decisión depende del futuro donde afecta la fracción hacia atrás; Primera "DP" indirecta hacia atrás resuelta                                                                                                                       |
| https://codeforces.com/contest/1760/problem/C  | 800    | DS,Impl,S           | --                    | ????                                                                                                                                                                                                                                         |
| https://codeforces.com/contest/2204/problem/C  | 1000   | M,NumT              | Revisado editorial     | Ciclos LCM!                                                                                                                                                                                                                                  |
| https://codeforces.com/contest/2163/problem/C  | 1500   | BF,Comb,DP,M,2Ptr   | Revisado editorial     | Atascado: contar intervalos válidos únicos; Obs. encontrada: DPs de intervalos bidireccionales y encontrar linealmente el subconjunto de intervalo válido; Obs. perdida: ordenar por L luego R y encontrar **mín. derecha por extremo izquierdo** (DP indirecta extraña)                  |
| https://codeforces.com/contest/2161/problem/C  | 1200   | C,G,S,2Ptr          | Resuelto                | Invariancia clave: siempre llegamos a los mismos "niveles", pero reorganizar elementos nos permite maximizar                                                                                                                                           |
| https://codeforces.com/contest/2154/problem/C1 | 1400   | G,Impl,M,NumT       | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2153/problem/C  | 1500   | C,Geom,G,Impl,S     | Resuelto                | Probé casos límite sin mirar el caso de prueba #2                                                                                                                                                                                            |
| https://codeforces.com/contest/2155/problem/C  | 1500   | BF,G,Impl           | **Saltado**           | (necesita ser revisado)                                                                                                                                                                                                                        |
| https://codeforces.com/contest/2151/problem/C  | 1400   | G,Impl,M            | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2144/problem/C  | 1300   | Comb,DP,M           | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2139/problem/C  | 1100   | BitM,C,G            | Revisado editorial     | Obs. perdida: "backtracking", ya sabemos cuál es el resultado final pero queremos las ops. el camino para llegar; podemos encontrar invariancia si miramos desde el final al comienzo                                                              |
| https://codeforces.com/contest/2134/problem/C  | 1200   | BF,G,Impl           | Revisado editorial     | No te centres en fórmulas analíticas elegantes; Obs. perdida: cuando una decisión local afecta dominó/cascadas globalmente, entiende qué decisión local única optimiza mejor el problema global en mano                                            |
| https://codeforces.com/contest/2127/problem/C  | 1400   | games,G,S           | Revisado editorial     |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2211/problem/C1 | 1300   | BS,BF,G,2Ptr        | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2210/problem/C1 | 1200   | G,NumT              | Revisado editorial     | Malentendido; lcm(gcd,gcd)                                                                                                                                                                                                                |
| https://codeforces.com/contest/2128/problem/C  | 1200   | G,M                 | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2122/problem/C  | 1700   | C, Geom, G, M, S    | Revisado editorial     | Obs. elegante: particiona los puntos en cuadrantes y empareja desde ambas mitades                                                                                                                                                             |
| https://codeforces.com/contest/2119/problem/C  | 1300   | BitM, C, M          | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2120/problem/C  | 1400   | C, G, M, S, trees   | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2118/problem/C  | 1300   | BitM, DS, G, M      | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2109/problem/C1 | 1500   | BitM, C, I, M, NumT | Revisado editorial     | Obs. perdida: *x* es como máximo 16 después de aplicar `digit` dos veces, a veces no tienes que preocuparte por las cosas pequeñas, a veces sí, como aquí al encontrar el rango final de valores de *x*                                               |
| https://codeforces.com/contest/2107/problem/C  | 1500   | BS, C, DP, Impl, M  | Revisado editorial     | Obs. perdida: máx DP @i puede pensarse como mantener la acumulación anterior (crecer la suma del subarray) o reiniciar de nuevo (nueva suma del subarray)                                                                                                        |
| https://codeforces.com/contest/2104/problem/C  | 1100   | BF, C, games, G, M  | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2103/problem/C  | 1600   | BS,G,Impl,S         | Revisado editorial     | Obs. clave: podemos usar `max` y comparadores como una forma de verificar existencia (y solo nos importa la existencia porque la respuesta solo se preocupa por la existencia)                                                                                          |
| https://codeforces.com/contest/2084/problem/C  | 1400   | C,DS,G,Impl         | Revisado editorial     | Obs. clave: en lugar de intercambiar desde el índice actual, dado el índice actual, intercambia 2 *otros índices de la segunda mitad* (no te centres siempre en el presente)                                                                                         |
| https://codeforces.com/contest/2092/problem/C  | 1200   | C,G,M               | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2085/problem/C  | 1600   | BitM, C, DP, G      | Resuelto                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2078/problem/C  | 1500   | C,G,M,prob,S        | Revisado editorial     | Obs. perdida: automáticamente no pensé en reordenar o revisar profundamente la condición porque pensé que cualquier restricción adicional junto a las restricciones triviales no tenía nada que analizar (similar a malentendido)                            |
| https://codeforces.com/contest/2070/problem/C  | 1500   | BS, G               | Revisado editorial     | Obs. perdida: búsqueda binaria **sobre la respuesta** (y verificar si la respuesta dada satisface la restricción en # de ops.)                                                                                                                          |

| Clasificación | % Resuelto |
| ------------- | ---------- |
| 1000   | 0/1      |
| 1100   | 1/2      |
| 1200   | 3/7      |
| 1300   | 8/11     |
| 1400   | 3/6      |
| 1500   | 2/10     |
| 1600   | 1/3      |
| 1700   | 0/1      |

| Etiqueta            | % Resuelto |
| ------------------- | ---------- |
| G(reedy)       | 15/32    |
| C(onstructive) | 7/16     |
| DS             | 1/4      |
| BS             | 2/8      |
| M(ath)         | 11/23    |
| S(orting)      | 5/10     |
| 2Ptr           | 3/5      |
| BitM           | 4/8      |
| games          | 1/3      |
| NumT           | 2/6      |
| BF             | 3/7      |
| Impl           | 3/10     |
| Comb           | 1/2      |
| Geom           | 1/2      |
| DSU            | --       |
| D&Q            | --       |
| I(nteractive)  | --       |
| trees          | --       |

Posible Solución (además de consejos generalizados en línea):
* Sugerencias de Claude
  * Resolver solo Cs no regresará la tasa de resolución en A,B, pero puede regresar la velocidad A,B, lo cual puede recuperarse rápidamente después de algún calentamiento (¿eso es un alivio?)
  * Mejorar específicamente en búsqueda binaria + implementación (?)
* Análisis
  * Las etiquetas no me dicen nada (equivalente me voy mal en todas las áreas; igualmente soy bueno (?) en todas las áreas)
  * Necesito centrarme en C con >=1500 (y parece ser lo más difícil que llega C)
  * Nota adicional: los únicos 1300 sin resolver son los tres primeros
* Plan:
  * **Simplemente resuelve 2 problemas C de 1400-1700 (Div.2) cada día** *sin cronómetro/flexible* hasta lograr una tasa de resolución efectiva completa

| Problema C 1400-1700 | Resuelto                    | Notas                                                                                                                                                                                                                                               |
| -------------------- | --------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1990C               | ✅                         |                                                                                                                                                                                                                                                     |
| 1993C               | ✅                         |                                                                                                                                                                                                                                                     |
| 1989C               | ✅                         |                                                                                                                                                                                                                                                     |
| 1983C               | ❌                         | problema aburrido con mucha permutación a considerar (aunque podría ser cómo se estila en ICPC).                                                                                                                                                    |
| 1978C               | ❌                         | malentendido la pregunta como maximizar la habilidad del equipo en lugar de seguir su proceso de contratación fijo (hice la pregunta más difícil y aún la resolví; sin resolver)                                                                                            |
| 1974C               | ❌                         | no escribiendo código; div3C; podemos hacer trampa con mapas (incluyendo el conteo de pares) hasheando los tripletes explícitamente y contando adicionalmente cada impacto mientras restamos si es exacto (porque queremos exactamente UN error)                             |
| 2222C               | ❌                         | solución por discord; problema DP muy elegante; idea: dp[i] es la máxima partición válida disponible y hacemos un 2do bucle hacia atrás para calcular dp[j-1]+1 (donde j a i es 1 grupo válido) y verificar contra dp[i] si es mayor o no                |
| 1973C               | ❌                         | alguna visión faltante como si el más grande (n) está en par/impar, entonces ese conjunto de índices debería contener todos los mayores, y sumarlo con la mitad superior de otra permutación garantiza >=n+1 (si asignamos el más pequeño con el más grande)                |
| 1969C               | ❌  (sí soy lwk patético) | (finalmente más exposición a DP) otro problema DP elegante: la idea clave es que el paso inductivo asume que dados d ops, podemos tener todos d+1 elementos adyacentes asignados al mín e iterar d O(k) dentro del marco DP O(nk) resultando O(nk^2)             |
| 1957C               | ❌                         | combinatoriamente: observa que sí nos importa el orden dentro de cada par, pero no nos importa el orden entre otros pares en términos de pares (o por pares); DP-able: obs. clave, podemos emparejar con *cualquier* i-1 filas/cols (invariancia clave) |
| 1956C               | ❌                         | problema *constructivo* de 1600 => simplemente mejora                                                                                                                                                                                                      |

\*: (¿accidentalmente?) revisé etiquetas y clasificaciones (es decir, influyó significativamente en el proceso de resolución de problemas *especialmente al principio*)  
⁑: revisé los casos de prueba ocultos de evaluación (para WA en 2 o más)  
⁂: revisé editorial / sin resolver   
†: WA en 1ro (caso de prueba de muestra)  
‡: WA después del 1ro  
⹋: TLE / MLE  
✥: dormí durante (incluido en el tiempo)  
x: en cola por mucho tiempo  
y: malentendido/malinterpreté el problema  

Historial de resolución rápida (II)
| Competencia | A (=5)      | B (=25)      | C (=60)       |
| ----------- | ----------- | ------------ | ------------- |
| 2122    | -8:29‡‡     | +7:27        | ⁂             |
| 2119    | -26:52‡‡‡   | +0:22‡       | -31:20‡⁑      |
| 2120    | -17:18      | -13:44✥      | +3:58‡        |
| 2118    | -10:47‡     | -12:41††     | -19:18✥       |
| 2116    | <-60:00‡†‡‡ | <-120:00‡‡‡⁑ | ⁂ (<-60:00)   |
| 2109    | -8:03       | <-60:00†‡✥⁑  | ⁂ (<-30:00)   |
| 2107    | -3:13       | -61:20✥‡     | ⁂ (<-20:00)   |
| 2104    | -5:37       | +6:01        | +9:03✥        |
| 2103    | -2:00       | -32:57       | <-60:00       |
| 2084    | -20:39      | -22:05       | ⁂ (<-120:00)  |
| 2092    | --          | +12:30       | +24:29        |
| 2085    | -18:54✥     | -15:28✥††    | +31:53        |
| 2078    | -6:17       | +9:51        | y⁂ (<-120:00) |
| 2070    | -3:44       | -1:30        | y⁂ (<-50:00)  |


Historial de resolución rápida
| Competencia     | A (=5) | B (=25)                              | Notas                                                                                                                                                                                  |
| --------------- | ------ | ------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 2178        | +0:40  | +12:01 (ronda más fácil?)               | *A: (bastante suerte ig?)                                                                                                                                                                  |
| 2176        | +0:49  | -32:38 (malentendido el problema)       |                                                                                                                                                                                        |
| 2173        | +0:07  | -32:40 (después de revisar la editorial)    |                                                                                                                                                                                        |
| 2170        | -7:36  | -11:41                               |                                                                                                                                                                                        |
| 2166        | +2:03  | +7:34 (B 900 / B más fácil)             |                                                                                                                                                                                        |
| 2208 (live) | -26:00 | -50:00                               | muy descuidado; mantén una mente abierta incluso para problemas fáciles                                                                                                                                      |
| 2204 (live) | +2:00  | +21:00                               | *C: conoce los ciclos LCM                                                                                                                                                                |
| 2163        | -1:38  | <0; (revisé editorial)              | Busca los trucos; ni siquiera pierdas un segundo buscando una solución elegante                                                                                                                 |
| 2161        | -37:56 | <0; (B 1200 / más difícil)                | Me limité en la *interpretación* de A (=> nunca limítese en la interpretación y estrategia de ningún problema, esp. cuando tienes un sesgo previo fuerte sobre un contexto/configuración de un problema)     |
| 2154        | -18:07 | -8:59                                | raro error I/O ocurrió en A (accidentalmente escribí el código de A en el código de C1... muy descuidado hoy); súper descuidado hoy por alguna razón?? (greedy sin pruebas cada vez más incómodo :/) |
| 2153        | +0:51  | +10:42                               |                                                                                                                                                                                        |
| 2155        | <-10   | -4:24                                | *A: tomó mucho tiempo en cola, pero nota estas invariancias asap                                                                                                                       |
| 2144        | <-30   | <-30                                 | práctica # teoría.                                                                                                                                                                     |
| 2139        | +2:00  | <-10                                 |                                                                                                                                                                                        |
| 2134        | -0:59  | -19:39 (el problema más hermoso jamás) |                                                                                                                                                                                        |
| 2127        | -23:07 | -38:23                               | A: molesto de implementar; deducción elegante. La validación manual personalizada de casos límite ayudó mucho => necesito hacerlo más a menudo.                                                              |
| 2211 (live) | -1:00  | <-60:00                              |                                                                                                                                                                                        |
| 2210 (live) | -2:00  | -8:00                                |                                                                                                                                                                                        |
| 2128        | -3:42  | -23:06                               |                                                                                                                                                                                        |
