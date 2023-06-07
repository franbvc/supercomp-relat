import os
import re
import subprocess
import time

from tqdm import tqdm


def is_valid_file(file_name):
    #pattern = r'input_[1-2]?[0-9]?_.*'
    pattern = r'input_((1?[0-9]?)|(2[0-6]))_.*'
    return re.match(pattern, file_name) is not None


def benchmark_input(input_file: str) -> tuple[str, str, float]:
    with open(input_file) as f:
        start = time.perf_counter()
        proc = subprocess.run(
            [".\exhaustive_omp.exe"], input=f.read(), text=True, capture_output=True)
        end = time.perf_counter()

    return proc.stdout, proc.stderr, end - start


def main():
    with open("exhaustive_omp_benchmark.txt", 'w') as result_f:
        result_f.write(
            f"Input File | Stdout | Stderr | Tempo total(s)\n"
        )
        directory = ".\input"

        for filename in tqdm(os.listdir(directory)):
            if not filename.endswith(".txt"):
                continue
            if not is_valid_file(filename):
                continue

            print(f"Running {filename}...")

            (out, err, time) = benchmark_input(
                input_file=os.path.join(directory, filename))
            result_f.write(f"{filename}|{out}|{err}|{time:.6f}\n")


if __name__ == '__main__':
    main()
