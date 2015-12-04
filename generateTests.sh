
for n in 2 4 8 16 32 64 128 256 512
do
    for i in 1 2 3 4 5
    do
        ./Gen $n > Tests/t${n}_${i}.dat
    done
done
