import os
import subprocess
import time

from tqdm import tqdm


def benchmark_input(input_file: str) -> tuple[str, str, float]:
    with open(input_file) as f:
        start = time.perf_counter()
        proc = subprocess.run(
            [".\greedy_random.exe", "--benchmark"], input=f.read(), text=True, capture_output=True)
        end = time.perf_counter()

    return proc.stdout, proc.stderr, end - start


def main():
    with open("greedy_random_benchmark.txt", 'w') as result_f:
        result_f.write(
            f"Input File | Stdout | Stderr | Tempo total(s)\n"
        )
        directory = ".\input"

        for filename in tqdm(os.listdir(directory)):
            if filename.endswith(".txt"):
                (out, err, time) = benchmark_input(
                    input_file=os.path.join(directory, filename))
                result_f.write(f"{filename}|{out}|{err}|{time:.6f}\n")


if __name__ == '__main__':
    main()
