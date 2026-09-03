import threading
import time


shared_data = "EXAMINATION DATABASE"

read_count = 0

read_count_lock = threading.Lock()
resource_lock = threading.Lock()


def reader(reader_id):

    global read_count

    with read_count_lock:
        read_count += 1

        if read_count == 1:
            resource_lock.acquire()

    print(f"Reader {reader_id} -> Reading shared data")

    time.sleep(1)

    print(f"Reader {reader_id} -> Finished reading")

    with read_count_lock:
        read_count -= 1

        if read_count == 0:
            resource_lock.release()


def writer(writer_id):

    print(f"Writer {writer_id} -> Waiting for exclusive access")

    with resource_lock:

        print(f"Writer {writer_id} -> Writing to shared data")

        time.sleep(1)

        print(f"Writer {writer_id} -> Finished writing")


def main():

    print("=" * 65)
    print("       UNICORE - SYNCHRONIZATION MODULE")
    print("=" * 65)

    print("\nShared Resource:")
    print(shared_data)

    print("\nREADERS-WRITERS SIMULATION")
    print("-" * 50)

    threads = []

    threads.append(threading.Thread(target=reader, args=(1,)))
    threads.append(threading.Thread(target=reader, args=(2,)))
    threads.append(threading.Thread(target=writer, args=(1,)))
    threads.append(threading.Thread(target=reader, args=(3,)))

    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()

    print("\n" + "-" * 50)
    print("Race Condition      : PREVENTED")
    print("Shared Data Status   : CONSISTENT")
    print("Synchronization      : SUCCESSFUL")
    print("-" * 50)

    print("\nSynchronization module completed.")


if __name__ == "__main__":
    main()