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

### SSD Stride Read
![SSD Stride Read](assets/SSD%20Sequential%20Stride%20Read.png)

- Clearly smaller I/O sizes show much lesser throughput compared to bigger sizes.

- There is a sharp fall at the start with smaller strides with a lot of variance as well. But this stabilizes as the stride size increases and plateaus very early.

- At smaller strides, frequent access to non-contiguous data leads to higher latency for fetching data. As the stride size increases, contiguous blocks can be read, allowing higher throughput.

### SSD Stride Write
![SSD Stride Write](assets/SSD%20Sequential%20Stride%20Write.png)

- 