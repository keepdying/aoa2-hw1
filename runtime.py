import subprocess
import time
import matplotlib
import os

matplotlib.use('Agg')
import matplotlib.pyplot as plt


# List of program arguments to test
args_list = [1, 2, 3, 6, 7, 9, 11, 13]

# List to store the runtimes
runtimes = []

cwd = os.getcwd()

# Iterate over the arguments and measure the runtime for each one
for arg in args_list:
    # Start the timer
    start_time = time.time()
    # Run the external program with the current argument
    subprocess.run([f"./main", f"./graphs/case{arg}/input_{arg}.txt"], cwd=cwd)

    # End the timer
    end_time = time.time()

    # Calculate the runtime
    runtime = (end_time - start_time) * 1000

    # Add the runtime to the list
    runtimes.append(runtime)

# Create a graph showing the runtimes for each argument
plt.bar(args_list, runtimes)
plt.xlabel('Cases')
plt.ylabel('Runtime (milliseconds)')
plt.title('Program Runtimes')

plt.xticks(args_list, args_list)
plt.yticks(range(0, int(max(runtimes)) + 1, 25))

# for i in range(len(args_list)):
#     plt.hlines(runtimes[i], 0, args_list[i], colors='grey', linestyles='dashed')

# Save the graph as a PNG file
plt.savefig('runtimes.png')
