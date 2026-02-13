import time


# Memória-terhelő
def kmemoria():
    blokkok = []
    blokk = 50 * 1024 * 1024  # 50 MB

    try:
        while True:
            blokkok.append(bytearray(blokk))
            print(f"RAM felhasználva: {len(blokkok)*50} MB")
            time.sleep(0.1)  # lassabb, hogy ne fagyjon azonnal

    except MemoryError:
        print("Elérte a memória határt, lefoglalva tartom...")
        while True:
            time.sleep(1)


if __name__ == "__main__":
    kmemoria()
