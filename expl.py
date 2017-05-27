    import matplotlib.pyplot as plt
    plt.plot([1, 2, 3, 4, 5, 6, 7, 8,9, 10], [6692, 508, 518, 615,603,693,763,689,817,841])
    plt.ylabel('Time(ms)')
    plt.xlabel('Number of threads')
    plt.title('Графік залежності часу виконання задачі від кількості потоків.')
    plt.grid(True)
    plt.savefig("test.png")
    plt.show()
