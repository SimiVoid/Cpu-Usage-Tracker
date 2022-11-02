# cpu-usage-tracker

Cpu Usage Tracker is simple multithread application that tracks cpu usage on your linux machine. It uses /proc/stat file to get cpu usage information.

## Build

```bash
mkdir build
cd build
# CC and CXX are environment variables that specify compiler
cmake ..
make
```

Run tests
In directory build enter:
```bash
ctest
```
