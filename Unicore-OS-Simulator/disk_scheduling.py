def fcfs(requests, head):

    sequence = []
    movement = 0
    current = head

    for request in requests:

        movement += abs(current - request)

        current = request

        sequence.append(request)

    return sequence, movement


def sstf(requests, head):

    remaining = requests.copy()

    sequence = []

    movement = 0

    current = head

    while remaining:

        closest = min(
            remaining,
            key=lambda x: abs(x - current)
        )

        movement += abs(current - closest)

        current = closest

        sequence.append(closest)

        remaining.remove(closest)

    return sequence, movement


def scan(requests, head, disk_size=200):

    left = sorted(
        [r for r in requests if r < head]
    )

    right = sorted(
        [r for r in requests if r >= head]
    )

    sequence = []

    movement = 0

    current = head

    # Move right first
    for request in right:

        movement += abs(current - request)

        current = request

        sequence.append(request)

    # Move to end of disk
    if right:

        movement += abs(
            current - (disk_size - 1)
        )

        current = disk_size - 1

    # Reverse direction
    for request in reversed(left):

        movement += abs(current - request)

        current = request

        sequence.append(request)

    return sequence, movement


def display_result(name, sequence, movement):

    print("\n" + "-" * 65)

    print(name)

    print("-" * 65)

    print("Service Sequence:")

    print(
        " -> ".join(
            map(str, sequence)
        )
    )

    print("\nTotal Head Movement :", movement)


def main():

    print("=" * 65)
    print("         UNICORE - DISK SCHEDULING MODULE")
    print("=" * 65)

    head = 53

    requests = [
        98, 183, 37, 122,
        14, 124, 65, 67,
        45, 150
    ]

    print("\nDisk Cylinders : 0 - 199")
    print("Initial Head   :", head)

    print("\nRequests:")
    print(requests)

    # FCFS
    fcfs_sequence, fcfs_movement = fcfs(
        requests,
        head
    )

    display_result(
        "1. FCFS",
        fcfs_sequence,
        fcfs_movement
    )

    # SSTF
    sstf_sequence, sstf_movement = sstf(
        requests,
        head
    )

    display_result(
        "2. SSTF",
        sstf_sequence,
        sstf_movement
    )

    # SCAN
    scan_sequence, scan_movement = scan(
        requests,
        head
    )

    display_result(
        "3. SCAN",
        scan_sequence,
        scan_movement
    )

    print("\n" + "=" * 65)
    print("DISK SCHEDULING COMPARISON")
    print("=" * 65)

    print(
        f"{'Algorithm':<15}"
        f"{'Head Movement':<20}"
    )

    print("-" * 40)

    print(
        f"{'FCFS':<15}"
        f"{fcfs_movement:<20}"
    )

    print(
        f"{'SSTF':<15}"
        f"{sstf_movement:<20}"
    )

    print(
        f"{'SCAN':<15}"
        f"{scan_movement:<20}"
    )

    print("=" * 65)


if __name__ == "__main__":
    main()