def fifo(pages, frames_count):

    frames = []
    page_faults = 0
    pointer = 0

    print("\nFIFO PAGE REPLACEMENT")
    print("-" * 60)

    print(f"{'Page':<8}{'Frames':<25}{'Status'}")
    print("-" * 60)

    for page in pages:

        if page in frames:

            status = "HIT"

        else:

            page_faults += 1
            status = "FAULT"

            if len(frames) < frames_count:

                frames.append(page)

            else:

                frames[pointer] = page
                pointer = (pointer + 1) % frames_count

        print(
            f"{page:<8}"
            f"{str(frames):<25}"
            f"{status}"
        )

    print("\nTotal Page Faults :", page_faults)

    return page_faults


def lru(pages, frames_count):

    frames = []
    page_faults = 0

    print("\nLRU PAGE REPLACEMENT")
    print("-" * 60)

    print(f"{'Page':<8}{'Frames':<25}{'Status'}")
    print("-" * 60)

    for i, page in enumerate(pages):

        if page in frames:

            status = "HIT"

        else:

            page_faults += 1
            status = "FAULT"

            if len(frames) < frames_count:

                frames.append(page)

            else:

                recent = {}

                for frame in frames:

                    if frame in pages[:i]:
                        recent[frame] = i - 1 - pages[:i][::-1].index(frame)

                least_recent = min(
                    recent,
                    key=recent.get
                )

                index = frames.index(least_recent)

                frames[index] = page

        print(
            f"{page:<8}"
            f"{str(frames):<25}"
            f"{status}"
        )

    print("\nTotal Page Faults :", page_faults)

    return page_faults


def optimal(pages, frames_count):

    frames = []
    page_faults = 0

    print("\nOPTIMAL PAGE REPLACEMENT")
    print("-" * 60)

    print(f"{'Page':<8}{'Frames':<25}{'Status'}")
    print("-" * 60)

    for i, page in enumerate(pages):

        if page in frames:

            status = "HIT"

        else:

            page_faults += 1
            status = "FAULT"

            if len(frames) < frames_count:

                frames.append(page)

            else:

                future = pages[i + 1:]

                distances = {}

                for frame in frames:

                    if frame in future:
                        distances[frame] = future.index(frame)
                    else:
                        distances[frame] = float("inf")

                replace_page = max(
                    distances,
                    key=distances.get
                )

                index = frames.index(replace_page)

                frames[index] = page

        print(
            f"{page:<8}"
            f"{str(frames):<25}"
            f"{status}"
        )

    print("\nTotal Page Faults :", page_faults)

    return page_faults


def main():

    print("=" * 65)
    print("        UNICORE - MEMORY MANAGEMENT MODULE")
    print("=" * 65)

    pages = [
        7, 0, 1, 2, 0,
        3, 0, 4, 2, 3,
        0, 3, 2, 1, 2
    ]

    print("\nReference String:")
    print(" ".join(map(str, pages)))

    results = {}

    for frames in [3, 4]:

        print("\n")
        print("=" * 65)
        print(f"MEMORY FRAME CONFIGURATION : {frames} FRAMES")
        print("=" * 65)

        fifo_faults = fifo(pages, frames)
        lru_faults = lru(pages, frames)
        optimal_faults = optimal(pages, frames)

        results[frames] = {
            "FIFO": fifo_faults,
            "LRU": lru_faults,
            "Optimal": optimal_faults
        }

    print("\n" + "=" * 65)
    print("PAGE REPLACEMENT COMPARISON")
    print("=" * 65)

    print(
        f"{'Algorithm':<15}"
        f"{'3 Frames':<15}"
        f"{'4 Frames':<15}"
    )

    print("-" * 45)

    for algorithm in ["FIFO", "LRU", "Optimal"]:

        print(
            f"{algorithm:<15}"
            f"{results[3][algorithm]:<15}"
            f"{results[4][algorithm]:<15}"
        )

    print("=" * 65)


if __name__ == "__main__":
    main()