add_library(functions functions.c
        dataCaller.c
        tank.c
        tank.h
        structs.h
        dates.c
        dates.h
)
add_library(dataCaller dataCaller.c
        structs.h
        dates.c
        dates.h)

