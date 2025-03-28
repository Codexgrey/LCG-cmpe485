echo "Running tests..."
echo

output=$(./sim)

if [ $? -eq 0 ] ; then
  echo "Pass: Program exited zero"
else
  echo "Fail: Program did not exit zero"
  exit 1
fi

# nl=$(wc -l Results.doc | cut -f1 -d " ")

# if [ $nl -gt 100 ] ; then
#   echo "Pass: Number of lines in Results is greater than 100!"
# else
#   echo "Fail: Number of lines in Results is not greater than 100!"
#   exit 1
# fi

echo
echo "Simple tests OK!"

exit 0