## How to run the code:
    Compile with standard flags in cmake, and navigate into the buildVCPkg/src folder and run main. Main takes argument of width, height, samples per pixel, recursion depth, and file name, in that order.
    
    So to generate the image with a width of 150, a height of 100, 4 samples per pixel, and a recursion depth of 3, named CoolPic.png you would run:

    ./main 150 100 4 3 CoolPic.png

    I reccomend prioritizing recursion depth over samples per pixel in terms of where you dedicate your somputing power, as the image looks cooler the deeper you go.