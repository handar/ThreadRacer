# Thread Racing

## Build Instructions
make

## Run Instructions
./threadracer

## Explain why your program produces the wrong output
The output is supposed to be far away from 0, because of nanosleep(). The adderThread is supposed to add 3 to the globalValue and the subtractorThread is supposed to take away 3 from the globalValue. So normally, that would just make the globalValue 0. But, placing nanosleep() strategically in specific places in the code affects the globalValue and throws the number of threads created out of sync so it does not end up equaling 0 at the end. 
