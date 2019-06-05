## 1.1 Propósito
O projeto busca implementar um código que seja capaz de rotacionar em 90° uma matriz quadrática utilizando N threads, onde N é definido pelo usuário em sua compilação no sistema operacional Linux ou similares.
## 1.2 Visão Geral
Os dados para o preenchimento da matriz que sofrerá rotação estão separados em um arquivo com o formato .dat criado previamente. Com isso, o código desenvolvido terá que ler os dados, realizar a conversão em 90° com a implementação de múltiplos threads dessa matriz e então salvá-la em outro arquivo com o formato .rot. 
A sintaxe para a execução do programa no terminal do sistema operacional deverá ser: N M T <arquivo_de_entrada.dat> <arquivo_de_saida.rot> - onde N = número de linhas, M = número de colunas e T = número de threads. Após a execução, o arquivo de saída estará com o mesmo nome do arquivo de entrada, mudando somente o formato.

