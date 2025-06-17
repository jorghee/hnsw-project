# <samp>1. Hierarchical Navigable Small World (HNSW) algorithm<samp>
Es una estructura de datos diseñada para resolver el problema de búsqueda de 
vecinos más cercanos (K-Nearest Neighbors, KNN) en espacios vectoriales de 
alta dimensión. A diferencia del KNN clásico que compara exhaustivamente el 
punto de consulta con todo el dataset (con una complejidad de O(n)), HNSW 
permite realizar búsquedas aproximadas con una eficiencia significativamente 
mayor.

![Figura 1. Algoritmo k-Nearest Neighbors (kNN)](https://assets.zilliz.com/The_k_NN_algorithm_workflow_dffbf07072.png)

La base teórica de HNSW se inspira en los Small World Graphs (Watts & Strogatz, 
1998), donde los nodos de un grafo están conectados de manera que se puedan 
alcanzar en muy pocos pasos, aunque el grafo sea grande. En el contexto de HNSW, 
cada punto del dataset es un nodo, y los bordes representan relaciones de vecindad 
basadas en alguna medida de similitud o distancia.

# <samp>2. Skip List y grafos Navigable Small World (NSW) como fundamentos</samp>
Una Skip List es una estructura de datos probabilística que consta de varias capas 
de listas enlazadas, en las que cuanto más alta es la capa, más elementos de la 
lista se omiten. Como se puede ver en la siguiente visualización, la capa más baja 
contiene todos los elementos de una lista enlazada. A medida que avanzamos hacia las 
capas superiores, las listas enlazadas se saltan progresivamente cada vez más 
elementos, lo que da lugar a listas con menos elementos.

![Figura 2. Flujo de trabajo de Skip List](https://assets.zilliz.com/Skip_list_workflow_to_find_a_particular_element_a073ebd4b2.png)

En pocas palabras, un grafo NSW se construye barajando aleatoriamente una colección 
de puntos de datos y luego insertándolos uno a uno. Después de cada inserción, 
cada punto de datos se conecta a sus vecinos más cercanos a través de un número 
predefinido de aristas (M). Cuando cada punto está conectado a sus vecinos más 
cercanos, se crea un fenómeno de “mundo pequeño”, en el que dos puntos cualesquiera 
pueden recorrerse con caminos relativamente cortos.

![Figura 3. Grafo NSW](https://assets.zilliz.com/NSW_graph_creation_process_e70f9775ef.png)

# <samp>3. El concepto de HNSW</samp>

HNSW construye un grafo jerárquico con múltiples niveles. Cada nivel contiene un 
subconjunto de los puntos (vectores) del dataset, donde los niveles superiores 
tienen menos puntos pero permiten una navegación más eficiente. El proceso se 
puede resumir en los siguientes pasos:

1. **Inserción**: Cada nuevo vector se inserta comenzando por el nivel superior del 
grafo, buscando su ubicación ideal mediante navegación basada en la similitud. 
Luego se conecta con sus vecinos más cercanos en niveles progresivamente más 
bajos hasta llegar al nivel base.

2. **Búsqueda**: Para encontrar los K vecinos más cercanos a un punto dado, el 
algoritmo comienza la navegación en el nivel más alto, eligiendo iterativamente el 
vecino más cercano, y va descendiendo de nivel refinando la búsqueda hasta alcanzar 
el nivel base, donde se obtienen los vecinos finales.

Esta estructura permite búsquedas rápidas con precisión ajustable, y ha demostrado 
ser una de las más eficientes y precisas en entornos de alta dimensión, según 
benchmarks realizados en bibliotecas como FAISS (Facebook AI Research, 2023) y 
NMSLIB.

Durante el proceso de creación del grado, HNSW comienza asignando un número 
aleatorio de 0 a l a cada elemento, donde l es la capa máxima en la que puede 
estar presente un elemento en un gráfico multicapa. Si un elemento tiene l igual 
a 2 y el número total de capas es 4, este elemento estará presente desde la capa 
0 hasta la capa 2, pero no en la capa 3.

![Figura 4. Búsqueda de vector usando Hierarchical Navigable Small World](https://assets.zilliz.com/Vector_search_using_HNSW_algorithm_7fe2587026.png)

Durante el proceso de búsqueda vectorial, el algoritmo HNSW selecciona primero un 
punto de entrada, que debe ser el elemento presente en la capa más alta. A 
continuación, se elige el vecino más próximo del punto de entrada y se comprueba 
si este vecino más próximo nos acerca al punto de consulta. En caso afirmativo, y 
si ningún otro elemento de la capa superior está más cerca del punto de consulta, 
se continúa con el mismo procedimiento de búsqueda en la capa inferior.

# <samp>References</samp>
Watts, D. J., & Strogatz, S. H. (1998). Collective dynamics of 'small-world' 
networks. Nature, 393(6684), 440–442. https://doi.org/10.1038/30918

Facebook AI Research. (2023). FAISS: A library for efficient similarity search 
and clustering of dense vectors. https://github.com/facebookresearch/faiss
