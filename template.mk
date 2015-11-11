#CFLAGS= -Wall -ggdb -std=c++0x -Wshadow -Wfloat-equal -fstack-protector-all -DDEBUG -O0 -fmessage-length=0 
#CFLAGS= -Wall -ggdb -std=c++0x -Wshadow -Wfloat-equal
#CFLAGS= -Wall -pg

#CFLAGS= -Wall -std=c++0x -mtune=native -O3
#CFLAGS= -Wall -std=c++0x -DNDEBUG -mtune=native -O3

CFLAGS= -Wall -std=c++0x -DNDEBUG -O3

#CFLAGS= -Wall -std=c++0x -ggdb -Wno-variadic-macros -Wno-long-long -Wextra -Wno-unused-parameter -Wno-type-limits
#CFLAGS= -Wall -std=c++0x -ggdb #-ansi -pedantic -Wno-variadic-macros -Wno-long-long -Wextra -Wno-unused-parameter 

CC= g++ 

AR=ar rcs

