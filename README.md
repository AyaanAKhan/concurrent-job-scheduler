# Concurrent Job Scheduler

A C++17 multithreaded job scheduler that demonstrates concurrency, task queues, worker threads, and clean shutdown behavior.

This project is meant to show systems level programming ability beyond basic CRUD apps. It focuses on thread coordination, scheduling logic, and production style project structure.

## What It Demonstrates

- Modern C++17 development
- Worker thread pool design
- Priority based task scheduling
- Thread safe queue design direction
- Synchronization and graceful shutdown
- CMake based build workflow

## Core Concepts

```text
Submitted jobs
     |
     v
Priority queue
     |
     v
Worker thread pool
     |
     +--> Execute job A
     +--> Execute job B
     +--> Execute job C
     |
     v
Graceful shutdown
```

## Tech Stack

| Area | Tools |
|---|---|
| Language | C++17 |
| Build | CMake |
| Concepts | Threads, mutexes, condition variables, priority queues |

## Build and Run

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./concurrent_job_scheduler
```

## Repository Structure

```text
.
├── README.md
└── src/
    └── scheduler.cpp
```

## Recruiter Notes

This project is useful for showing concurrency fundamentals, C++ ability, and comfort with systems concepts. It pairs well with backend, infrastructure, embedded, fintech, and performance oriented roles.

## Future Improvements

- Add unit tests for queue ordering and shutdown behavior
- Add timed jobs and delayed scheduling
- Add dynamic worker pool resizing
- Add benchmarks for throughput under load
- Add CI with build and test checks
- Separate scheduler classes into headers and source files
