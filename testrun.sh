#!/bin/bash

echo "Testing Non-Vector Interpreter"

for f in ExamplePrograms/*
do
	echo Running program $f
	./bfc $f
done

