make kamilpro checker
for i in a b c d e f
do
  echo $i
  ./kamilpro <tests/$i.in >tests/$i.out
  ./checker tests/$i.in tests/$i.out
done
