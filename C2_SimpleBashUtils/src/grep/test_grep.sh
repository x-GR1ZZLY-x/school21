#!/bin/bash

S21=./s21_grep
SYS=grep
FILE=test_grep.txt

SUCCESS=0
FAIL=0
TOTAL=0

run_test(){
    ARGS="$1"

    $S21 $ARGS $FILE > s21_out.txt
    $SYS $ARGS $FILE > sys_out.txt

    if diff -q s21_out.txt sys_out.txt > /dev/null; then
        echo "[OK] $ARGS"
        ((SUCCESS++))
    else
        echo "[FAIL] $ARGS"
        diff s21_out.txt sys_out.txt
        ((FAIL++))
    fi

    ((TOTAL++))
    rm -f s21_out.txt sys_out.txt
}

echo "Single flags:"
run_test "main"
run_test "MAIN"

echo "Flags with pattern:"
run_test "-i main"
run_test "-v main"
run_test "-n main"
run_test "-c main"
run_test "-l main"
run_test "-e main"

echo "Flag combinations:"
run_test "-i -n main"
run_test "-v -n main"
run_test "-i -v main"
run_test "-v -c main"
run_test "-i -c main"
run_test "-n -c main"
run_test "-i -l main"
run_test "-v -l main"
run_test "-lc main"
run_test "-in main"
run_test "-ivlcne main"

echo "Many patterns:"
run_test "-e main -e return"
run_test "-i -e main -e RETURN"
run_test "-v -e main -e return"
run_test "-v -e main -e MaiN -ic"

echo "Edge cases:"
run_test "-- main"
run_test "nomatchpattern"
run_test "-v nomatchpattern"
run_test "-c no match pattern"
run_test "-l nomatchpattern"
run_test "-d dvsv"

run_test "-i ^m"
run_test "^main"
run_test ".ain"
run_test "\\"

echo "SUCCESS: $SUCCESS"
echo "FAIL:    $FAIL"
echo "TOTAL:   $TOTAL"