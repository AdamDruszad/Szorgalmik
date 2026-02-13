import multiprocessing
import time


#CPU-terhelő
def kcpu():
    x = 0
    while True:
        x += 1


#Memória-terhelő
def kmemoria():
    blokkok = []
    blokk = 50 * 1024 * 1024  # 50 MB-os

    try:
        while True:
            blokkok.append(bytearray(blokk))
            print(f"RAM felhasználva: {len(blokkok)*50} MB")
            time.sleep(0.1)  #azért, hogy ne fagyjon ki instant
    except MemoryError:
        print("Nincs több memória")
        while True:
            time.sleep(1)



if __name__ == "__main__":
    magok = multiprocessing.cpu_count()
    print(f"Használatban lévő CPU magok: {magok}")

    folyamatok = []

    # CPU
    for _ in range(magok):
        folyamat = multiprocessing.Process(target=kcpu)
        folyamat.start()
        folyamatok.append(folyamat)

    # Memorória
    memoria = multiprocessing.Process(target=kmemoria)
    memoria.start()
    folyamatok.append(memoria)

    try:
        for p in folyamatok:
            p.join()
    except KeyboardInterrupt:
        for p in folyamatok:
            p.terminate()
