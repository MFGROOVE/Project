import itertools
import csv

estrategias = ["sequencial", "id", "buckets", "id-simd", "buckets-simd","static-buckets"]
dimensoes = [1000, 100, 10]
threads = [1, 2, 3, 4, 5, 6, 7, 8]
size_bucket= [50,100,150,200]

input_archive = "input.csv"
cabecalho = ["estrategias", "threads", "dimensao","bucket_size"]

todas_combinacoes = itertools.product(estrategias, threads, dimensoes,size_bucket)
i = 0

try:
    with open(input_archive, "w", newline="", encoding="utf-8") as arquivo_csv:
        input = csv.writer(arquivo_csv)
        input.writerow(cabecalho)

        for combinacao in todas_combinacoes:
            linha = [combinacao[0], combinacao[1], combinacao[2],combinacao[3]]
            input.writerow(linha)


except IOError:
    print(f"Erro: Não foi possível escrever no arquivo {input_archive}")
