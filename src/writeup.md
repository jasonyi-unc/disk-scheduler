# Write Up

PID: 730475868 <br>
PID: 730506302 <br>
PID:           <br>
I pledge the COMP530 honor code.

## Note:

While working on this lab, we ran into some unforeseen circumstances with ADAMS shutting down, which hindered our ability to collect all the data. While we were able to get most of the data before ADAM went down, we were unable to collect data for HDD Sequential Stride Write, HDD Random Read, HDD Random Write, and SSD Sequential Stride Write. Out of these, we were able to gather the data for the SSD by running it locally on our machine. However, since none of us own a PC and we do not have access to a machine with an HDD, we were unable to collecte data for the 3. We also tried collecting data by running the script on Longleaf, but alas, we did not have the proper permissions to read / write data. 

Tl;dr: We were unable to collect the data necessary for HDD Sequential Stride Write, HDD Random Read, HDD Random Write and we request your leniency while grading these 3 plots.

## HDD

HDD performance improves significantly with larger I/O sizes, stabilizing at high throughput for sequential access patterns. Smaller I/O sizes and random access result in lower performance and higher variability, emphasizing the need for optimized I/O batching and sequential operations.

### HDD Sequential Read

![HDD_Sequential_Read](assets/HDD%20Sequential%20Read.png)

- The throughput stabilizes around 180 MB/s for I/O sizes above a certain threshold (e.g., ~4 KB). Smaller I/O sizes have significantly lower throughput and higher variability, indicating inefficiency for small requests.

- For optimal performance, file systems or applications should use larger I/O sizes (e.g., >=4 KB). This minimizes overhead and maximizes hardware utilization, particularly important for HDDs where throughput improves with sequential, larger block reads.

### HDD Sequential Write

![HDD_Sequential_Write](assets/HDD%20Sequential%20Write.png)

- Similar to read throughput, write performance improves as I/O size increases, stabilizing at around 150–200 MB/s for I/O sizes above ~16 KB. Smaller I/O sizes again show significant variability.

- Applications or file systems should batch or buffer small writes into larger blocks to achieve higher throughput. This is critical for HDDs, as frequent small writes degrade performance due to increased seek and rotational latency.

### HDD Sequential Stride Read

![HDD_Sequential_Stride_Read](assets/HDD%20Sequential%20Stride%20Read.png)

 - Larger I/O sizes (e.g., 10 MB, 8 MB) have higher throughput (~150-175 MB/s) regardless of the stride size, showing efficient sequential access. Smaller I/O sizes (e.g., 4 KB, 256 KB) experience much lower throughput, especially with smaller strides, highlighting inefficiency in handling frequent small reads.

 - Throughput for smaller I/O sizes improves slightly as stride size increases but remains substantially lower than that of larger I/O sizes. This implies that applications optimizing for HDD read performance should prioritize larger I/O sizes over adjusting stride sizes alone.


### HDD Sequential Stride Write

Unable to procure data. Please read the [Note](#note).

### HDD Random Read

Unable to procure data. Please read the [Note](#note).

### HDD Random Write

Unable to procure data. Please read the [Note](#note).

# SSD
SSD performance is highly influenced by the combination of I/O size and stride size, especially in sequential read and write operations. Larger I/O sizes consistently achieve higher throughput by minimizing overhead and fully utilizing the SSD’s bandwidth, while smaller I/O sizes are less efficient due to frequent processing of small data chunks. Stride size has limited impact in sequential workloads, as the SSD handles contiguous data efficiently. Optimal performance is observed with large I/O sizes (8 MB or 10 MB), where throughput stabilizes near the SSD’s peak capability, making them ideal for high-performance workloads.n Random writes are definitely slower than random reads since writes may require some additional overhead work like re-writing.

### SSD Sequential Read
![SSD Sequential Read](assets/SSD%20Sequential%20Read.png)

- Throughput grows very sharply for smaller I/O sizes but it stabilizes for higher sizes (after 20000KB approx.)  

- There is a very slight upward trend as I/O size increases  

- ### SSD Sequential Write
![SSD Sequential Write](assets/SSD%20Sequential%20Write.png)

- Very similar to the read, the throughput increases sharply for the smaller sizes but stabilizes at a point close to 20000KB

- There is a higher variability here as opposed to the previous graph

- Efficiency improves with larger I/O sizes

Overall, reads had a higher throughput than writes, which shows that SSDs are more equipped for read-heavy tasks.

### SSD Sequential Stride Read
![SSD Stride Read](assets/SSD%20Sequential%20Stride%20Read.png)

- Clearly smaller I/O sizes show much lesser throughput compared to bigger sizes.

- There is a sharp fall at the start with smaller strides with a lot of variance as well. But this stabilizes as the stride size increases and plateaus very early.

- Stride size causes variance for throughput due to stride size matching the size of the internal block sizes which leads to smoother performance.

### SSD Sequential Stride Write
![SSD Stride Write](assets/SSD%20Sequential%20Stride%20Write.png)

- Once again, higher I/O sizes get significantly higher throughput here.

- Smaller sizes have very high overhead and the performance barely increases for 4KB, 256KB. Throughput is highest for the highest size of 10MB.

- Differences occur in the stride size due to the stride sizes aligning with the internal block sizes.

### SSD Random Read

![SSD Random Read](assets/SSD%20Random%20Read.png)

- Throughput increases sharply for small I/O sizes, stabilizing around 300–350 MB/s after ~10,000 KB.

- For random reads, larger I/O sizes reduce the frequency of access requests and increase efficiency by fetching more data per request.

### SSD Random Write
![SSD Random Writw](assets/SSD%20Random%20Write.png)

- Throughput rises sharply for small I/O sizes, peaks early (~4,000–10,000 KB), and stabilizes around 150–200 MB/s

- While throughput stabilizes for higher sizes, there is a lot of variability seen as opposed to reads.

- Random writes can require erasure of some blocks to accommodate the new write which could explain higher variability.