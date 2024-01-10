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

| Compression Type | Final Compression | Bits per pixel | SNR | Encode time | Decode time | Compressed file size |
| :--- | :---: | :---: | :---: | :---: | :---: | ---: |
| Intra Lossless | 33.63% | 8.034 | None | 25.905s | 52.116s | 176.5mb |
| Hybrid Lossless | 43.36% | 6.857 | None | 54.359s | 58.255s | 150.7mb |
| Hybrid Lossy 64:64:64 | 50.35% | 6.011 | 92.39 | 65.334s | 70.055s | 132.1mb |
| Hybrid Lossy 16:16:16 | 52.06% | 5.803 | 31.33 | 52.993s | 59.890s | 127.5mb |
| Hybrid Lossy 8:8:8 | 52.1% | 5.799 | 26.94 | 55.683s | 58.275s | 127.4mb |
| Hybrid Lossy 3:3:3 | 52.11% | 5.798 | 25.75 | 54.825s | 54.825s | 127.4mb |


Conclusões da tabela acima:
 - Hybrid encoding é cerca de duas vezes mais lento do que intra, mas dá cerca de 10% mais compressão do ficheiro final;
 - O tempo de decoding entre o algoritmo Hybrid e Intra é o mesmo, visto que o Hybrid apenas requer uma multiplicação a mais no cálculo dos valores dos pixeis;
 - Visto que o algoritmo lossy usado encodifica o indice do step (0, 1, 2, 3, etc), não o próprio valor deste (0, 16, 32, 48, etc), o ganho de performance de steps mais pequenos (ex: 3:3:3) é parecido ao de steps maiores (16:16:16), uma vez que grande parte dos número encodificados gastam o mesmo número de bits ou no máximo apenas mais um ou dois. Isto não acontece caso o step seja muito mais alto, como por exemplo, 128 steps.
  
Com isto concluimos que a melhor compressão, em termos de performance de tempo e compressão, será do tipo Hybrid Lossy, com 16 passos de quantização em cada canal (y, u e v).

---

## TEST 2: Decide what M parameter to use
Assumindo o algoritmo Hybrid Lossy 16:16:16 obtido na tabela acima. 

| Parametro do Golomb (M) | Compression Type | Final Compression | Bits per pixel | Compressed file size | SNR |
| :--- | :---: | :---: | :---: |  :---: | ---: |
| 2 | Intra | 11.13% | 10.76 | 236.4mb | None |
| 4 | Intra | 33.62% | 8.034 | 176.5mb | None |
| 8 | Intra | 38.43% | 7.454 | 163.8mb | None |
| 16 | Intra | 34.07% | 7.982 | 175.4mb | None |
| 2 | Hybrid Lossless | 14.98% | 10.29 | 226.1mb | None |
| 4 | Hybrid Lossless | 43.36% | 6.857 | 150.7mb | None |
| 8 | Hybrid Lossless | 38.49% | 7.447 | 163.6mb | None |
| 16 | Hybrid Lossless | 33.27% | 8.078 | 177.5mb | None |
| 2 | Hybrid Lossy 16 | 52.54% | 5.745 | 126.2mb | 31.33 |
| 4 | Hybrid Lossy 16 | 52.06% | 5.803 | 127.5mb | 31.33 |
| 8 | Hybrid Lossy 16 | 45.33% | 6.619 | 145.4mb | 31.33 |
| 16 | Hybrid Lossy 16 | 35.42% | 7.818 | 171.8mb | 31.33 |

Conclusões da tabela acima:
 - Para a encodificação intra-frame, um M de 8 é preferível, visto que muitos valores encodificados podem ser maiores;
 - Para a encodificação Hybrid Lossless e Lossy 16 um M menor (ex:4) é preferencial, pois quase todos os valores codificados são muito mais pequenos, o que beneficia o tal M menor;
 - Com isto concluimos que um M de 4 é adequado à maior parte das soluções;
 - Também podemos notar que o valor SNR não é afetado pelo valor do Golomb, como seria de esperado.

---

Usando a encodificação Hybrid Lossy 16:
| Parametro do Golomb (M) | Video utilizado | Final Compression | Compressed file size | SNR |
| :--- | :---: | :---: | :---: | ---: |
| 4 | ducks_take_off | 52.06% | 127.5mb | 31.33 |
| 8 | ducks_take_off | 45.33% | 145.4mb | 31.33 |
| 4 | park_joy | 50.73% | 130.6mb | 23.18 |
| 8 | park_joy | 44.63% | 146.7mb | 23.18 |
| 4 | old_town_cross | 55.11% | 119.0mb | 36.53 |
| 8 | old_town_cross | 46.72% | 141.2mb | 36.53 |
| 4 | in_to_tree | 55.79% | 117.2mb | 35.26 |
| 8 | in_to_tree | 47.02% | 140.4mb | 35.26 |

Conclusões da tabela acima:
 - Independente do video, um parâmetro de M com valor 4 é sempre superior ao de valor 8, provando que o valor do parâmetro, apesar de sempre relacionado com o próprio video, não é afetado o suficiente por este em condições reais para ser nessário adapta-lo ao video em si, sendo então o valor final escolhido o 4.
  
---

## TEST 3: Decidir o Block Size, Best Block search size e seach block step length
Utilizando o video ducks_100_frames.y4m, o algoritmo Hybrid Lossy 16 e o parâmetro de Golomb 8.
O search size é 4 e o step lenght é 2

| Block Size | Final Compression | Compressed file size | Encode time |
| :--- | :---: | :---: | ---: |
| 2  | 39.2% | 161.7mb | 205.75s |
| 4  | 49.54% | 134.2mb | 140.03s |
| 8  | 52.06% | 127.5mb | 121.22s |
| 16 | 52.66% | 125.9mb | 111.72s |


Conclusões da tabela acima:
 - Um Block size de 8 é o optimal;
 - Apesar do block size de 16 parecer melhor, o tamanho de 8 foi escolhido pois a diferença de performance é pequena e este tem melhor capacidade de adaptar-se a outros videos;
 - Block sizes diferentes podem levar o programa a crashar na descodificação, provavelmente dado a checks errados de "saida de frame" no calculo do melhor bloco.

Assumindo um block size de 8 e step size de 2 a 2 até o tamanho do best block search

| Best Block Search Size | Step Size | Final Compression | Compressed file size | Encode time |
| :--- | :---: | :---: | :---: | ---: |
| 2  | 2 | 52.09% | 127.4mb | 55.936s |
| 4  | 2 | 52.06% | 127.5mb | 128.29s |
| 4  | 4 | 52.06% | 127.5mb |  68.21s |
| 8  | 2 | 52.00% | 127.7mb | 403.05s |
| 8  | 4 | 52.00% | 127.7mb | 125.43s |
| 8  | 8 | 52.03% | 127.6mb | 59.761s |

Com este teste concluimos:
  - Apesar de um best block search size de 2 com step size de 2 serem os valores optimais para estes parâmetros, estes valores são muito bons para videos com altas frames por segundo, dado que os melhores blocos vão ser todos perto dos originais, logo vamos optar por um best block search de 4 e step size de 4;
  - Block search sizes com valores parecidos ao tamanho dos steps levam a que menos blocos totais sejam avaliados, causando uma diminuição exponencial do tempo de encoding para uma perda marginal de performance.
  - Step sizes menores causam melhor taxa de compressão, o que indica que como o video testado tem muitas frames por segundo, as frames não tem muita diferença entre si, o que causa ao best block ser perto do bloco anterior. Isto é evidenciado pela linha de best block search size de 2 e step size de 2 com a linha de valores 4 e 4, que apesar de demorarem um tempo parecido, tem uma drástica diferença de performace; 


## TEST 4: Decidir a frequência de intra frames no algoritmo lossy
Utilizando o video ducks_100_frames.y4m, o algoritmo Hybrid Lossy 16 e o parâmetro de Golomb 8.
O block size é 8, o search size é 4 e o step lenght é 4

| Intra-frame Frequency | Final Compression | Compressed file size | Encode time | SNR |
| :--- | :---: | :---: | :---: | ---: |
| 3  | 52.06% | 127.5mb | 63.18s | 31.33 |
| 6  | 56.82% | 114.9mb | 60.869s | 31.32 |
| 12 | 59.05% | 108.9mb | 68.772s |  31.32 |
| 24 | 60.15% | 106mb | 71.732s |  31.33 |
| 100 | 61.28% | 103mb | 75.892s |  31.31 |

Com este teste concluimos:
  - Apesar de um maior intra frame frequency parecer melhorar considerávelmente a performance do algoritmo, apenas aumentado o tempo de encodificação, o ficheiro final para uma frequencia maior de 6 contém muitos erros visíveis, pois a soma das perdas da quantização após muitas frames leva a uma extrema perca de informação do video final;
  - Com isto, determinamos que uma frequencia de 6 é a melhor para ainda manter a qualidade do video e permitir o uso do algoritmo lossy para videos de longa duração sem perca do conteúdo essencial do video, independentemente do fator de quantização usado.
  

## Concluindo
Os parametros optimos finais são os seguintes:
```
 ------------- Parameters ------------- 
 ----- Block ----- 
 -> Golomb M = 4
 -> Block Size = 8
 -> Best Block Search Size = 4
 -> Block Step Size = 4
 -> Interframe Frequency = 6
 ----- Files ----- 
 -> Input Vid File = TestFiles/ducks_100_frames.y4m
 -> Input Vid Size = 1280x720
 -> Output Bin File = BinFiles/output.bin
 -> Output Vid File = OutputFiles/output.mp4
 -> Output Y4M File = OutputFiles/output.y4m
 ----- Lossy ----- 
 -> Lossy encoding was choosen 
 -> Lossy Y Quantization Step = 16
 -> Lossy U Quantization Step = 16
 -> Lossy V Quantization Step = 16
```
Com os resultados:

| Encodificação | Final Compression | Final size comparison (compressed /initial)| Compressed file size | Initial File Size | Bits per Pixel | Encode time | Decode time | SNR |
| :--- | :---: | :---: | :---: | :---:| :---: | :---: | :---: | ---: |
| Intra-frame | 33.63% | 66.37% | 176.5mb | 266mb | 8.034 | 26.971s | 71.433s | None (ထ) |
| Hybrid Lossless | 35.39% | 64.61% | 171.9mb | 266mb | 7.822 | 69.287s | 67.748s | None (ထ) |
| Hybrid Lossy 16:16:16 | 56.82% | 43.18% | 114.9mb | 266mb | 5.228 | 68.545s | 75.541s | 31.32 |