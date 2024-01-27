# Parallel-Processing-Assignment-1

// INSTRUCTIONS
Hi boss, in this github project you'll find the prime counter you requested. It's written in c++ and only has a single source file, Assignment1.cpp. To compile and run it from the terminal,
first download it to your directory of choice then navigate their with the cd command. Since all of our company computers as well as the machine we're renting already has g++ installed,
run the command "g++ -o Assignment1 Assignment1.cpp" to compile the program. Then just type "Assignment1.exe" to run it.

// DOCUMENTATION/DESIGN APPROACH
The main approach is built around the one showcased in the lecture slides. There is a shared "counter" resource that hands out unused values to each thread, and it does this thanks to
a mutex guard lock. This ensures that the counter value is atomic. The main benefit of this approach is that the workload is shared pretty evenly between the threads. My instinctive approach
was to divide 10^8 into 8 chunks that became increasingly smaller as they drew closer to the maximum value, but the inherent unpredictability of where primes are found as well as the math required
to find the right distribution were just too much. This is a much simpler approach. As for the isPrime algorithm, I just went with what we were taught in Programming Languages with Leinecker. It's not
the fastest algorithm but I didn't want a probabilistic one, and I didn't want to use Sieve of Eratosthenes because the space complexity just seemed worse than the time complexity. There's also a
"topTen" queue structure used to track the ten highest primes. Since this is multithreaded, there's no guarantee that the "next" prime to come in is higher than the last, so topTen checks it.
