def calculate_need(maximum, allocation):
    need = []

    for i in range(len(maximum)):
        row = []

        for j in range(len(maximum[i])):
            row.append(maximum[i][j] - allocation[i][j])

        need.append(row)

    return need


def is_safe(allocation, maximum, available):

    n = len(allocation)

    need = calculate_need(maximum, allocation)

    work = available.copy()

    finish = [False] * n

    safe_sequence = []

    while len(safe_sequence) < n:

        found = False

        for i in range(n):

            if not finish[i]:

                possible = True

                for j in range(len(work)):
                    if need[i][j] > work[j]:
                        possible = False
                        break

                if possible:

                    for j in range(len(work)):
                        work[j] += allocation[i][j]

                    finish[i] = True
                    safe_sequence.append(i)

                    found = True

        if not found:
            break

    return len(safe_sequence) == n, safe_sequence, need


def display_matrix(title, matrix):

    print("\n" + title)
    print("-" * 45)

    for row in matrix:
        print(" ".join(f"{value:4}" for value in row))


def test_request(allocation, maximum, available,
                 process, request):

    print("\n" + "=" * 65)
    print("UNSAFE RESOURCE REQUEST TEST")
    print("=" * 65)

    print(f"\nProcess P{process} requests:")
    print(request)

    need = calculate_need(maximum, allocation)

    for j in range(len(request)):

        if request[j] > need[process][j]:

            print("\nResult : REJECTED")
            print("Reason : Request exceeds declared maximum.")
            return

        if request[j] > available[j]:

            print("\nResult : REJECTED")
            print("Reason : Resources are currently unavailable.")
            return

    temp_allocation = [row.copy() for row in allocation]
    temp_available = available.copy()

    for j in range(len(request)):
        temp_available[j] -= request[j]
        temp_allocation[process][j] += request[j]

    safe, sequence, _ = is_safe(
        temp_allocation,
        maximum,
        temp_available
    )

    if safe:
        print("\nResult : GRANTED")
        print("Reason : System remains in a SAFE state.")

        print("\nNew Safe Sequence:")
        print(" -> ".join(f"P{i}" for i in sequence))

    else:
        print("\nResult : REJECTED")
        print("Reason : Request leads to an UNSAFE state.")


def main():

    print("=" * 65)
    print("          UNICORE - BANKER'S ALGORITHM")
    print("=" * 65)

    allocation = [
        [0, 1, 0, 1],
        [2, 0, 0, 0],
        [3, 0, 2, 1],
        [2, 1, 1, 0]
    ]

    maximum = [
        [2, 1, 1, 2],
        [3, 2, 1, 1],
        [3, 1, 2, 1],
        [4, 2, 1, 2]
    ]

    available = [1, 1, 1, 1]

    print("\nResources:")
    print("R1 R2 R3 R4")

    display_matrix("Allocation Matrix", allocation)
    display_matrix("Maximum Matrix", maximum)

    need = calculate_need(maximum, allocation)

    display_matrix("Need Matrix", need)

    print("\nAvailable Resources:")
    print(available)

    safe, sequence, _ = is_safe(
        allocation,
        maximum,
        available
    )

    print("\n" + "=" * 65)

    if safe:

        print("SYSTEM STATUS : SAFE")

        print("\nSafe Sequence:")

        print(" -> ".join(
            f"P{i}" for i in sequence
        ))

    else:

        print("SYSTEM STATUS : UNSAFE")

    print("=" * 65)

    # Test a resource request
    request = [0, 1, 1, 0]

    test_request(
        allocation,
        maximum,
        available,
        1,
        request
    )


if __name__ == "__main__":
    main()