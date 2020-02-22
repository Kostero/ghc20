for((i=1;i<=10;i++)); do
  echo $i
  ./pro $i < f.in > f.out &
done
wait
