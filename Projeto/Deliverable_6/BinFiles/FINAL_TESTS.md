# Files
#### These files are used for all the tests bellow:
```
    ----- Files ----- 
    -> Input Vid File = TestFiles/ducks_100_frames.y4m
    -> Input Vid Size = 1280x720
    -> Output Bin File = BinFiles/output.bin
    -> Output Vid File = OutputFiles/output.mp4
    -> Output Y4M File = OutputFiles/output.y4m

    Initial file size: 266mb
```

# Tests
## TEST 1: Decide which algorithm and lossy parameters to use

#### Default Parameters:
```
     ----- Block ----- 
    -> Golomb M = 4
    -> Block Size = 8
    -> Best Block Search Size = 4
    -> Block Step Size = 4
    -> Interframe Frequency = 3
```

| Compression Type | Final Compression | Bits per pixel | Encode time | Decode time | Compressed file size |
| :--- | :---: | :---: | :---: | :---: | ---: |
| Intra Lossless | 66.37% | 8.034 | 25.905s | 52.116s | 176.5mb |
| Hybrid Lossless | 56.64% | 6.857 | 54.359s | 58.255s | 150.7mb |
| Hybrid Lossy 64:64:64 | 51.02% | 6.176 | 51.514s | 57.166s | 135.7mb |
| Hybrid Lossy 16:16:16 | 47.95% | 5.804 | 54.548s | 54.465s | 127.5mb |
| Hybrid Lossy 8:8:8 | 47.9% | 5.799 | 50.466s | 58.275s | 127.4mb |
| Hybrid Lossy 3:3:3 | 47.89% | 5.798 | 50.949s | 54.7s | 127.4mb |


Conclusões da tabela acima:
 - Hybrid encoding é cerca de duas vezes mais lento do que intra, mas dá cerca de 10% mais compressão do ficheiro final;
 - O tempo de decoding entre o algoritmo Hybrid e Intra é o mesmo, visto que o Hybrid apenas requer uma multiplicação a mais no cálculo dos valores dos pixeis;
 - Visto que o algoritmo lossy usado encodifica o indice do step (0, 1, 2, 3, etc), não o próprio valor deste (0, 16, 32, 48, etc), o ganho de performance de steps mais pequenos (ex: 3:3:3) é parecido ao de steps maiores (16:16:16), uma vez que grande parte dos número encodificados gastam o mesmo número de bits ou no máximo apenas mais um ou dois. Isto não acontece caso o step seja muito mais alto, como por exemplo, 128 steps.
  
Com isto concluimos que a melhor compressão, em termos de performance de tempo e compressão, será do tipo Hybrid Lossy, com 16 passos de quantização em cada canal (y, u e v).

---

## TEST 2: Decide what M parameter to use
Assumindo o algoritmo Hybrid Lossy 16:16:16 obtido na tabela acima. 

| Parametro do Golomb (M) | Final Compression | Bits per pixel | Compressed file size |
| :--- | :---: | :---: | ---: |
| 2 | Intra | 88.87% | 10.76 | 236.4mb |
| 4 | Intra | 66.37% | 8.034 | 176.5mb |
| 6 | Intra | 54.85% | 6.64 | 145.9mb |
| 8 | Intra | 61.57% | 7.454 | 163.8mb |
| 12 | Intra | 56.09% | 6.791 | 149.2mb |
| 2 | Hybrid Lossless | 65.87% | 7.974 | 175.2mb |
| 4 | Hybrid Lossless | 56.58% | 6.849 | 150.5mb |
| 6 | Hybrid Lossless | 49.36% | 5.975 | 131.3mb |
| 8 | Hybrid Lossless | 58.41% | 7.071 | 155.4mb |
| 12 | Hybrid Lossless | 54.94% | 6.651 | 146.1mb |
| 2 | Hybrid Lossy 16 | 47.51% | 5.751 | 126.4mb |
| 4 | Hybrid Lossy 16 | 47.95% | 5.804 | 127.5mb |
| 6 | Hybrid Lossy 16 | 43.99% | 5.326 | 117mb |
| 8 | Hybrid Lossy 16 | 54.68% | 6.619 | 145.4mb |
| 12 | Hybrid Lossy 16 | 52.81% | 6.393 | 140.5mb |

Usando a encodificação Hybrid Lossy 16:
| Parametro do Golomb (M) | Video utilizado | Final Compression | Compressed file size |
| :--- | :---: | :---: | ---: |
| 6 | ducks_take_off | 43.99% | 117mb |
| 8 | ducks_take_off | 54.68% | 145.4mb |
| 6 | park_joy | 44.92% | 119mb |
| 8 | park_joy | 55.40% | 146.8mb |
| 6 | in_to_tree | 41.61% | 110.3mb |
| 8 | in_to_tree | 52.98% | 140.4mb |
| 6 | old_town_cross | 42.04% | 111.4mb |
| 8 | old_town_cross | 53.28% | 141.2mb |

Conclusões da tabela acima:
 - Independente do video, um parâmetro de M com valor 6 é sempre superior ao de valor 8, provando que o valor do parâmetro, apesar de sempre relacionado com o próprio video, não é afetado o suficiente por este em condições reais para ser nessário adapta-lo ao video em si, sendo então o valor final escolhido o 6.
  
---

## TEST 3: Decidir o Block Size, Best Block search size e seach block step lenght
Utilizando o video ducks_100_frames.y4m, o algoritmo Hybrid Lossy 16 e o parâmetro de Golomb 6.
O search size é 4 e o step lenght é 2

| Block Size | Final Compression | Compressed file size | Encode time |
| :--- | :---: | :---: | ---: |
| 2  | 56.09% | 149.2mb | 184.04s |
| 4  | 46.36% | 123.3mb | 129.57s |
| 8  | 43.97% | 117mb | 107.24s |
| 16 | 56.26% | 149.6mb | 143.57s |


Conclusões da tabela acima:
 - Um Block size de 8 é o optimal;
 - Block sizes diferentes podem levar o programa a crashar na descodificação, provavelmente dado a checks errados de "saida de frame" no calculo do melhor bloco.

Assumindo um block size de 8 e step size de 2 a 2 até o tamanho do best block search

| Best Block Search Size | Step Size | Final Compression | Compressed file size | Encode time |
| :--- | :---: | :---: | :---: | ---: |
| 2  | 2 | 43.96% | 116.9mb | 50.055s |
| 4  | 2 | 43.97% | 117mb | 107.98s |
| 4  | 4 | 49.36% | 131.3mb | 53.488s |
| 8  | 2 | 44.01% | 117.1mb | 329.26s |
| 8  | 4 | 44.03% | 117.1mb | 106.22s |
| 8  | 8 | 44.01% | 117.1mb | 51.384s |

Com este teste concluimos:
  - Apesar de um best block search size de 2 com step size de 2 serem os valores optimais para estes parâmetros, estes valores são muito bons para videos com altas frames por segundo, dado que os melhores blocos vão ser todos perto dos originais, logo vamos optar por um best block search de 4 e step size de 2;
  - Block search sizes com valores parecidos ao tamanho dos steps levam a que menos blocos totais sejam avaliados, causando um aumento exponencial do tempo de encoding para um ganho marginal de performance.
  - Step sizes menores causam melhor taxa de compressão, o que indica que como o video testado tem muitas frames por segundo, as frames não tem muita diferença entre si, o que causa ao best block ser perto do bloco anterior. Isto é evidenciado pela linha de best block search size de 2 e step size de 2 com a linha de valores 4 e 4, que apesar de demorarem um tempo parecido, tem uma drástica diferença de performace; 


## TEST 4: Decidir a frequência de intra frames no algoritmo lossy
Utilizando o video ducks_100_frames.y4m, o algoritmo Hybrid Lossy 16 e o parâmetro de Golomb 6.
O block size é 8, o search size é 4 e o step lenght é 2

| Intra-frame Frequency | Final Compression | Compressed file size | Encode time |
| :--- | :---: | :---: | ---: |
| 3  | 43.97% | 117mb | 107.98s |
| 6  | 41.17% | 109.5mb | 132.04s |
| 12 | 39.85% | 106mb | 138.34s | 

Com este teste concluimos:
  - Apesar de um maior intra frame frequency parecer melhorar considerávelmente a performance do algoritmo, apenas aumentado o tempo de encodificação, o ficheiro final para uma frequencia maior de 3 está cheio de erros, pois a soma das perdas da quantização após muitas frames leva a uma extrema perca de informação do video final;
  - Com isto, determinamo que uma frequencia de 3 é a melhor para ainda manter a qualidade do video e permitir o use do algoritmo lossy.
  

## Concluindo
Os parametros optimos finais são os seguintes:  