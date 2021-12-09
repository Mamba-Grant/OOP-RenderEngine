# set directory
cd /home/runner/Final-1/src

# install freeglut3.x.x - code by qcm (on replit)
if [ ! -f /home/runner/.apt/usr/lib/x86_64-linux-gnu/libglut.so.3 ]
then
  install-pkg freeglut3-dev
fi

# proud of the amount of bash I had to learn to make this work LOL
if [ ! -f /home/runner/.apt/usr/lib/x86_64-linux-gnu/libGLEW.so.2.0 ]
then
  install-pkg libglew-dev
fi

# compile
g++ main.cpp -o /home/runner/Final-1/src/main.out -lGLEW -lglut -lGLU -lGL -g
# run 
./main.out