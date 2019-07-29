# Malloc
An implementation of the malloc function.

# API
```c
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);       /* print a summary of allocated blocks */
void	show_alloc_mem_ex(void);    /* same as above function + semantic hexdump of the allocated memory */
```

# Usage & testing

To create the library:
```sh
make
```

To add the shared library as the system malloc library:
```sh
source config.sh
```

To see an example of this implementation of the malloc function:
```sh
make exec
```
