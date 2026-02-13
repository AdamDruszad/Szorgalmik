import multiprocessing


# CPU-terhelő
def kcpu():
    x = 0
    while True:
        x += 1


if __name__ == "__main__":
    magok = multiprocessing.cpu_count()
    print(f"Használt CPU magok: {magok}")

    folyamatok = []

    # minden magra 1 folyamat
    for _ in range(magok):
        p = multiprocessing.Process(target=kcpu)
        p.start()
        folyamatok.append(p)

    try:
        for p in folyamatok:
            p.join()
    except KeyboardInterrupt:
        for p in folyamatok:
            p.terminate()
