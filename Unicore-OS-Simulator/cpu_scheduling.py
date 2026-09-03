from collections import deque
# ---------------------------------------------------------
# FCFS SCHEDULING
# ---------------------------------------------------------
def fcfs(processes):
    processes = sorted(processes, key=lambda x: x["arrival"])
    current_time = 0
    results = []
    gantt = []
    for p in processes:
        pid = p["pid"]
        arrival = p["arrival"]
        burst = p["burst"]
        if current_time < arrival:
            current_time = arrival
        start = current_time
        waiting = start - arrival
        current_time += burst
        completion = current_time
        turnaround = completion - arrival
        response = start - arrival
        results.append({
            "pid": pid,
            "waiting": waiting,
            "turnaround": turnaround,
            "response": response
        })

        gantt.append((pid, start, completion))

    return results, gantt


# ---------------------------------------------------------
# ROUND ROBIN
# ---------------------------------------------------------
def round_robin(processes, quantum):
    processes = sorted(processes, key=lambda x: x["arrival"])

    n = len(processes)
    remaining = {p["pid"]: p["burst"] for p in processes}
    response = {p["pid"]: None for p in processes}
    completion = {}

    queue = deque()
    current_time = 0
    index = 0
    gantt = []

    while len(completion) < n:

        # Add arrived processes
        while index < n and processes[index]["arrival"] <= current_time:
            queue.append(processes[index]["pid"])
            index += 1

        # If queue is empty, jump to next process
        if not queue:
            if index < n:
                current_time = processes[index]["arrival"]
                continue

        pid = queue.popleft()

        if response[pid] is None:
            response[pid] = current_time - next(
                p["arrival"] for p in processes if p["pid"] == pid
            )

        execution = min(quantum, remaining[pid])

        start = current_time
        current_time += execution
        remaining[pid] -= execution

        gantt.append((pid, start, current_time))

        # Add newly arrived processes
        while index < n and processes[index]["arrival"] <= current_time:
            queue.append(processes[index]["pid"])
            index += 1

        if remaining[pid] > 0:
            queue.append(pid)
        else:
            completion[pid] = current_time

    results = []

    for p in processes:
        pid = p["pid"]

        turnaround = completion[pid] - p["arrival"]
        waiting = turnaround - p["burst"]

        results.append({
            "pid": pid,
            "waiting": waiting,
            "turnaround": turnaround,
            "response": response[pid]
        })

    return results, gantt


# ---------------------------------------------------------
# DISPLAY RESULTS
# ---------------------------------------------------------
def display_results(name, results, gantt):

    print("\n" + "=" * 65)
    print(name)
    print("=" * 65)

    print("\nGANTT CHART")

    for pid, start, end in gantt:
        print(f"| {pid} ", end="")
    print("|")

    print(gantt[0][1], end=" ")

    for _, _, end in gantt:
        print(f"--> {end}", end=" ")

    print("\n")

    print(f"{'Process':<10}{'Waiting':<12}"
          f"{'Turnaround':<15}{'Response':<12}")

    print("-" * 50)

    total_waiting = 0
    total_turnaround = 0
    total_response = 0

    for r in results:
        print(f"{r['pid']:<10}"
              f"{r['waiting']:<12}"
              f"{r['turnaround']:<15}"
              f"{r['response']:<12}")

        total_waiting += r["waiting"]
        total_turnaround += r["turnaround"]
        total_response += r["response"]

    n = len(results)

    print("-" * 50)

    print(f"Average Waiting Time    : {total_waiting / n:.2f}")
    print(f"Average Turnaround Time : {total_turnaround / n:.2f}")
    print(f"Average Response Time   : {total_response / n:.2f}")


# ---------------------------------------------------------
# MAIN PROGRAM
# ---------------------------------------------------------
def main():

    print("=" * 65)
    print("        UNICORE - CPU SCHEDULING MODULE")
    print("=" * 65)

    processes = [
        {"pid": "P1", "arrival": 0, "burst": 5},
        {"pid": "P2", "arrival": 1, "burst": 8},
        {"pid": "P3", "arrival": 2, "burst": 4},
        {"pid": "P4", "arrival": 3, "burst": 3},
        {"pid": "P5", "arrival": 4, "burst": 10},
        {"pid": "P6", "arrival": 5, "burst": 7},
        {"pid": "P7", "arrival": 6, "burst": 4},
        {"pid": "P8", "arrival": 7, "burst": 6}
    ]

    print("\nUNIVERSITY WORKLOAD")
    print("-" * 50)

    print(f"{'Process':<10}{'Arrival':<12}{'Burst':<10}")

    for p in processes:
        print(f"{p['pid']:<10}{p['arrival']:<12}{p['burst']:<10}")

    # FCFS
    fcfs_results, fcfs_gantt = fcfs(processes)
    display_results("1. FCFS SCHEDULING", fcfs_results, fcfs_gantt)

    # Round Robin
    rr_results, rr_gantt = round_robin(processes, 3)
    display_results("2. ROUND ROBIN SCHEDULING (QUANTUM = 3)",
                    rr_results, rr_gantt)

    print("\n" + "=" * 65)
    print("CPU SCHEDULING MODULE COMPLETED")
    print("=" * 65)


if __name__ == "__main__":
    main()