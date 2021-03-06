
#define TSS             0x00000500
#define SOFTIRQLIST     0x00000600
#define GDT             0x00000608
#define SOCKETSLIST     0x00000708
#define MEMMAP          0x00000710
#define MEMMAPEND       0x00000BFF
#define IOAPICHANDLERS  0x00000C00      
#define RESERVED2       0x00001C00      
#define RESERVED2END    0x00001FFF      
#define SMP_TRAMPOLINE  0x00002000      // needs to be aligned on a 4k page 
#define IPI_MESSAGES    0x00002100
#define VMINFOS         0x00002300
#define VMINFOSEND      0x00006000

#define IDTSPACE        0x00006000
#define RESERVED1       0x00007000
#define RESERVED1END    0x00007FFF
#define PML4TABLE       0x00008000      // needs to be 4k aligned. we only use 1 entry
#define PDPTTABLE       0x00009000      // only 1 table is needed (512 gig) 
#define RESERVED5       0x0000A000
#define RESERVED5END    0x0000DFFF
#define TMP_PAGE_TABLES 0x0000E000
#define PRDT1           0x00010000
#define PRDT2           0x00010010
#define TASKLIST_BASE   0x00020000
#define TASKLISTEND     0x0005FFFF
#define BLOCK_CACHE     0x00060000
#define BLOCK_CACHE_END 0x0006FFFF
#define AP_STACKS       0x00070000      // 64 256bytes stacks for max 64 CPUs
#define AP_STACKS_END   0x00077FFF
#define KERNEL_BASE     0x00100000       
#define KERNEL_END      0x00200000       

// Anything above this space is not mapped in user process.
// Anything below, is mapped in user process
#define PDTABLE         KERNEL_END     // need to be 4k aligned. enough space for 512 tables
#define PAGETABLES      (PDTABLE+0x00200000)


////////////////////////////////////////////////////
////////////////////////////////////////////////////
// Process virtual memoty
////////////////////////////////////////////////////
////////////////////////////////////////////////////
#define THREAD_CODE_START 0x02000000
#ifdef __ASSEMBLER__
#define TOP_VIRTUAL 0xFFFFFFFF00000000
#else
#define TOP_VIRTUAL 0xFFFFFFFF00000000LL
#endif
#define META_VIRTUAL_ADDRESS         ((TOP_VIRTUAL)-0x2000000) 
#define STACK0TOP_VIRTUAL_ADDRESS    (META_VIRTUAL_ADDRESS) //this can't be more than 4pages since ring3 stack top is 16k below it
#define STACK3TOP_VIRTUAL_ADDRESS    (STACK0TOP_VIRTUAL_ADDRESS-0x4000) 
#define STACK3_DEPTH (20*1024*1024)
#define STACK3BOTTOM_VIRTUAL_ADDRESS (STACK3TOP_VIRTUAL_ADDRESS-STACK3_DEPTH)
#define PAGE_GUARD                   (STACK3BOTTOM_VIRTUAL_ADDRESS-0x1000)
#define HEAP_TOP                     PAGE_GUARD

// we save the following information after the stack
#define AVX_SAVE_AREA   (META_VIRTUAL_ADDRESS)      //right at the begining. up to 0xFE0047F7
#define AVX_SAVE_AREA_END (AVX_SAVE_AREA+0x7F8)
#define TIME_SLICE_COUNT AVX_SAVE_AREA_END
#define CONSOLE_POINTER (TIME_SLICE_COUNT+8)
// file handles are stored as linked list at this address
#define FILE_HANDLE_ADDRESS (CONSOLE_POINTER+8)
#define PROCESS_HEAP_ADDRESS (FILE_HANDLE_ADDRESS+8)
#define PROCESS_VMCS (PROCESS_HEAP_ADDRESS+8)
#define VIDEO_POINTER (PROCESS_VMCS+8)

// MMIO. 
#define APIC_BASE       0xFEE00000

#define IDENTITY_MAPPING   0x4000000000


// Segment selectors
#define TSSSELECTOR     (0x20)
#define RING3CSSELECTOR (0x10)

//SOFTIRQ
#define SOFTIRQ_NET 0x01

//APIC
#define AP_STACK_SIZE   0x200
#define IPI_FIRST_VECTOR 0x60
#define IPI_TLB_SHOOTDOWN_VECTOR 0x60
#define IPI_LAST_VECTOR 0x7F
#define APIC_TIMER_VECTOR 0xF0 
#define APIC_SPURIOUS_VECTOR 0x4F // low nibble MUST be 0b1111
#define APIC_ERROR_VECTOR 0xFF
#define DESIRED_APIC_PERIOD_NS 10000000     // the APIC timer handler will be called every 10ms

// Scheduler
#define TASK_TIME_MS  40                   // a task will 40 ms
#define TASK_QUANTUM_COUNTER (TASK_TIME_MS/(DESIRED_APIC_PERIOD_NS/1000000))
#define SCREEN_REFRESH_RATE 30
#define SCREEN_REFRESH_RATE_COUNTER ((1000000000/SCREEN_REFRESH_RATE)/DESIRED_APIC_PERIOD_NS)
