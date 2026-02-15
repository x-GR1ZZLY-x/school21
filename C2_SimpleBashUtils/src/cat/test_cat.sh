#!/bin/bash

S21=./s21_cat
SYS=cat
FILE=test.txt

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
for f in -n -b -g -e -t -v -E -T
do
    run_test "$f"
done

echo "Combination flags:"
FLAGS=(-n -b -s -e -t -v -E -T)
for ((i=0; i<${#FLAGS[@]}; i++)); do
    for ((j=i+1; j<${#FLAGS[@]}; j++)); do
        run_test "${FLAGS[i]} ${FLAGS[j]}"
    done
done

echo "Triple combinations:"
for ((i=0; i<${#FLAGS[@]}; i++)); do
    for ((j=i+1; j<${#FLAGS[@]}; j++)); do
        for((k=j+1; k<${#FLAGS[@]}; k++)); do
            run_test "${FLAGS[i]} ${FLAGS[j]} ${FLAGS[k]}"
        done
    done
done

echo "Additional tests:"
run_test ""
run_test "--"
run_test "--number"
run_test "--number-nonblank"
run_test "--squeeze-blank"
run_test "-n -b"
run_test "-b -n"
run_test "-nbsetvET"

echo "SUCCESS: $SUCCESS"
echo "FAIL:    $FAIL"
echo "TOTAL:   $TOTAL"