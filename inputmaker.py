import itertools
import csv

estrategias = ["sequencial", "id", "buckets", "id-simd", "buckets-simd"]
dimensoes = [1000, 100, 10]
threads = [1, 2, 3, 4, 5, 6, 7, 8]


input_archive = "input.csv"
cabecalho = ["estrategias", "threads", "dimensoes(N X N)"]

todas_combinacoes = itertools.product(estrategias, threads, dimensoes)
i = 0

try:
    with open(input_archive, "w", newline="", encoding="utf-8") as arquivo_csv:
        input = csv.writer(arquivo_csv)
        input.writerow(cabecalho)

        for combinacao in todas_combinacoes:
            linha = [combinacao[0], combinacao[1], combinacao[2]]
            input.writerow(linha)
            i += 1


except IOError:
    print(f"Erro: Não foi possível escrever no arquivo {input_archive}")
