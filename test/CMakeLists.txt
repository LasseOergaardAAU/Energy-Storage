add_executable(testAll testAll.c
        ../application/functions.c
        ../application/dataCaller.c
        ../application/structs.h
        ../application/tank.c
        ../application/dates.c
        ../application/dates.h
        tankTests.c
        dataCallerTests.c
        datesTests.c
        functionsTests.c
)

add_test(NAME testAll COMMAND testAll)
