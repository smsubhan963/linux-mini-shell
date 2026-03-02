# Mini Linux Shell (Process Management)

Created a small command-line program that can run other programs and manage them. Practiced core Linux process concepts (starting programs, waiting for completion, and inspecting process details) to understand how command execution works under the hood.

## What this project demonstrates
- `fork()` to create a child process
- `execvp()` to replace the child with the requested command
- `wait()` / `waitpid()` so the parent shell can wait for completion
- Basic command parsing (command + arguments)
- Process inspection using the Linux `/proc` filesystem

## Project structure
- `src/osh.c` — the mini shell implementation
- `screenshots/` — screenshots used in this README

## Build & run
```bash
cd src
gcc -g osh.c -o osh
./osh
