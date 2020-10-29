import subprocess
import queue
from tqdm import tqdm

cycles_queue = queue.PriorityQueue(15)
load_queue = queue.PriorityQueue(15)
store_queue = queue.PriorityQueue(15)

pow_of_two = [2**i for i in range(14)]
for i in tqdm(pow_of_two):
    for j in tqdm(pow_of_two):
        for k in pow_of_two[3:]:
            if i*j*k > 32000:
                continue
            with open("./gcc.trace", "r") as trace:
                proc = subprocess.run(["./csim", str(i), str(j), str(k), "write-allocate", "write-back", "lru"], stdin=trace, stdout=subprocess.PIPE)
                stats = [int(string.split(": ")[1]) for string in str(proc.stdout).split("\\n")[:-1]]
                if load_queue.empty():
                    load_queue.put((stats[2], [i, j, k, stats[2], stats[4], stats[6]]))
                else:
                    cmp_obj = load_queue.get()
                    if  cmp_obj[0] < stats[2]:
                        if load_queue.full():
                            load_queue.put((stats[2], [i, j, k, stats[2], stats[4], stats[6]]), block=False)
                        else:
                            load_queue.put((stats[2], [i, j, k, stats[2], stats[4], stats[6]]), block=False)
                            try:
                                load_queue.put(cmp_obj, block=False)
                            except:
                                pass
                if store_queue.empty():
                    store_queue.put((stats[4], [i, j, k, stats[2], stats[4], stats[6]]))
                else:
                    cmp_obj = store_queue.get()
                    if  cmp_obj[0] < stats[4]:
                        if store_queue.full():
                            store_queue.put((stats[4], [i, j, k, stats[2], stats[4], stats[6]]), block=False)
                        else:
                            store_queue.put((stats[4], [i, j, k, stats[2], stats[4], stats[6]]), block=False)
                            try:
                                store_queue.put(cmp_obj, block=False)
                            except:
                                pass
                if stats[6] <= 8444084:
                    print(stats)
                if cycles_queue.empty():
                    cycles_queue.put((-stats[6], [i, j, k, stats[2], stats[4], stats[6]]), block=False)
                else:
                    cmp_obj = cycles_queue.get()
                    if cmp_obj[0] < -stats[6]:
                        if cycles_queue.full():
                            cycles_queue.put((-stats[6], [i, j, k, stats[2], stats[4], stats[6]]), block=False)
                        else:
                            cycles_queue.put((-stats[6], [i, j, k, stats[2], stats[4], stats[6]]), block=False)
                            try:
                                cycles_queue.put(cmp_obj, block=False)
                            except:
                                pass
print("32KB Max Cache:")
for i in range(15):
    if not cycles_queue.empty():
        print("Cycles:")
        print(cycles_queue.get())
    if not load_queue.empty():
        print("Load:")
        print(load_queue.get())
    if not store_queue.empty():
        print("Store:")
        print(store_queue.get())
