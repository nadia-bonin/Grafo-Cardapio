# CARDAPIO PERSONALIZADO

**Autor**: Nádia Bonin.
**Data final**: 11/06/2025

## Descrição
**Projeto final - Estrutura de dados aplicada - GRAFOS E BUSCA**.
Este projeto propõe a modelagem de um sistema de geração de cardápios personalizados utilizando grafos. A proposta considera as restrições alimentares de um grupo de pessoas como vegetarianismo, veganismo, intolerância à lactose, doença celíaca, diabetes e alergias alimentares, e utiliza grafos para representar a compatibilidade entre ingredientes. A partir disso, algoritmos de busca são empregados para gerar combinações válidas de ingredientes que formam cardápios seguros para todos os membros do grupo.

## Objetivos
✅	Compreender e aplicar representações de grafos: matriz e lista de adjacência.
✅	Utilizar algoritmos de busca em profundidade (DFS) para exploração do grafo.
✅	Desenvolver uma aplicação que modele um problema real com grafos.
✅	Avaliar a eficiência e validade das combinações geradas.
✅	Desenvolver uma interface simples em terminal para entrada de dados e visualização de resultados.

## Logica aplicada
-	Vértices: ingredientes disponíveis (17 ao total).
-	Arestas: são criadas entre dois ingredientes se ambos forem permitidos a todas as pessoas do grupo.
-	Tipo: grafo não-direcionado e não ponderado.
-	Implementações:
 -	Matriz de adjacência matrizadj[MAXI][MAXI] para conexões diretas.
 -	Lista de adjacência listaadj[MAXI] para eficiência na DFS.

## Busca
DFS (Depth First Search),	O algoritmo marca os ingredientes visitados para evitar ciclos,	a cada caminho válido de tamanho n, o sistema imprime a combinação (cardápio).

## Problemas encontrados
O algoritmo atual de DFS gera combinações repetidas de ingredientes, o que aumenta significativamente o custo de processamento. Por exemplo, se considerarmos apenas 2 ingredientes disponíveis, como leite e tomate, o DFS produz duas combinações distintas: [leite, tomate] e [tomate, leite]. No entanto, para o objetivo do projeto, essas combinações deveriam ser consideradas equivalentes, pois contêm os mesmos ingredientes. Esse comportamento se torna crítico à medida que o número de ingredientes aumenta, já que o número de permutações cresce fatorialmente. No caso de 17 ingredientes, o DFS gera até 17! = 371.993.326.789.902 combinações possíveis, incluindo repetições que não fazem diferença para a análise final, tornando o processamento extremamente custoso. Uma estratégia mais eficaz seria gerar apenas combinações únicas desde o início. Por exemplo, ordenando os ingredientes e permitindo que o DFS adicione apenas ingredientes que aparecem depois na ordem.

## Como Executar
1. Abrir o projeto no Visual Studio.
2. Compilar e rodar.
3. Inserir dados das restrições alimentares.
4. Observar os cardápios gerados no terminal.
