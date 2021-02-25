zip source.zip *.cpp *.h CMakeLists.txt

./build.sh

for i in ./input/*.txt ;
do echo $i
./solution $i;
done

rm -rf ./output
mkdir ./output
mv ./input/*.txt_res ./output