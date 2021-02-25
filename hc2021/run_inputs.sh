zip source.zip *.cpp *.h CMakeLists.txt

for i in ./input/*.txt ;
do echo $i
./solution $i;
done
