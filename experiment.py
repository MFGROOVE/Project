import csv
import subprocess
import os
import sys
import re
from typing import Text

STRATEGY_TO_EXECUTABLE_MAP = {
    "sequencial": "multiply_sequencial",
    "id": "multiply_id",
    "bucket": "multiply_bucket",
    "id_simd": "multiply_id_simd",
    "bucket_simd": "multiply_bucket_simd",
    "buckets": "multiply_bucket",
    "id-simd": "multiply_id_simd",
    "buckets-simd": "multiply_bucket_simd",
}

SINGLE_ARG_EXECUTABLES = ["multiply_sequencial"]
BUILD_DIR = "build"
INPUT_CSV = "input.csv"
id_command = 'echo "$(hostname)-$(date +%F)-$(date +%T)"'
result_command = subprocess.run(id_command, capture_output=True, text=True, shell=True)
OUTPUT_CSV = result_command.stdout.strip() + ".csv"
STRATEGY_COLUMN_INDEX = 0
THREADS_COLUMN_INDEX = 1
DIMENSIONS_COLUMN_INDEX = 2
BINARIES_RESULTS = "Binaries_results"


def build_with_cmake():
    print("--- Iniciando Build com CMake ---")
    os.makedirs(BUILD_DIR, exist_ok=True)

    cmake_configure_cmd = [
        "cmake",
        "-S",
        ".",
        "-B",
        BUILD_DIR,
        "-DCMAKE_BUILD_TYPE=Release",
    ]
    cmake_build_cmd = ["cmake", "--build", BUILD_DIR]
    try:
        os.mkdir(BINARIES_RESULTS)
    except Exception as e:
        print(f"Erro:{e}")

    try:
        result = subprocess.run(
            cmake_configure_cmd, capture_output=True, text=True, check=False
        )
        if result.returncode != 0:
            print(f"erro ao configurar CMake\nStderr:\n{result.stderr}")
            sys.exit(1)

        result = subprocess.run(
            cmake_build_cmd, capture_output=True, text=True, check=False
        )
        if result.returncode != 0:
            print(f"ERRO compilando\nStderr:\n{result.stderr}")
            sys.exit(1)
        print("Projeto compilado")
    except Exception as e:
        print(f"Ocorreu um erro inesperado durante o build: {e}")
        sys.exit(1)

    print("--- Build Finalizado ---\n")
    return True


def run_benchmarks():
    print("--- Iniciando Benchmarks ---")
    try:
        with open(INPUT_CSV, mode="r", newline="", encoding="utf-8") as infile:
            reader = csv.reader(infile)
            try:
                header = next(reader)
            except StopIteration:
                print(
                    f"ERRO: O arquivo CSV '{INPUT_CSV}' está vazio ou não pôde ser lido."
                )
                return

            new_header = header + ["tempo"]
            output_rows = [new_header]

            for i, row in enumerate(reader):
                if not row:
                    continue

                strategy_name = row[STRATEGY_COLUMN_INDEX].strip().lower()
                num_threads = row[THREADS_COLUMN_INDEX].strip()
                dimension_val = row[DIMENSIONS_COLUMN_INDEX].strip()

                executable_name = STRATEGY_TO_EXECUTABLE_MAP.get(strategy_name)

                result_time = "ESTRATEGIA_NAO_ENCONTRADA"

                if executable_name:
                    exe_path = os.path.join(BUILD_DIR, executable_name)

                    if executable_name in SINGLE_ARG_EXECUTABLES:
                        command_to_run = [exe_path, dimension_val]
                        print(f"  -> Rodando '{executable_name}' (1 arg)...")
                    else:
                        command_to_run = [exe_path, num_threads, dimension_val]
                        print(f"  -> Rodando '{executable_name}' (2 args)...")

                    try:
                        result = subprocess.run(
                            command_to_run,
                            capture_output=True,
                            text=True,
                            check=True,
                            encoding="utf-8",
                        )
                        execution_time = result.stdout.strip().split("\n")[-1]
                        result_time = execution_time
                    except FileNotFoundError:
                        print(f"ERRO: Executável não encontrado: {exe_path}")
                        result_time = "ERRO_NAO_ENCONTRADO"
                    except subprocess.CalledProcessError as e:
                        print(f"ERRO ao executar '{executable_name}':")
                        print(f"   Comando: {' '.join(command_to_run)}")
                        print(f"   Saída de erro (stderr): {e.stderr.strip()}")
                        result_time = "ERRO_DE_EXECUCAO"
                else:
                    print(
                        f"  -> AVISO: A estratégia '{strategy_name}' não foi encontrada no mapeamento do script."
                    )

                output_rows.append(row + [result_time])

        with open(OUTPUT_CSV, mode="w", newline="", encoding="utf-8") as outfile:
            writer = csv.writer(outfile)
            writer.writerows(output_rows)

        print(f"\n--- Benchmarks Finalizados ---")
        print(f"Resultados salvos com sucesso em '{OUTPUT_CSV}'")

    except FileNotFoundError:
        print(f"ERRO: Arquivo de entrada '{INPUT_CSV}' não encontrado.")
        sys.exit(1)
    except IndexError:
        print(
            f"ERRO: Uma linha no CSV tem menos colunas que o esperado. Verifique o arquivo '{INPUT_CSV}'."
        )
        sys.exit(1)
    except Exception as e:
        print(f"Ocorreu um erro inesperado: {e}")
        sys.exit(1)


if __name__ == "__main__":
    if build_with_cmake():
        run_benchmarks()
