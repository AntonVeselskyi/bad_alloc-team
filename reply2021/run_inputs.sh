zip source.zip *.cpp *.h CMakeLists.txt

./build.sh

for i in ./input/*.in ;
do echo $i
./solution $i;
done

rm -rf ./output
mkdir ./output
mv ./input/*.in_res ./output