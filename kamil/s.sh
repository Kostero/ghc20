for x in c e f; do
  echo $x
  ./pro $1 < $x.in > $x.out
  # ../kostka/checker $x.in $x.out
done
# wait
