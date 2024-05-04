#!/bin/bash

# Function to monitor memory usage of a PID
monitor_memory_usage() {
    pid=$1
    while true; do
        memory_usage=$(ps -p $pid -o rss | grep -v RSS)
        echo "Memory usage of PID $pid: $memory_usage KB"
        sleep 1  # Adjust the interval as needed
    done
}

# Example usage: Monitor memory usage of a program named "example_program"
program_name="cub3D"
pid=$(pgrep "$program_name")

if [ -z "$pid" ]; then
    echo "Program '$program_name' is not running."
    exit 1
fi

echo "Monitoring memory usage of '$program_name' (PID: $pid)"
monitor_memory_usage "$pid"