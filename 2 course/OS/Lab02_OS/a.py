import matplotlib.pyplot as plt

threads = [1,2, 4, 8]
work_times = [837.586,630.828, 507.853, 476.601]

plt.plot(threads, work_times, marker='o')
plt.title('Dependency of Work Time on Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Work Time (ms)')
plt.show()