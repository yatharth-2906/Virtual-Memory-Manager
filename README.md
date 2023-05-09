# Virtual-Memory-Manager
Virtual Memory Manager is a software component that manages the mapping of virtual addresses used by a process to physical memory addresses. It allows processes to use more memory than is physically available and swaps data between RAM and disk to maximize performance.

# Applications Of Virtual Memory Manager
Here are some applications of a Virtual Memory Manager:

* Allows multiple processes to run simultaneously, even when the total memory required by all processes exceeds the available physical memory.
* Reduces the amount of swapping of entire processes to disk, as it allows swapping of smaller units of memory.
* Provides a memory protection mechanism by allowing each process to have its own virtual address space.
* Enables the use of larger programs and datasets than can fit entirely in physical memory.
* Facilitates memory sharing between processes, as multiple processes can map to the same physical memory page.
* Improves overall system performance by reducing the number of page faults and minimizing disk I/O.


## Steps involved:

* Extract ‘Page Number’ and ‘Offset’ (Logical address)
* Find the corresponding frame number using page number.
* Consult TLB. If there is TLB hit, the frame number is obtained from TLB.
* If there is a TLB miss, consult page table. If there is a page table hit, the frame number is obtained.
* Otherwise, page fault occurs. After handling page fault, restart the process, frame number can be retrieved from TLB.
* Concatenate: ‘Frame Number’ and ‘Offset’ to get the corresponding ‘Physical address’.
* With frame number and offset, data can be extracted from physical memory.

![os_1](https://github.com/yatharth-2906/Virtual-Memory-Manager/assets/97800277/a81eefba-42dc-40d9-a244-a371936eef77)

![os_2](https://github.com/yatharth-2906/Virtual-Memory-Manager/assets/97800277/e52a0310-1fd9-4437-a5a0-5a53a35aa66b)

## Configuration:

* Physical memory of 65,536 bytes (256 frames * 256-byte frame size)
* Language: C
* Data: integer
* BackingStore: BinaryFile (BackingStore.bin)
* Input/ Output File: Txt File (address.txt; output.txt)
* Table Update method: LRU(Least Recent Use)

## Result and Analysis

* Program displays and stores the following values to output.txt.
* The logical address being translated.
* The corresponding physical address .
* The signed byte value stored at the translated physical address.
* Page-fault rate - The percentage of address references that resulted in page faults.
* TLB hit rate - The percentage of address references that were resolved in the TLB.

## Sample output

![os_3](https://github.com/yatharth-2906/Virtual-Memory-Manager/assets/97800277/24caea70-4f8d-46aa-834e-087221ac89ef)
